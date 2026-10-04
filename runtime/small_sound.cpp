#include "small.h"
#include "small_internal.h"

#include <QAudioDevice>
#include <QAudioFormat>
#include <QAudioSink>
#include <QBuffer>
#include <QCoreApplication>
#include <QMediaDevices>
#include <QThread>
#include <QTimer>

#include <algorithm>
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

struct Player
{
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
    ~Player() { stop(); }
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

std::unique_ptr<SoundSystem>& System()
{
    static std::unique_ptr<SoundSystem> system;
    return system;
}

void Play(Tone tone, bool wait)
{
    Validate(tone);
    auto* app = QCoreApplication::instance();
    if (!app || app->thread() != QThread::currentThread())
        throw std::runtime_error("Sound must be played from the Small C++ application thread.");
    if (!System()) System() = std::make_unique<SoundSystem>();
    const QAudioDevice device = QMediaDevices::defaultAudioOutput();
    if (device.isNull())
    {
        if (!System()->warnedAboutDevice)
        {
            std::cerr << "Sound unavailable: no audio output device.\n";
            System()->warnedAboutDevice = true;
        }
        return;
    }

    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);
    if (!device.isFormatSupported(format)) format = device.preferredFormat();
    if (!format.isValid()) throw std::runtime_error("The audio device has no usable format.");

    auto player = std::make_shared<Player>(tone, device, format);
    if (!wait)
    {
        System()->players.push_back(player);
        return;
    }
    while (!player->Finished())
    {
        // Keep windows responsive, but do not advance the user's Main().
        QCoreApplication::processEvents();
        QThread::msleep(1);
    }
}
}

namespace small_detail
{
void ShutdownAudio()
{
    if (!System()) return;
    System()->Shutdown();
    System().reset();
}
}

void play_sound(Sound sound) { Play(Preset(sound), false); }
void play_sound_and_wait(Sound sound) { Play(Preset(sound), true); }
void beep(double frequency, double seconds) { Play({frequency, seconds, 0.25}, false); }
void beep_and_wait(double frequency, double seconds) { Play({frequency, seconds, 0.25}, true); }

} // namespace Small
