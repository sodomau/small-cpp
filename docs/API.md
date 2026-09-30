# Small C++ API --- Quick Reference

## Console

`Print`, `Write`, `Format`, `Input`, `InputInt`, `InputReal`

## Data

`String`: `Length`, `Substring`, `[]`, comparisons, concatenation

`Array<T>`: `Length`, `[]`

## Files

`FileMode`: `Read`, `Write`, `Append`, `ReadBinary`, `WriteBinary`,
`AppendBinary`

`File`: `Open`, `Close`, `IsOpen`, `End`, text input/output, `ReadInt`,
`ReadReal`, `WriteInt`, `WriteReal`

## Graphics

`Color`, `RGB`, built-in colors

`Window`: `Open`, `SetTitle`, `Close`, `IsOpen`, `Width`, `Height`,
`Clear`, `SetPixel`, line/rectangle/circle/text drawing, `Show`

## Input

Keyboard: `KeyDown`, `KeyPressed`, `KeyReleased`

Mouse: `MouseX`, `MouseY`, `MouseDown`, `MousePressed`, `MouseReleased`

## Time / Random / Sound

`StopWatch`, `Sleep`, `Timer`

`RandomInt`, `RandomReal`

`PlaySound`, `PlaySoundAndWait`, `Beep`, `BeepAndWait`

## Runtime

`InitializeSmall`, `ShutdownSmall`, beginner-facing `SmallMain`

## Image Extension

Include `<small/image.h>`.

`Image`, `Width`, `Height`, `Pixel`, `Alpha`, `SetPixel`, `LoadImage`,
`SaveImage`, `DrawImage`
