#include "Highlighter.h"
#include <QApplication>
#include <QPalette>
#include <QFont>

Highlighter::Highlighter(QTextDocument* document) : QSyntaxHighlighter(document)
{
    rebuild(QApplication::palette().base().color().lightness() < 128);
}

void Highlighter::setDark(bool dark)
{
    rebuild(dark);
    rehighlight();
}

void Highlighter::rebuild(bool dark)
{
    rules_.clear();
    auto add = [&](const QString& regex, const QColor& color, bool bold = false) {
        QTextCharFormat format;
        format.setForeground(color);
        if (bold) format.setFontWeight(QFont::Bold);
        rules_.append({QRegularExpression(regex), format});
    };
    add(R"(\b(alignas|alignof|auto|bool|break|case|catch|char|class|const|constexpr|continue|default|delete|do|double|else|enum|explicit|extern|false|float|for|friend|if|inline|int|long|namespace|new|noexcept|nullptr|operator|private|protected|public|return|short|signed|sizeof|static|struct|switch|template|this|throw|true|try|typedef|typename|union|unsigned|using|virtual|void|volatile|while)\b)",
        dark ? QColor("#93b8ff") : QColor("#234b91"), true);
    add(R"(\b(String|Array|File|FileMode|Window|Color|StopWatch|Timer|Key|MouseButton|Sound)\b)",
        dark ? QColor("#d6a4ef") : QColor("#83409a"), true);
    add(R"(\b(SmallMain|Format|Print|Write|Input|InputInt|InputReal|RGB|PlaySound|PlaySoundAndWait|Beep|BeepAndWait|Sleep)\b)",
        dark ? QColor("#69d1d4") : QColor("#006c78"));
    add(R"(\b\d+(?:\.\d+)?(?:[eE][+-]?\d+)?[fFlLuU]*\b)",
        dark ? QColor("#edb77f") : QColor("#975100"));
    string_.setForeground(dark ? QColor("#ace09b") : QColor("#27722f"));
    comment_.setForeground(dark ? QColor("#939baa") : QColor("#777f89"));
}

void Highlighter::highlightBlock(const QString& text)
{
    for (const Rule& rule : rules_) {
        auto matches = rule.expression.globalMatch(text);
        while (matches.hasNext()) { auto match = matches.next(); setFormat((int)match.capturedStart(), (int)match.capturedLength(), rule.format); }
    }
    bool inComment = previousBlockState() == 1; setCurrentBlockState(0); int i = 0;
    while (i < text.size()) {
        if (inComment) { int end=(int)text.indexOf("*/",i); if(end<0){setFormat(i,(int)text.size()-i,comment_);setCurrentBlockState(1);return;} setFormat(i,end+2-i,comment_);i=end+2;inComment=false; }
        else if(text.mid(i,2)=="//"){setFormat(i,(int)text.size()-i,comment_);return;}
        else if(text.mid(i,2)=="/*"){int start=i,end=(int)text.indexOf("*/",i+2);if(end<0){setFormat(start,(int)text.size()-start,comment_);setCurrentBlockState(1);return;}setFormat(start,end+2-start,comment_);i=end+2;}
        else if(text[i]=='"'||text[i]=='\''){QChar quote=text[i];int start=i++;while(i<text.size()){if(text[i]=='\\'){i=qMin(i+2,(int)text.size());continue;}if(text[i++]==quote)break;}setFormat(start,i-start,string_);}
        else ++i;
    }
}
