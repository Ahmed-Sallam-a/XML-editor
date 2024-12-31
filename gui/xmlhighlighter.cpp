// xmlhighlighter.cpp
#include "xmlhighlighter.h"

XMLHighlighter::XMLHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent) {
    setupFormats();
}

void XMLHighlighter::setupFormats() {
    HighlightingRule rule;

    // Tags format (like <tag>, </tag>)
    QTextCharFormat tagFormat;
    tagFormat.setForeground(Qt::darkCyan);
    tagFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression(QStringLiteral("(<[!?]?\\w+(?=\\s|>|/>)[^>]*>|</\\w+>)"));
    rule.format = tagFormat;
    highlightingRules.append(rule);

    // Attributes format (like attribute=)
    QTextCharFormat attributeFormat;
    attributeFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression(QStringLiteral("\\s+\\w+(?=\\s*=)"));
    rule.format = attributeFormat;
    highlightingRules.append(rule);

    // Values format (like "value")
    QTextCharFormat valueFormat;
    valueFormat.setForeground(Qt::darkRed);
    rule.pattern = QRegularExpression(QStringLiteral("\"[^\"]*\""));
    rule.format = valueFormat;
    highlightingRules.append(rule);

    // Comments format (<!-- comment -->)
    QTextCharFormat commentFormat;
    commentFormat.setForeground(Qt::gray);
    rule.pattern = QRegularExpression(QStringLiteral("<!--[^>]*-->"));
    rule.format = commentFormat;
    highlightingRules.append(rule);
}

void XMLHighlighter::highlightBlock(const QString &text) {
    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
