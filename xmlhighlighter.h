// xmlhighlighter.h
#ifndef XMLHIGHLIGHTER_H
#define XMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QVector>

class XMLHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    explicit XMLHighlighter(QTextDocument *parent = nullptr);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    void setupFormats();
};

#endif // XMLHIGHLIGHTER_H
