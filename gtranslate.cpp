#include "gtranslate.h"
#include <QDebug>
#include <QUrl>

/*GTranslate::GTranslate(const GTranslate &other)
{
}*/
GTranslate::~GTranslate()
{
    delete pageRequest;
}

GTranslate::GTranslate(QObject* parent) : QObject(parent)
{
    pageRequest = new QNetworkAccessManager(this);
    working = false;
}
void GTranslate::pageFetched(QNetworkReply* pReply)
{

    QByteArray data=pReply->readAll();
    QString str(data);
    //writeToFile("h:/page.html", &str);
    int i,j;
    if ((i=str.indexOf("result_box")) >=0 ){
        if ((i=str.indexOf(">", i+1)) >=0 ){
            if ((j=str.indexOf("</div>", i+1)) >=0 ){
                str = str.mid(i+1, j-i-1);
                str.replace( QRegExp("<[^>]*>"), "" );
                translationReady(textsCounter, &str);
                translated.append(str);
            }
        }
        working = false;
        textsCounter++;
        nextText();
    }
}

void GTranslate::translate(QString textToTranslate)
{
    url = "http://translate.google.com/?hl=en&ie=UTF8&langpair="+languageFromTo+"&text="+textToTranslate;
    connect(pageRequest, SIGNAL(finished(QNetworkReply*)), this, SLOT(pageFetched(QNetworkReply*)));
    textsCounter = 0;
    textsTotal = 0;
    working = true;
    translated.clear();
    pageRequest->get(QNetworkRequest(QUrl(url)));
}

void GTranslate::translate(QStringList *textsToTranslate)
{
    texts = textsToTranslate;
    textsCounter = 0;
    textsTotal = texts->length();
    translated.clear();
    nextText();
}

void GTranslate::nextText()
{
    if (textsCounter < textsTotal){
        url = "http://translate.google.com/?hl=en&ie=UTF8&langpair="+languageFromTo+"&text="+texts->at(textsCounter);
        connect(pageRequest, SIGNAL(finished(QNetworkReply*)),this, SLOT(pageFetched(QNetworkReply*)));
        pageRequest->get(QNetworkRequest(QUrl(url)));
        working = true;
    }else{

    }
}

void GTranslate::writeToFile(QString filename, QString *whatToWtite)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << *whatToWtite;
        file.close();
    }
}

