#include "RuntimeDiagnostics.h"
#include <QRegularExpression>
#include <QStringList>

namespace {
int uniqueLineContaining(const QStringList& lines, const QRegularExpression& re)
{
    int found = 0;
    for (int i = 0; i < lines.size(); ++i) {
        if (re.match(lines[i]).hasMatch()) {
            if (found != 0) return 0; // ambiguous: don't pretend we know the line
            found = i + 1;
        }
    }
    return found;
}
}

SmallRuntimeDiagnostic ExplainRuntimeError(const QString& raw, const QString& source)
{
    SmallRuntimeDiagnostic d;
    QString message = raw.trimmed();
    message.remove(QRegularExpression(R"(^Runtime error:\s*)"));
    const QStringList lines = source.split('\n');
    QString title = "Runtime error";
    QString explanation = message;
    QString suggestion;

    auto m = QRegularExpression(R"(^Array index (-?\d+) is out of range\. Length: (\d+)\.$)").match(message);
    if (m.hasMatch()) {
        const int index = m.captured(1).toInt(), length = m.captured(2).toInt();
        title = "Array index out of range";
        explanation = QString("Index %1 was used, but this Array has %2 elements.").arg(index).arg(length);
        suggestion = length == 0 ? "This Array is empty, so it has no valid index."
                                 : QString("Valid indices are 0 to %1.").arg(length - 1);
        d.line = uniqueLineContaining(lines, QRegularExpression(QString(R"(\[\s*%1\s*\])").arg(index)));
    }
    else if ((m = QRegularExpression(R"(^String index (-?\d+) is out of range\. Length: (\d+)\.$)").match(message)).hasMatch()) {
        const int index = m.captured(1).toInt(), length = m.captured(2).toInt();
        title = "String index out of range";
        explanation = QString("Index %1 was used, but this String has %2 characters.").arg(index).arg(length);
        suggestion = length == 0 ? "This String is empty, so it has no valid index."
                                 : QString("Valid indices are 0 to %1.").arg(length - 1);
        d.line = uniqueLineContaining(lines, QRegularExpression(QString(R"(\[\s*%1\s*\])").arg(index)));
    }
    else if (message == "Substring start index is out of range.") {
        title = "Substring start is out of range";
        explanation = "The starting position is outside this String.";
        suggestion = "Use a start position from 0 through the String's Length().";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\.Substring\s*\()"));
    }
    else if (message == "Substring extends beyond the String.") {
        title = "Substring is too long";
        explanation = "The requested substring goes past the end of the String.";
        suggestion = "Reduce the start position or the substring length.";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\.Substring\s*\()"));
    }
    else if (message == "Array length cannot be negative.") {
        title = "Invalid Array length"; explanation = "An Array cannot have a negative length.";
        suggestion = "Use zero or a positive integer for the Array length.";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\bArray\s*<[^>]+>\s+\w+\s*\()"));
    }
    else if (message == "Color values must be between 0 and 255.") {
        title = "Invalid color value"; explanation = "Each RGB value must be between 0 and 255.";
        suggestion = "For example: RGB(255, 128, 0)";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\bRGB\s*\()"));
    }
    else if (message == "The Window is not open. Call Open(width, height) first.") {
        title = "Window is not open"; explanation = "This operation needs an open Window.";
        suggestion = "Call window.Open(width, height) before drawing or showing the Window.";
    }
    else if (message == "Window width and height must be positive.") {
        title = "Invalid Window size"; explanation = "Window width and height must both be greater than zero.";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\.Open\s*\()"));
    }
    else if (message == "Pixel position is outside the Window.") {
        title = "Pixel is outside the Window"; explanation = "SetPixel was given a position outside the Window.";
        suggestion = "x must be from 0 to Width()-1 and y from 0 to Height()-1.";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\.SetPixel\s*\()"));
    }
    else if (message == "Rectangle size cannot be negative.") {
        title = "Invalid rectangle size"; explanation = "Rectangle width and height cannot be negative.";
        suggestion = "Use zero or positive values for width and height.";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\.(?:DrawRectangle|FillRectangle)\s*\()"));
    }
    else if (message == "Circle radius cannot be negative.") {
        title = "Invalid circle radius"; explanation = "A circle radius cannot be negative.";
        suggestion = "Use zero or a positive radius.";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\.(?:DrawCircle|FillCircle)\s*\()"));
    }
    else if (message == "Text size must be positive.") {
        title = "Invalid text size"; explanation = "Text size must be greater than zero.";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\.DrawText\s*\()"));
    }
    else if (message == "Sleep duration must be a non-negative, finite number.") {
        title = "Invalid Sleep duration"; explanation = "Sleep needs a finite duration of zero seconds or more.";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\bSleep\s*\()"));
    }
    else if (message == "Timer interval must be a positive, finite number.") {
        title = "Invalid Timer interval"; explanation = "A Timer interval must be a finite number greater than zero.";
        suggestion = "For example: timer.Start(1.0, OnTimer);";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\.Start\s*\()"));
    }
    else if (message == "Timer callback cannot be empty.") {
        title = "Timer callback is missing"; explanation = "Timer.Start needs a function to call when the timer fires.";
        suggestion = "For example: timer.Start(1.0, OnTimer);";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\.Start\s*\()"));
    }
    else if (message.startsWith("Beep frequency and duration must be positive")) {
        title = "Invalid Beep"; explanation = "Beep needs a positive frequency and a positive duration.";
        suggestion = "For example: Beep(440, 0.5);";
        d.line = uniqueLineContaining(lines, QRegularExpression(R"(\b(?:Beep|BeepAndWait)\s*\()"));
    }
    else if (message == "Input ended before a value was entered.") {
        title = "Input ended"; explanation = "The program asked for input, but no more input was available.";
    }

    d.text = title + "\n\n";
    if (d.line > 0) {
        d.text += QString("Likely source line %1\n    %2\n\n").arg(d.line).arg(lines.value(d.line - 1));
        d.text += "This line is inferred because it is the only matching operation in the program.\n\n";
    }
    d.text += explanation.isEmpty() ? "The program stopped because of an error." : explanation;
    if (!suggestion.isEmpty()) d.text += "\n\n" + suggestion;
    return d;
}
