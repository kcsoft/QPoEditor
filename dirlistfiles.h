#ifndef DIRLISTFILES_H
#define DIRLISTFILES_H
#include <QStringList>
#include <QDir>
#include <QFile>

class DirListFiles
{
public:
    DirListFiles();
    QStringList filters;
    QStringList fileList;
    void exec(QString path);
    void recursiveSearch(QString path);
};

#endif // DIRLISTFILES_H
