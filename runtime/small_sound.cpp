#include "small.h"
#include "small_internal.h"

#include <QAudioDevice>
#include <QAudioFormat>
#include <QAudioSink>
#include <QBuffer>
#include <QFile>
#include <QFileInfo>
#include <QHash>
#include <QtEndian>
#include <QCoreApplication>
#include <QMediaDevices>
#include <QThread>
#include <QTimer>

#include <algorithm>
#include <atomic>
#include <exception>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>

namespace Small
{
namespace
{
struct Tone
{
    double frequency;
    double seconds;
    double volume;
};

Tone Preset(Sound sound)
{
    // Preserve the nine v0.6 PCM presets; do not substitute an OS alert beep.
    switch (sound)
    {
    case Sound::Click:     return {900,  0.035, 0.18};
    case Sound::Pop:       return {300,  0.090, 0.28};
    case Sound::Jump:      return {600,  0.120, 0.22};
    case Sound::Hit:       return {140,  0.100, 0.32};
    case Sound::Coin:      return {1200, 0.120, 0.22};
    case Sound::Shoot:     return {220,  0.070, 0.30};
    case Sound::Explosion: return {80,   0.300, 0.35};
    case Sound::Win:       return {880,  0.350, 0.22};
    case Sound::Lose:      return {180,  0.400, 0.25};
    }
    throw std::invalid_argument("Unknown Sound preset.");
}

void Validate(Tone tone)
{
    if (!std::isfinite(tone.frequency) || tone.frequency <= 0 ||
        !std::isfinite(tone.seconds) || tone.seconds <= 0)
        throw std::invalid_argument("beep frequency and duration must be positive, finite numbers.");
}

QByteArray MakePcm(Tone tone, const QAudioFormat& format)
{
    const double frameCount = std::ceil(tone.seconds * format.sampleRate());
    const int bytesPerFrame = format.bytesPerFrame();
    if (bytesPerFrame <= 0 || frameCount > std::numeric_limits<int>::max() / bytesPerFrame)
        throw std::length_error("The requested sound is too long.");
    if (tone.frequency >= format.sampleRate() / 2.0)
        throw std::invalid_argument("beep frequency is too high for the audio device.");

    const int frames = static_cast<int>(frameCount);
    QByteArray bytes(frames * bytesPerFrame, '\0');
    char* destination = bytes.data();
    constexpr double twoPi = 6.28318530717958647692;

    for (int i = 0; i < frames; ++i)
    {
        const double t = static_cast<double>(i) / format.sampleRate();
        const double fade = std::clamp(std::min(t / 0.01, (tone.seconds - t) / 0.01), 0.0, 1.0);
        const double sample = std::sin(twoPi * tone.frequency * t) * tone.volume * fade;
        for (int channel = 0; channel < format.channelCount(); ++channel)
        {
            // memcpy avoids assuming the alignment of QByteArray's buffer.
            switch (format.sampleFormat())
            {
            case QAudioFormat::UInt8:
            {
                const auto value = static_cast<std::uint8_t>(std::clamp(128.0 + sample * 127.0, 0.0, 255.0));
                std::memcpy(destination, &value, sizeof value); destination += sizeof value;
                break;
            }
            case QAudioFormat::Int16:
            {
                const auto value = static_cast<std::int16_t>(sample * 32767.0);
                std::memcpy(destination, &value, sizeof value); destination += sizeof value;
                break;
            }
            case QAudioFormat::Int32:
            {
                const auto value = static_cast<std::int32_t>(sample * 2147483647.0);
                std::memcpy(destination, &value, sizeof value); destination += sizeof value;
                break;
            }
            case QAudioFormat::Float:
            {
                const auto value = static_cast<float>(sample);
                std::memcpy(destination, &value, sizeof value); destination += sizeof value;
                break;
            }
            default:
                throw std::runtime_error("Unsupported audio sample format.");
            }
        }
    }
    return bytes;
}

struct Wave
{
    QByteArray data;
    QAudioFormat format;
};

Wave LoadWave(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        throw std::runtime_error("Could not open sound file: " + path.toStdString());
    const QByteArray bytes = file.readAll();
    auto bad = [&]() { return std::runtime_error("Sound file must be a valid 16-bit PCM WAV: " + path.toStdString()); };
    if (bytes.size() < 12 || bytes.first(4) != "RIFF" || bytes.mid(8, 4) != "WAVE") throw bad();
    auto u16 = [&](qsizetype at) { return qFromLittleEndian<quint16>(bytes.constData() + at); };
    auto u32 = [&](qsizetype at) { return qFromLittleEndian<quint32>(bytes.constData() + at); };
    const quint64 end = quint64(u32(4)) + 8;
    if (end > quint64(bytes.size()) || end < 12) throw bad();
    Wave wave;
    bool foundFormat = false, foundData = false;
    for (quint64 offset = 12; offset + 8 <= end; ) {
        const qsizetype at = qsizetype(offset);
        const quint32 size = u32(at + 4);
        const quint64 next = offset + 8 + size;
        if (next > end) throw bad();
        if (bytes.mid(at, 4) == "fmt ") {
            if (size < 16 || u16(at + 8) != 1 || u16(at + 22) != 16) throw bad();
            const int channels = u16(at + 10);
            const quint32 rate = u32(at + 12);
            if ((channels != 1 && channels != 2) || rate < 8000 || rate > 192000
                || u16(at + 20) != channels * 2 || u32(at + 16) != rate * channels * 2) throw bad();
            wave.format.setSampleRate(int(rate));
            wave.format.setChannelCount(channels);
            wave.format.setSampleFormat(QAudioFormat::Int16);
            foundFormat = true;
        } else if (bytes.mid(at, 4) == "data") {
            wave.data = bytes.mid(at + 8, size);
            foundData = true;
        }
        offset = next + (size & 1);
    }
    if (!foundFormat || !foundData || wave.data.isEmpty()
        || wave.data.size() % wave.format.bytesPerFrame() != 0) throw bad();
    return wave;
}

struct Completion
{
    std::atomic<bool> done{false};
    std::exception_ptr error;
};

struct Player
{
    std::shared_ptr<Completion> completion;
    QByteArray data;
    QBuffer buffer;
    std::unique_ptr<QAudioSink> sink;

    Player(Tone tone, const QAudioDevice& device, const QAudioFormat& format)
        : data(MakePcm(tone, format)), buffer(&data),
          sink(std::make_unique<QAudioSink>(device, format))
    {
        buffer.open(QIODevice::ReadOnly);
        sink->start(&buffer);
    }
    Player(const Wave& wave, const QAudioDevice& device)
        : data(wave.data), buffer(&data),
          sink(std::make_unique<QAudioSink>(device, wave.format))
    {
        buffer.open(QIODevice::ReadOnly);
        sink->start(&buffer);
    }
    ~Player() { stop(); if (completion) completion->done.store(true, std::memory_order_release); }
    void stop()
    {
        if (sink)
        {
            sink->stop();
            buffer.close();
            sink.reset();
        }
    }
    bool Finished() const
    {
        return !sink || sink->state() == QAudio::IdleState || sink->state() == QAudio::StoppedState;
    }
};

struct SoundSystem
{
    std::vector<std::shared_ptr<Player>> players;
    QTimer cleanupTimer;
    bool warnedAboutDevice = false;

    SoundSystem()
    {
        QObject::connect(&cleanupTimer, &QTimer::timeout, &cleanupTimer, [this] {
            players.erase(std::remove_if(players.begin(), players.end(),
                [](const auto& player) { return player->Finished(); }), players.end());
        });
        cleanupTimer.start(50);
    }

    void Shutdown()
    {
        // shutdown_small() calls this while QApplication is still alive.
        // stop asynchronous cleanup first, then release every audio player.
        cleanupTimer.stop();
        for (auto& player : players)
            if (player) player->stop();
        players.clear();
    }
};

// Every audio QObject, including its timer and buffers, lives on this thread.
// Device discovery, PCM generation, sink start/stop must never stall a game frame.
class AudioThread
{
    QThread thread;
    QObject dispatcher;
    std::unique_ptr<SoundSystem> state;
    QHash<QString, Wave> files;
public:
    AudioThread()
    {
        dispatcher.moveToThread(&thread);
        thread.start();
    }
    ~AudioThread()
    {
        QMetaObject::invokeMethod(&dispatcher, [this] {
            if (state) state->Shutdown();
            state.reset();
            dispatcher.moveToThread(QCoreApplication::instance()->thread());
        }, Qt::BlockingQueuedConnection);
        thread.quit();
        thread.wait();
    }
    void SubmitFile(const QString& path, const std::shared_ptr<Completion>& completion,
                    bool wait, bool preload)
    {
        QMetaObject::invokeMethod(&dispatcher, [this, path, completion, wait, preload] {
            try {
                if (!files.contains(path)) files.insert(path, LoadWave(path));
                if (preload) {
                    completion->done.store(true, std::memory_order_release);
                    return;
                }
                if (!state) state = std::make_unique<SoundSystem>();
                const auto device = QMediaDevices::defaultAudioOutput();
                if (device.isNull()) throw std::runtime_error("No audio output device.");
                const auto& wave = files[path];
                if (!device.isFormatSupported(wave.format))
                    throw std::runtime_error("The audio device cannot play this WAV format.");
                auto player = std::make_shared<Player>(wave, device);
                player->completion = completion;
                state->players.push_back(std::move(player));
            } catch (...) {
                completion->error = std::current_exception();
                if (!wait) {
                    try { std::rethrow_exception(completion->error); }
                    catch (const std::exception& error) { std::cerr << "Sound unavailable: " << error.what() << '\n'; }
                }
                completion->done.store(true, std::memory_order_release);
            }
        }, Qt::QueuedConnection);
    }
    void Submit(Tone tone, const std::shared_ptr<Completion>& completion, bool wait)
    {
        QMetaObject::invokeMethod(&dispatcher, [this, tone, completion, wait] {
            try
            {
                if (!state) state = std::make_unique<SoundSystem>();
                const QAudioDevice device = QMediaDevices::defaultAudioOutput();
                if (device.isNull())
                {
                    if (!state->warnedAboutDevice)
                    {
                        std::cerr << "Sound unavailable: no audio output device.\n";
                        state->warnedAboutDevice = true;
                    }
                    completion->done.store(true, std::memory_order_release);
                    return;
                }
                QAudioFormat format;
                format.setSampleRate(44100);
                format.setChannelCount(1);
                format.setSampleFormat(QAudioFormat::Int16);
                if (!device.isFormatSupported(format)) format = device.preferredFormat();
                if (!format.isValid()) throw std::runtime_error("The audio device has no usable format.");
                auto player = std::make_shared<Player>(tone, device, format);
                player->completion = completion;
                state->players.push_back(std::move(player));
            }
            catch (...)
            {
                completion->error = std::current_exception();
                if (!wait)
                {
                    try { std::rethrow_exception(completion->error); }
                    catch (const std::exception& error) { std::cerr << "Sound unavailable: " << error.what() << '\n'; }
                    catch (...) { std::cerr << "Sound unavailable: unknown audio error.\n"; }
                }
                completion->done.store(true, std::memory_order_release);
            }
        }, Qt::QueuedConnection);
    }
};

std::unique_ptr<AudioThread>& System()
{
    static std::unique_ptr<AudioThread> system;
    return system;
}

void Play(Tone tone, bool wait)
{
    Validate(tone);
    auto* app = QCoreApplication::instance();
    if (!app || app->thread() != QThread::currentThread())
        throw std::runtime_error("Sound must be played from the Small C++ application thread.");
    if (!System()) System() = std::make_unique<AudioThread>();
    auto completion = std::make_shared<Completion>();
    System()->Submit(tone, completion, wait);
    if (!wait) return;
    while (!completion->done.load(std::memory_order_acquire))
    {
        // Keep windows responsive without advancing the learner's code.
        QCoreApplication::processEvents();
        QThread::msleep(1);
    }
    if (completion->error) std::rethrow_exception(completion->error);
}
void PlayFile(const String& path, bool wait, bool preload)
{
    auto* app = QCoreApplication::instance();
    if (!app || app->thread() != QThread::currentThread())
        throw std::runtime_error("Sound must be played from the Small C++ application thread.");
    if (path.length() == 0) throw std::invalid_argument("Sound file path must not be empty.");
    // Resolve before queueing: later changes to the working folder cannot change this request.
    const QString absolute = QFileInfo(QString::fromUtf8(path.c_str())).absoluteFilePath();
    if (!System()) System() = std::make_unique<AudioThread>();
    auto completion = std::make_shared<Completion>();
    System()->SubmitFile(absolute, completion, wait, preload);
    if (!wait) return;
    while (!completion->done.load(std::memory_order_acquire)) {
        QCoreApplication::processEvents();
        QThread::msleep(1);
    }
    if (completion->error) std::rethrow_exception(completion->error);
}

}

namespace small_detail
{
void ShutdownAudio()
{
    if (!System()) return;
    System().reset();
}
}

void preload_sound(const String& path) { PlayFile(path, true, true); }
void play_sound(const String& path) { PlayFile(path, false, false); }
void play_sound_and_wait(const String& path) { PlayFile(path, true, false); }
void play_sound(Sound sound) { Play(Preset(sound), false); }
void play_sound_and_wait(Sound sound) { Play(Preset(sound), true); }
void beep(double frequency, double seconds) { Play({frequency, seconds, 0.25}, false); }
void beep_and_wait(double frequency, double seconds) { Play({frequency, seconds, 0.25}, true); }

} // namespace Small
