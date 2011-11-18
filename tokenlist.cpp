#include "tokenlist.h"

TokenList::TokenList()
{
}

void TokenList::append(const TranslateToken &value)
{
    bool exist = false;
    for (int i=0;i<this->length();i++){
        if (this->at(i).originalPhrase.compare(value.originalPhrase) ==0 ){
            //must verify is file is not already there
            this->operator [](i).inFile.append(value.inFile);
            //for (int j=0;j<value.inFile.length();j++)
                //at(i).inFile.append(value.inFile.at(j));
            exist = true;
            break;
        }
    }
    if (!exist)
        QList<TranslateToken>::append(value);
}

void TokenList::addToken(QString token, QString filename)
{
    TranslateToken t;
    t.originalPhrase = token;
    t.inFile.append(filename);
    this->append(t);
}
