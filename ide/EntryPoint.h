#pragma once
#include <QString>

enum class SmallEntryPoint
{
    SmallMain,
    Main
};

// Lightweight C++ lexical scan. Comments, strings, character literals,
// preprocessor lines and nested scopes do not masquerade as a top-level main.
SmallEntryPoint DetectEntryPoint(const QString& source);
