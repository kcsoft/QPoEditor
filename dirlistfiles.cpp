#include "dirlistfiles.h"

DirListFiles::DirListFiles()
{
}

void DirListFiles::exec(QString path)
{
    if (filters.length()<=0) return;
    if (!QFile::exists(path)) return;
    fileList.clear();
    recursiveSearch(path);
}

void DirListFiles::recursiveSearch(QString path)
{
    QDir dir = QDir(path);
    QStringList files = dir.entryList(filters, QDir::Files, QDir::NoSort);
    for (int j=0;j<files.length();j++)
        fileList.append(path+"/"+files.at(j));
    QStringList subDirs = dir.entryList(filters, QDir::AllDirs, QDir::NoSort);
    for (int i=0;i<subDirs.length();i++){
        if ((subDirs.at(i).compare(".") !=0 ) && (subDirs.at(i).compare("..") !=0 )){
            recursiveSearch(path+"/"+subDirs.at(i));
        }
    }
}
