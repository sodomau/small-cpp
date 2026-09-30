#pragma once
#include <QPlainTextEdit>
#include <QSet>

class LineArea;
class CodeEditor : public QPlainTextEdit
{
    friend class LineArea;
    Q_OBJECT
public:
    explicit CodeEditor(QWidget* parent = nullptr);
    int lineAreaWidth() const;
    void paintLineArea(QPaintEvent* event);
    void markErrorLine(int line);
    void clearError();
    void setDarkTheme(bool dark);
    const QSet<int>& breakpoints() const { return breakpoints_; }
    void setDebugLine(int line);
    void clearDebugLine();
    void setDebugGutterEnabled(bool enabled);
signals:
    void breakpointsChanged();
protected:
    void resizeEvent(QResizeEvent* event) override;
    void changeEvent(QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
private:
    QWidget* area_;
    int errorLine_ = -1;
    int debugLine_ = -1;
    QSet<int> breakpoints_;
    bool darkTheme_ = false;
    bool debugGutterEnabled_ = true;
    void updateMargin();
    void updateMarks();
    void indentSelection(bool remove);
};
