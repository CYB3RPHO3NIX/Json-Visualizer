#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "JsonSummary.h"
#include "JsonWorker.h"
#include "JsonSummaryDialog.h"
#include <QMessageBox>
#include <QTime>
#include <QTextStream>
#include <QFileDialog>
#include <QtNetwork/QNetworkAccessManager>
#include <File.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    
private:
    Ui::MainWindowClass ui;
    Summary* summary;    //this will store the analysis data of the json.
    JsonWorker worker;      //worker class for handling json related operations.
    QJsonModel* treeModel;
    std::string plainTextEditorMD5Hash;

    //recreated functions
    void UpdateJsonSummary();


    //functions
    void DrawTreeView(QString& jsonString);
    void setStatus(const char* statusString);
    void setEditorEnabled(bool enable);
private slots:
    void on_plainTextEdit_textChanged();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionSummary_triggered();
    void on_txtJsonQuery_textChanged(const QString &arg1);
    void on_actionBrowse_File_triggered();
    void on_actionNew_File_triggered();
    void on_actionSave_As_triggered();
    void on_actionSave_triggered();
};
