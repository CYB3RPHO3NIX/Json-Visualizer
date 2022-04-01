#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "JsonSummary.h"
#include "JsonWorker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    
private:
    Ui::MainWindowClass ui;
    QFile currentFile;
    QString currentJson;    //actual json data.
    QString fileName;       //fully qualified filename.
    JsonSummary summary;    //this will store the analysis data of the json.
    JsonWorker worker;      //worker class for handling json related operations.
    bool IsCurrentJsonValid;
    QJsonModel* treeModel;

    //functions
    void DrawTreeView(QString &jsonString);
    void setStatus(const char* statusString);
    void loadURL(QString &url);
    void loadFile(QString &filename);
    void saveFile(QString &filename);
private slots:
    void on_plainTextEdit_textChanged();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionSummary_triggered();
    void on_txtJsonQuery_textChanged(const QString &arg1);
    void on_actionBrowse_File_triggered();
};
