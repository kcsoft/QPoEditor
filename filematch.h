#ifndef FILEMATCH_H
#define FILEMATCH_H
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegExp>
#include "tokenlist.h"

class FileMatch
{
public:
    FileMatch();
    FileMatch(QString FileName, QString RegularExpression, TokenList *tokenList);
    FileMatch(QString FileName, QStringList RegularExpressions, TokenList *tokenList);
    QString fileName;
    QString regularExpression;
    QStringList foundExpressions;
    QRegExp regExpr;
};

#endif // FILEMATCH_H
