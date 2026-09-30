#include "Diagnostics.h"
#include <QFileInfo>
#include <QRegularExpression>
#include <QStringList>

SmallDiagnostic ExplainDiagnostic(const QString& raw, const QString& source,
                                 const QString& sourceFile)
{
    SmallDiagnostic result;
    QString clean = raw;
    clean.replace(QRegularExpression("\\x1b\\[[0-9;]*[A-Za-z]"), "");
    clean.replace(QChar(0x2018), QChar('\''));
    clean.replace(QChar(0x2019), QChar('\''));

    const QString fileName = QFileInfo(sourceFile).fileName();
    QRegularExpression location(QRegularExpression::escape(fileName) +
        R"(:(\d+):(\d+):\s*(?:fatal\s+)?error:\s*([^\r\n]+))");
    const auto match = location.match(clean);
    QString message;
    if (!fileName.isEmpty() && match.hasMatch())
    {
        result.line = match.captured(1).toInt();
        result.column = match.captured(2).toInt();
        message = match.captured(3).trimmed();
    }
    else
    {
        auto any = QRegularExpression(R"((?:fatal\s+)?error:\s*([^\r\n]+))").match(clean);
        message = any.hasMatch() ? any.captured(1).trimmed() : clean.trimmed();
    }

    const QStringList lines = source.split('\n');
    QString title = "Build error";
    QString explanation = message;
    QString suggestion;

    // Be conservative: inspect a simple declaration immediately before the
    // reported location, not arbitrary multiline C++ expressions.
    bool missingDeclarationSemicolon = false;
    if (result.line > 1 &&
        (message.contains("expected initializer before") || message.contains("expected ',' or ';'")))
    {
        const QString previous = lines.value(result.line - 2).trimmed();
        const QRegularExpression declaration(
            R"(^(?:int|double|bool|char|String|Window|Color|StopWatch|Array\s*<\s*\w+\s*>)\s+[A-Za-z_]\w*\s*(?:=\s*[^;{}]+)?$)");
        if (declaration.match(previous).hasMatch())
        {
            --result.line;
            result.column = static_cast<int>(lines.value(result.line - 1).size()) + 1;
            missingDeclarationSemicolon = true;
        }
    }

    if (missingDeclarationSemicolon || message.contains("expected ';'"))
    {
        title = "Missing semicolon";
        explanation = missingDeclarationSemicolon ? "This declaration needs a ';' at its end."
                                                  : "A semicolon ';' is missing near this location.";
        suggestion = "Check the end of this statement and the previous statement.";
    }
    else if (message.contains("suggest parentheses around assignment used as truth value") ||
             message.contains("using the result of an assignment as a condition"))
    {
        title = "Assignment used as a condition";
        explanation = "This condition uses '=' which assigns a value.";
        suggestion = "If you meant to compare two values, use '==' instead.";
    }
    else if (message.contains("expected '(' before") &&
             result.line > 0 &&
             (lines.value(result.line - 1).trimmed().startsWith("if ") ||
              lines.value(result.line - 1).trimmed().startsWith("while ")))
    {
        title = "Missing parentheses around condition";
        explanation = "if and while conditions must be written inside ( ).";
        suggestion = "For example: if (x > 10)";
    }
    else if (message.contains("expected ']'"))
    {
        title = "Missing closing bracket";
        explanation = "An index opened with '[' needs a matching ']'.";
    }
    else if (message.contains("expected '{'"))
    {
        title = "Missing opening brace";
        explanation = "A block needs an opening '{' here.";
    }
    else if (message.contains("expected ',' or ';' before '}'"))
    {
        title = "Missing semicolon";
        explanation = "The statement before this closing brace needs a ';'.";
        suggestion = "Check the previous line.";
    }
    else if (message.contains("was not declared in this scope") || message.contains("has not been declared"))
    {
        const auto name = QRegularExpression("'([^']+)'").match(message);
        title = "Unknown name";
        explanation = name.hasMatch() ? "'" + name.captured(1) + "' has not been declared." : message;
        suggestion = "Check the spelling and where the name is declared.";
    }
    else if (message.contains("operator[]"))
    {
        title = "Invalid index or indexing operation";
        explanation = "This value cannot be used with [ ] in that way.";
        suggestion = "For Array and String, use an integer index inside [ ].";
    }
    else if (message.contains("invalid conversion") || message.contains("cannot convert") ||
             message.contains("conversion from") || message.contains("cannot initialize"))
    {
        title = "Type mismatch";
        explanation = "The value's type does not match the type expected here.";
        suggestion = "Check the variable or parameter type and the value supplied.";
    }
    else if (message.contains("no matching function for call"))
    {
        title = "Function arguments do not match";
        explanation = "This function cannot accept the arguments you supplied.";
        suggestion = "Check both the number and the types of the arguments. In the editor, look at the function name and compare your call with an earlier working example.";
    }
    else if (message.contains("too few arguments"))
    {
        title = "Not enough arguments";
        explanation = "The function requires more arguments.";
    }
    else if (message.contains("too many arguments"))
    {
        title = "Too many arguments";
        explanation = "The function was given more arguments than it accepts.";
    }
    else if (message.contains("expected '}'"))
    {
        title = "Missing closing brace";
        explanation = "A block opened with '{' still needs its closing '}'.";
    }
    else if (message.contains("expected ')'"))
    {
        title = "Missing closing parenthesis";
        explanation = "An opening '(' needs a matching ')'.";
    }
    else if (message.contains("expected primary-expression"))
    {
        title = "Incomplete expression";
        explanation = "A value or expression is missing here.";
    }
    else if (message.contains("else without a previous if"))
    {
        title = "else without matching if";
        explanation = "This else does not have an if that it can belong to.";
        suggestion = "Check the braces and the if statement immediately before this else.";
    }
    else if (message.contains("break statement not within loop") || message.contains("break statement not within loop or switch"))
    {
        title = "break used outside a loop";
        explanation = "break can only be used inside a loop in Small C++.";
        suggestion = "Move this break inside a for or while loop, or remove it.";
    }
    else if (message.contains("continue statement not within a loop"))
    {
        title = "continue used outside a loop";
        explanation = "continue can only be used inside a loop.";
        suggestion = "Move this continue inside a for or while loop, or remove it.";
    }
    else if (message.contains("has no member named"))
    {
        const auto member = QRegularExpression(R"(has no member named ['`]([^'`]+)['`])").match(message);
        title = "Unknown member";
        explanation = member.hasMatch() ? "This object has no member named '" + member.captured(1) + "'." : message;
        suggestion = "Check the spelling and the object's available functions or values.";
    }
    else if (message.contains("is private within this context") || message.contains("is private"))
    {
        title = "Private member cannot be used here";
        explanation = "This member belongs to the private part of the class.";
        suggestion = "Use the class's public interface instead.";
    }
    else if (message.contains("invalid operands") || message.contains("no match for 'operator"))
    {
        title = "Operator cannot be used with these values";
        explanation = "These two value types cannot be used with this operator.";
        suggestion = "Check the types on both sides of the operator.";
    }
    else if (message.contains("expected unqualified-id"))
    {
        title = "Unexpected code here";
        explanation = "C++ found something here that cannot appear in this position.";
        suggestion = "Check the previous line for a missing brace, parenthesis, or semicolon.";
    }
    else if (message.contains("does not name a type"))
    {
        title = "Unknown type";
        explanation = "C++ does not know this type name.";
        suggestion = "Check the spelling, or make sure the type is declared before it is used.";
    }
    else if (message.contains("cannot be used as a function"))
    {
        title = "This name is not a function";
        explanation = "The name before ( ) is not a function that can be called.";
        suggestion = "Check whether you meant to use the value directly instead of calling it.";
    }
    else if (message.contains("redefinition of") || message.contains("redeclaration of"))
    {
        title = "Name already defined";
        explanation = "This name was already defined in this scope.";
    }
    else if (message.contains("return-statement"))
    {
        title = "Wrong return value";
        explanation = "The return statement does not match the function's return type.";
    }
    else if (clean.contains("undefined reference to") && clean.contains("SmallMain()"))
    {
        title = "SmallMain is missing";
        explanation = "The program needs a function named SmallMain with no parameters and no return value.";
        suggestion = "void SmallMain()\n{\n    // Your program\n}";
    }

    result.text = title + "\n\n";
    if (result.line > 0)
    {
        result.text += QString("Line %1, column %2\n").arg(result.line).arg(result.column);
        const QString code = lines.value(result.line - 1);
        result.text += "    " + code + '\n';
        const int column = qBound(0, result.column - 1, static_cast<int>(code.size()));
        result.text += "    " + QString(column, ' ') + "^\n\n";
    }
    result.text += explanation.isEmpty() ? "The program could not be built." : explanation;
    if (!suggestion.isEmpty()) result.text += "\n\n" + suggestion;
    result.text += "\n\nUse \"Show C++ Error\" for the original compiler output.";
    return result;
}
