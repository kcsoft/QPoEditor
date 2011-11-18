#include "posettings.h"
#include <QDebug>

PoSettings::PoSettings()
{
    validSettings = false;
}

bool PoSettings::loadSettings(QString fileName)
{
    clearGroups();
    QSettings settings(fileName, QSettings::IniFormat);
    languagePair = settings.value("LanguagePair", "en|en").toString();
    QStringList groupNames = settings.childGroups();
    for (int i=0;i<groupNames.length();i++){
        if (groupNames.at(i).startsWith("FileGroup")){
            settings.beginGroup(groupNames.at(i));
            QStringList keys = settings.childKeys();
            PoSettingsData oneGroup;
            for (int j=0;j<keys.length();j++){
                QString keyvalue = settings.value(keys.at(j),"").toString();
                if (keys.at(j).startsWith("filter")){
                    oneGroup.filters.append(keyvalue);
                }else
                if (keys.at(j).startsWith("regexp")){
                    oneGroup.regexps.append(keyvalue);
                }
            }
            groups.append(oneGroup);
            settings.endGroup();
        }
    }
    validSettings = (groups.length()>0);
    return validSettings;
}

void PoSettings::clearGroups()
{
    for (int i=0;i<groups.length();i++){
        groups.operator [](i).filters.clear();
        groups.operator [](i).regexps.clear();
    }
    groups.clear();
}

