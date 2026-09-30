# Qt references used for the tutorial implementation

The implementation uses the existing Qt Widgets/Gui/Core modules, not Qt WebEngine.

- Modeless QDialog lifecycle and `show()`:
  https://doc.qt.io/qt-6/qdialog.html
- QScrollArea widget ownership and resizable content:
  https://doc.qt.io/qt-6/qscrollarea.html
- QTextDocument Markdown parsing, MarkdownNoHTML and default font:
  https://doc.qt.io/qt-6/qtextdocument.html
- Local QSettings storage:
  https://doc.qt.io/qt-6/qsettings.html
- Resource collection embedding and Q_INIT_RESOURCE for static libraries:
  https://doc.qt.io/qt-6/resources.html

These are API references, not claims that the new Qt GUI was executed in the
artifact-generation environment. See VALIDATION_v0.27.md for actual results.
