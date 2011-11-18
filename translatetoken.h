#ifndef TRANSLATETOKEN_H
#define TRANSLATETOKEN_H

#include <QString>
#include <QStringList>

class TranslateToken
{
public:
    TranslateToken();
    QString originalPhrase;
    QString translatedPhrase;
    QStringList inFile;
};

#endif // TRANSLATETOKEN_H
