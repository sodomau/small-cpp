# Extensions and Tutorials

## Extensions

Keep `extension.json` as an explicit package manifest. It documents
id/name, header/include location, library, and optional
examples/tutorial roots. Image is the reference extension.

Typical layout:

``` text
extensions/image/
├─ extension.json
├─ include/
├─ lib/
├─ examples/
└─ tutorial/
   ├─ 01_create/
   └─ 02_pixels/
```

Ordering is local to each extension; extensions themselves need no
curriculum order.

## Core tutorials

The current core pack has 88 Korean Small Steps lessons. The layout below
illustrates the supported format; `en.md` is an optional translation and
filenames such as `example1.cpp` may instead be `example.cpp`.

``` text
tutorial/
├─ languages.json
├─ 01_hello/
│  ├─ ko.md
│  ├─ en.md
│  ├─ example1.cpp
│  ├─ exercise1_starter.cpp
│  ├─ exercise1_solution.cpp
│  └─ images/
└─ ...
```

Folder `NN_id` supplies order/id. Core part information is Markdown
metadata.

## Languages

`languages.json` declares selectable languages/default. Missing
translations fall back to the default. C++ and images are shared between
translations.

## Special tags

``` markdown
@code example1.cpp
@exercise exercise1_starter.cpp
@solution exercise1_solution.cpp
```

Everything else should remain ordinary Markdown.

## Images

Use standard relative Markdown:

``` markdown
![Coordinate system](images/coordinates.png)
```

No custom image tag is needed.

Because tutorials are external content, properly formed lesson folders
can be added or edited after build.
