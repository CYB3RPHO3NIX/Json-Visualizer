#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "JsonSummary.h"
#include "JsonWorker.h"
#include "JsonSummaryDialog.h"
#include <QMessageBox>
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
    File *currentFile = NULL;
    JsonSummary summary;    //this will store the analysis data of the json.
    JsonWorker worker;      //worker class for handling json related operations.
    QJsonModel* treeModel;
    std::string jsonMD5Hash;

    //functions
    void DrawTreeView(QString &jsonString);
    void setStatus(const char* statusString);
    void loadURL(QString url);
    void loadFile();
    void saveFile();
    void newFile();
    void saveAsFile();
    void setEditorEnabled(bool enable);

    void saveChanges();
    void validateJson();
    void ResetLayout();
    bool isAnyFileOpen();
    bool isFileSaved();
    void DestroyFileInstance();
    void BrowseFile();
    void createNewFile(QString);
    int PromptSaveChanges();
    void updateEditorTextHash();
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
