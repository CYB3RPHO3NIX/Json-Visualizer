#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
class File
{
public:
    //Variables
    QFile file;
    QFileInfo fileInfo;
    QString jsonData;
    //Functions
    File();
    void LoadFile(QWidget* parent);
    void NewFile(QWidget* parent);
    void setJsonData(QString data);
    QString* getJsonData();
};

#endif // FILE_H