#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    editor = new QPoEditor();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete editor;
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionSelect_path_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    if (dialog.exec()){
        if (dialog.selectedFiles().length() == 1){
            editor->searchPath = dialog.selectedFiles()[0];
            //ui->pathLabel->setText(editor->searchPath);
        }
    }
}

void MainWindow::on_actionUpdate_from_files_triggered()
{
    if (posettings.validSettings){
        ui->textWindow->clear();
        tokens.clear();
        for (int k=0;k<posettings.groups.length();k++){
            DirListFiles dl = DirListFiles();
            dl.filters.clear();
            dl.filters.append(posettings.groups.operator [](k).filters);
            dl.exec(editor->searchPath);
            FileMatch fm;
            for (int i=0;i<dl.fileList.length();i++){
                fm = FileMatch(dl.fileList.at(i), posettings.groups.operator [](k).regexps, &tokens);
                //qDebug()<<dl.fileList.at(i);
            }
        }
        gTranslate = new GTranslate(this);
        gTranslate->languageFromTo = posettings.languagePair;
        QObject::connect(gTranslate, SIGNAL(translationReady(int, QString *)), this,  SLOT(onTranslate(int, QString *)));
        tokenList.clear();
        for (int i=0;i<tokens.length();i++)
            tokenList.append(tokens.at(i).originalPhrase);
        gTranslate->translate(&tokenList);
        /*for (int i=0;i<tokens.length();i++){
            qDebug()<<tokens.at(i).originalPhrase;
            for (int j=0;j<tokens.at(i).inFile.length();j++){
                qDebug()<<"\t"<<tokens.at(i).inFile.at(j);
            }
        }*/
    }
}

void MainWindow::on_actionTranslate_triggered()
{
    /*gTranslate = new GTranslate(this);
    gTranslate->languageFromTo = "en|ro";
    QObject::connect(gTranslate, SIGNAL(translationReady(int, QString *)), this,  SLOT(onTranslate(int, QString *)));
    gTranslate->translate(ui->toTranslate->text());*/
    //gTranslate = new GTranslate(this, "http://translate.google.com/?hl=en");
}

void MainWindow::onTranslate(int index,QString *str)
{
    //qDebug()<<index<<tokenList.at(index)<<*str;
    ui->textWindow->appendPlainText(QString::number(index)+" "+tokenList.at(index)+"=>"+*str);
    for (int i=0;i<tokens.at(index).inFile.length();i++)
        ui->textWindow->appendPlainText("\t"+tokens.at(index).inFile.at(i));
}

void MainWindow::on_actionOpen_project_file_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QStringList filters;
    filters << "Project files INI (*.ini)"
            << "Any files (*)";
    dialog.setNameFilters(filters);
    if (dialog.exec()){
        if (dialog.selectedFiles().length() == 1){
            posettings.loadSettings(dialog.selectedFiles()[0]);
            //qDebug()<< dialog.selectedFiles()[0];
        }
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "ABout this program", "QPoEditor v0.1\n\n Scans files recursively for one or more string patterns\nand can automatically translate them.\nOpen project (ini) file, select path and update from files.\n\n\t\tkcsoft (c) 2011");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}
