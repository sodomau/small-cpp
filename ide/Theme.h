#pragma once

#include <QString>
#include <QPalette>
#include <utility>

// Palette-based rules keep Light/Dark consistent while allowing user QSS
// to override individual controls. No effect on learner program windows.
inline QString smallWindowStyleSheet(const QPalette& palette)
{
    QString style = QStringLiteral(R"(
QWidget { color: palette(window-text); }
QMainWindow, QDialog { background: palette(window); }
QMenuBar { background: palette(window); padding: 4px 8px; }
QMenuBar::item { padding: 6px 12px; border-radius: 6px; }
QMenuBar::item:selected { background: palette(alternate-base); }
QMenu { background: palette(base); border: 1px solid palette(mid); padding: 6px; }
QMenu::item { padding: 7px 28px 7px 12px; border-radius: 5px; }
QMenu::item:selected { background: palette(highlight); color: palette(highlighted-text); }
QMenu::separator { height: 1px; background: palette(mid); margin: 5px 8px; }
QToolBar { background: palette(base); border: none; border-bottom: 1px solid palette(mid); padding: 7px 10px; spacing: 6px; }
QToolButton, QPushButton { background: palette(button); color: palette(button-text); border: 1px solid palette(mid); border-radius: 6px; padding: 6px 12px; }
QToolButton:hover, QPushButton:hover { background: palette(alternate-base); border-color: palette(highlight); }
QToolButton:pressed, QPushButton:pressed { background: palette(highlight); color: palette(highlighted-text); }
QToolButton:disabled, QPushButton:disabled { color: palette(mid); background: palette(window); border-color: palette(window); }
QToolButton#runButton { background: #2563eb; color: white; border-color: #2563eb; font-weight: bold; padding: 6px 20px; }
QToolButton#runButton:hover { background: #1d4ed8; }
QToolButton#runButton:disabled { background: palette(button); color: palette(mid); border-color: palette(mid); }
QTabWidget::pane { border: 1px solid palette(mid); background: palette(base); }
QTabBar { background: palette(window); }
QTabBar::tab { background: palette(window); color: palette(window-text); border: 1px solid transparent; border-bottom: 2px solid transparent; padding: 7px 14px; margin: 3px 2px 0 2px; border-top-left-radius: 6px; border-top-right-radius: 6px; }
QTabBar::tab:selected { background: palette(base); border-bottom: 2px solid #2563eb; }
QTabBar::tab:hover:!selected { background: palette(alternate-base); }
QPlainTextEdit, QTextEdit, QTextBrowser, QTreeWidget, QTableWidget, QLineEdit { background: palette(base); alternate-background-color: palette(alternate-base); color: palette(text); border: 1px solid palette(mid); border-radius: 5px; selection-background-color: palette(highlight); selection-color: palette(highlighted-text); }
QTreeWidget::item, QTableWidget::item { padding: 5px; }
QTreeWidget::item:selected, QTableWidget::item:selected { background: palette(highlight); color: palette(highlighted-text); }
QHeaderView::section { background: palette(button); color: palette(button-text); border: none; border-bottom: 1px solid palette(mid); padding: 7px; }
QGroupBox { border: 1px solid palette(mid); border-radius: 8px; margin-top: 12px; padding-top: 8px; }
QGroupBox::title { subcontrol-origin: margin; left: 12px; padding: 0 5px; }
QSplitter::handle { background: palette(window); }
QStatusBar { background: palette(window); color: palette(window-text); border-top: 1px solid palette(mid); padding: 3px 8px; }
QScrollBar:vertical { background: palette(window); width: 12px; margin: 0; }
QScrollBar::handle:vertical { background: palette(mid); min-height: 24px; border-radius: 5px; margin: 2px; }
QScrollBar:horizontal { background: palette(window); height: 12px; margin: 0; }
QScrollBar::handle:horizontal { background: palette(mid); min-width: 24px; border-radius: 5px; margin: 2px; }
QScrollBar::add-line, QScrollBar::sub-line { width: 0; height: 0; }
QScrollBar::add-page, QScrollBar::sub-page { background: transparent; }
QToolTip { background: palette(base); color: palette(text); border: 1px solid palette(mid); padding: 6px; }
)");
    const std::pair<const char*, QPalette::ColorRole> roles[] = {
        {"window-text", QPalette::WindowText}, {"window", QPalette::Window},
        {"base", QPalette::Base}, {"alternate-base", QPalette::AlternateBase},
        {"mid", QPalette::Mid}, {"highlight", QPalette::Highlight},
        {"highlighted-text", QPalette::HighlightedText}, {"button", QPalette::Button},
        {"button-text", QPalette::ButtonText}, {"text", QPalette::Text}
    };
    for (const auto& role : roles)
        style.replace("palette(" + QString::fromLatin1(role.first) + ")",
                      palette.color(role.second).name());
    return style;
}
