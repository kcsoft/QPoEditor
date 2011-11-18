#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qpoeditor.h"
#include "dirlistfiles.h"
#include <QDebug>
#include "filematch.h"
#include "gtranslate.h"
#include "tokenlist.h"
#include "posettings.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_actionSelect_path_triggered();
    void on_actionUpdate_from_files_triggered();
    void on_actionTranslate_triggered();
    void onTranslate(int index,QString *str);

    void on_actionOpen_project_file_triggered();

    void on_actionAbout_triggered();

    void on_actionAbout_Qt_triggered();

private:
    Ui::MainWindow *ui;
    QPoEditor *editor;
    GTranslate *gTranslate;
    QStringList tokenList;
    PoSettings posettings;
    TokenList tokens;
};

#endif // MAINWINDOW_H
