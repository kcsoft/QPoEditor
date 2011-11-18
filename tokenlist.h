#ifndef TOKENLIST_H
#define TOKENLIST_H

#include <QList>
#include "translatetoken.h"

class TokenList : public QList<TranslateToken>
{
public:
    TokenList();
    void append ( const TranslateToken & value );
    void addToken(QString token, QString filename);
};

#endif // TOKENLIST_H
