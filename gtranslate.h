#ifndef GTRANSLATE_H
#define GTRANSLATE_H
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QString>
#include <QStringList>

class GTranslate : public QObject
{
    Q_OBJECT
public:
    //GTranslate(const GTranslate &other);
    GTranslate(QObject* parent);
    ~GTranslate();
    void translate(QString textToTranslate);
    void translate(QStringList *textsToTranslate);
    void nextText();

    void writeToFile(QString filename, QString *whatToWtite);

    QString languageFromTo;
    QStringList *texts;
    bool working;
    QStringList translated;

public slots:
    void pageFetched(QNetworkReply* pReply);
signals:
    void translationReady(int index, QString *translatedText);
    void multipleTranslationReady(QStringList *translatedText);

private:
    QNetworkAccessManager* pageRequest;
    QString url;
    int textsCounter, textsTotal;
};

#endif // GTRANSLATE_H
