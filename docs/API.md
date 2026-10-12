# Small C++ API --- Quick Reference

## Console

`print`, `write`, `format`, `input`, `input_int`, `input_real`

## Data

`String`: `length`, `substring`, `[]`, comparisons, concatenation

`Array<T>`: `length`, `[]`

## Files

`FileMode`: `Read`, `write`, `Append`, `ReadBinary`, `WriteBinary`,
`AppendBinary`

`File`: `open`, `close`, `is_open`, `end`, text input/output, `read_int`,
`read_real`, `write_int`, `write_real`

## Graphics

`Color`, `rgb`, built-in colors

`Window`: `open`, `set_title`, `close`, `is_open`, `width`, `height`,
`clear`, `set_pixel`, line/rectangle/circle/text drawing, `show`

## Input

Keyboard: `key_down`, `key_pressed`, `key_released`

Mouse: `mouse_x`, `mouse_y`, `mouse_down`, `mouse_pressed`, `mouse_released`

## Time / Random / Sound

`StopWatch`, `sleep`, `Timer`

`random_int`, `random_real`

`play_sound`, `play_sound_and_wait`, `preload_sound`, `beep`, `beep_and_wait`

`play_sound` and `play_sound_and_wait` accept either a built-in `Sound` or a
WAV file path (`String`). Files must be 16-bit PCM WAV, mono or stereo, in a
format supported by the audio device. Relative paths use the program's working
folder. The first `play_sound("sound.wav")` loads asynchronously; later calls
reuse cached samples. Each call has its own player, so sounds can overlap.
`preload_sound("sound.wav")` optionally waits for loading, without playing.
`play_sound_and_wait` waits for playback while keeping windows responsive.
The cache lasts until `shutdown_small()`; changing a cached file does not reload it.
Missing/invalid files throw from preload or waiting calls; asynchronous errors
are reported to the console. Include your WAV files with Publish → Add Files.

## Runtime

`initialize_small`, `shutdown_small`, beginner-facing `small_main`

## Image Extension

Include `<small/image.h>`.

`Image`, `width`, `height`, `pixel`, `alpha`, `set_pixel`, `load_image`,
`save_image`, `draw_image`
