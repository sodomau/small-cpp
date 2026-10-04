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

`play_sound`, `play_sound_and_wait`, `beep`, `beep_and_wait`

## Runtime

`initialize_small`, `shutdown_small`, beginner-facing `small_main`

## Image Extension

Include `<small/image.h>`.

`Image`, `width`, `height`, `pixel`, `alpha`, `set_pixel`, `load_image`,
`save_image`, `draw_image`
