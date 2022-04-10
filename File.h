#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <JsonWorker.h>

class File
{
public:
    QWidget* parent;

    //Variables

    QFileInfo fileInfo;

    QString jsonData;
    QString fileName;
    QString filePath;
    bool IsValidJson = false;

    JsonWorker worker;
    //Functions
    File(QWidget*);
    void LoadFile();
    void NewFile();
    void Save();
    void SaveAs();
    void LoadURL();
    void OpenContainingFolder();
    void Close();

    void updateFileInfo();
    void saveFile();
    void setJsonData();
    void validateJson();
    void discardChanges();
    void promptSaveChanges();
    bool IsSaved();
    void resetFile();
    bool doesFileExists();
    void updateWindowTitle(QString);
    void LoadEmptyFile();
};

#endif // FILE_H
