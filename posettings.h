#ifndef POSETTINGS_H
#define POSETTINGS_H
#include <QString>
#include <QSettings>
#include <QStringList>
#include "posettingsdata.h"
#include <QList>

class PoSettings
{
public:
    PoSettings();
    void clearGroups();
    bool loadSettings(QString fileName);

    QList<PoSettingsData> groups;
    QString languagePair;
    bool validSettings;
};

#endif // POSETTINGS_H
