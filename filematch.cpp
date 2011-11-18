#include "filematch.h"
#include <QDebug>

FileMatch::FileMatch()
{
}

FileMatch::FileMatch(QString FileName, QString RegularExpression, TokenList *tokenList){
    fileName = FileName;
    regularExpression = RegularExpression;

    regExpr = QRegExp(regularExpression);
    QFile textFile(fileName);
    if (textFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream textStream(&textFile);
        QString line;
        int i, lineNumber = 0;
        while (!textStream.atEnd())
        {
            line = textStream.readLine();
            lineNumber++;
            i = 0;
            while ((i = regExpr.indexIn(line,i))!= -1){
                i += regExpr.matchedLength();
                tokenList->addToken(regExpr.cap(1), fileName+":"+QString::number(lineNumber));
                //qDebug()<<fileName<<":"<<lineNumber<<regExpr.cap(1);
            }
        }
        textFile.close();
    }
}

FileMatch::FileMatch(QString FileName, QStringList RegularExpressions, TokenList *tokenList){
    fileName = FileName;

    QFile textFile(fileName);
    if (textFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream textStream(&textFile);
        QString line;
        int i, lineNumber = 0;
        while (!textStream.atEnd())
        {
            line = textStream.readLine();
            lineNumber++;
            for (int r=0;r<RegularExpressions.length();r++){
                i = 0;
                regExpr = QRegExp(RegularExpressions.at(r));
                while ((i = regExpr.indexIn(line,i))!= -1){
                    i += regExpr.matchedLength();
                    tokenList->addToken(regExpr.cap(1), fileName+":"+QString::number(lineNumber));
                }
            }
        }
        textFile.close();
    }
}
