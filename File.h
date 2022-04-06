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
    //Variables
    QFile file;
    QFileInfo fileInfo;
    QString jsonData;
    bool IsValidJson = false;
    JsonWorker worker;
    //Functions
    File();
    void LoadFile(QWidget* parent);
    void NewFile(QWidget* parent);
    void Save(QWidget* parent);
    void SaveAs(QWidget* parent);
    void LoadURL(QWidget* parent);
    void OpenContainingFolder(QWidget* parent);
    void Close(QWidget* parent);

    void updateFileInfo();
    void saveFile(QWidget* parent);
    void setJsonData(QString data);
    void validateJson();
    void discardChanges();
    void promptSaveChanges(QWidget* parent);
    bool IsSaved();
    void resetFile();
};

#endif // FILE_H
