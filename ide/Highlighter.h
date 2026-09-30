#pragma once
#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QVector>

class Highlighter : public QSyntaxHighlighter
{
public:
    explicit Highlighter(QTextDocument* document);
    void setDark(bool dark);
protected:
    void highlightBlock(const QString& text) override;
private:
    struct Rule { QRegularExpression expression; QTextCharFormat format; };
    QVector<Rule> rules_;
    QTextCharFormat string_, comment_;
    void rebuild(bool dark);
};
