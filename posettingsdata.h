#ifndef POSETTINGSDATA_H
#define POSETTINGSDATA_H

#include <QString>
#include <QStringList>

class PoSettingsData
{
public:
    PoSettingsData();
    QStringList filters;
    QStringList regexps;

};

#endif // POSETTINGSDATA_H
