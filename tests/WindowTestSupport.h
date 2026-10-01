#pragma once
#include "MainWindow.h"
#include <QAction>

// Document tests explicitly enter editing mode; startup is covered separately.
inline void OpenNewProgram(MainWindow& window)
{
    window.findChild<QAction*>("actionCloseTab")->trigger();
    window.findChild<QAction*>("actionNew")->trigger();
}
