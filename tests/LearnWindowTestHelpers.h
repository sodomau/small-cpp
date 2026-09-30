#pragma once
#include <QApplication>
#include <QEvent>

// Learn windows are intentionally top-level, not QObject children of MainWindow.
template<class T> T* learnWindow()
{
    for (auto* widget : QApplication::topLevelWidgets())
        if (auto* window = qobject_cast<T*>(widget)) return window;
    return nullptr;
}

template<class T> int learnWindowCount()
{
    int count = 0;
    for (auto* widget : QApplication::topLevelWidgets())
        if (qobject_cast<T*>(widget)) ++count;
    return count;
}
