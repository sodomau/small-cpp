# small_main and main

Small C++ supports two entry styles in the same IDE.

## Beginner entry

```cpp
void small_main()
{
    print("Hello");
}
```

The IDE links `small_entry`, whose real `main()` initializes Small and calls `small_main()`.

## Learner-owned C++ entry

```cpp
int main()
{
    initialize_small();

    print("Hello");
    return 0;
}
```

or:

```cpp
int main(int argc, char* argv[])
{
    initialize_small(argc, argv);
    return 0;
}
```

The IDE detects a real top-level `main()` lexically and does not link `small_entry`. It still links `small_runtime`, so the full Small API remains available after `initialize_small()`.

A source containing both uses the explicit `main()`. `small_main()` is then just an ordinary uncalled function unless the learner calls it.

Comments, strings, declarations of `main`, and nested functions named `main` do not select this path.

A completely ordinary standard C++ `main()` also works without calling `initialize_small()` when no Small runtime facilities requiring initialization are used.
