#include "EntryPoint.h"

#include <QStringView>
#include <QVector>

namespace
{
enum class Kind { Identifier, Symbol };
struct Token { Kind kind; QString text; int depth; };

QVector<Token> Lex(const QString& source)
{
    QVector<Token> out;
    int depth = 0;
    const int n = source.size();
    bool lineStart = true;
    for (int i = 0; i < n;)
    {
        const QChar c = source[i];

        if (c == '\n') { ++i; lineStart = true; continue; }
        if (c.isSpace()) { ++i; continue; }

        // Ignore preprocessor directives, including backslash continuations.
        if (lineStart && c == '#')
        {
            do {
                int end = source.indexOf('\n', i);
                if (end < 0) return out;
                int k = end - 1;
                while (k >= i && (source[k] == ' ' || source[k] == '\t' || source[k] == '\r')) --k;
                const bool continued = k >= i && source[k] == '\\';
                i = end + 1;
                if (!continued) break;
            } while (i < n);
            lineStart = true;
            continue;
        }
        lineStart = false;

        if (c == '/' && i + 1 < n && source[i + 1] == '/')
        {
            int end = source.indexOf('\n', i + 2);
            i = end < 0 ? n : end;
            continue;
        }
        if (c == '/' && i + 1 < n && source[i + 1] == '*')
        {
            int end = source.indexOf("*/", i + 2);
            i = end < 0 ? n : end + 2;
            continue;
        }

        // Ordinary and prefixed string/character literals. For entry-point
        // detection it is enough to skip their contents safely.
        int quoteAt = i;
        if ((c == 'u' || c == 'U' || c == 'L') && i + 1 < n &&
            (source[i + 1] == '"' || source[i + 1] == '\''))
            quoteAt = i + 1;
        else if (c == 'u' && i + 2 < n && source[i + 1] == '8' &&
                 (source[i + 2] == '"' || source[i + 2] == '\''))
            quoteAt = i + 2;
        if (source[quoteAt] == '"' || source[quoteAt] == '\'')
        {
            const QChar quote = source[quoteAt];
            i = quoteAt + 1;
            while (i < n)
            {
                if (source[i] == '\\') { i += qMin(2, n - i); continue; }
                if (source[i] == quote) { ++i; break; }
                ++i;
            }
            continue;
        }

        if (c.isLetter() || c == '_')
        {
            const int start = i++;
            while (i < n && (source[i].isLetterOrNumber() || source[i] == '_')) ++i;
            out.push_back({Kind::Identifier, source.mid(start, i - start), depth});
            continue;
        }

        if (c == '{') { out.push_back({Kind::Symbol, "{", depth}); ++depth; ++i; continue; }
        if (c == '}') { depth = qMax(0, depth - 1); out.push_back({Kind::Symbol, "}", depth}); ++i; continue; }
        out.push_back({Kind::Symbol, QString(c), depth});
        ++i;
    }
    return out;
}

bool HasTopLevelMainDefinition(const QVector<Token>& tokens, const QString& name = "main")
{
    for (int i = 0; i < tokens.size(); ++i)
    {
        if (tokens[i].depth != 0 || tokens[i].kind != Kind::Identifier || tokens[i].text != name)
            continue;
        if (i + 1 >= tokens.size() || tokens[i + 1].text != "(") continue;

        int parens = 0;
        int j = i + 1;
        for (; j < tokens.size(); ++j)
        {
            if (tokens[j].text == "(") ++parens;
            else if (tokens[j].text == ")" && --parens == 0) { ++j; break; }
        }
        if (parens != 0) continue;

        // Skip common post-parameter specifiers. A declaration ending in ';'
        // is not an entry-point definition; a following '{' is.
        for (; j < tokens.size() && tokens[j].depth == 0; ++j)
        {
            if (tokens[j].text == "{") return true;
            if (tokens[j].text == ";") break;
        }
    }
    return false;
}
}

SmallEntryPoint DetectEntryPoint(const QString& source)
{
    return HasTopLevelMainDefinition(Lex(source)) ? SmallEntryPoint::Main
                                                   : SmallEntryPoint::SmallMain;
}

QStringList DefinedEntryPoints(const QString& source)
{
    const auto tokens = Lex(source);
    QStringList result;
    if (HasTopLevelMainDefinition(tokens)) result << "main";
    if (HasTopLevelMainDefinition(tokens, "SmallMain")) result << "SmallMain";
    return result;
}
