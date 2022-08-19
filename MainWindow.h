#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "Summary.h"
#include "JsonWorker.h"
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
    QString _JsonData;
    
private:
    Ui::MainWindowClass ui;
    Summary* _summary;    //this will store the analysis data of the json.
    JsonWorker _worker;      //worker class for handling json related operations.
    QJsonModel* _treeModel;
    File _currentFile;
    std::string _JsonDataMD5Hash;


    //Flags
    bool IsFileSaved;
    bool IsValidJson;
    bool IsAnyFileOpen;

    //recreated functions
    void UpdateJsonSummary();
    void validateJson();
    void SaveFile();
    void SaveAsFile();
    void SaveChanges();
    void BrowseFile();
    void CreateNewFile();

    void OpenFile();
    void CloseFile();


    void PromptSaveChanges();
    void Reset();
    void ResetTreeViewPanel();
    void ResetEditorPanel();

    //functions
    void DrawTreeView(QString&);
    void setStatus(const char* statusString);
    void setEditorEnabled(bool enable);
    void updateJsonDataHash();


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
