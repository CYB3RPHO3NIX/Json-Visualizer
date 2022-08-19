#ifndef FILE_H
#define FILE_H

#include<QFile>
#include<QFileInfo>
#include<QTextStream>
#include<QMessageBox>
#include<QCryptographicHash>
#include<QFileDialog>
#include<QDesktopServices>

class File
{
private:
    QFile _file;
public:
    //Variables
    QWidget* parentWnd;
    std::string _fileHash;


    void OpenContainingFolder();

    //functions
    File(QWidget *parent);
    //This function will open the file by taking the _filePath as input.
    bool OpenFile(); //when this gets triggered then change the IsAnyFileOpen status to true;

    //This function will close the file and clear the _fileName and _filePath variables.
    bool CloseFile(); //when this gets triggered then change the IsAnyFileOpen status to false;

    void BrowseFile();

    void CreateNewFile();

    void SaveFile();

    void SaveAsFile();

    bool IsExists();

    //Read the entire file.
    QString ReadFile();
    //Write into the file.
    void WriteFile(QString data);
    //Json Data related operations.
    void UpdateFileHash();
};

#endif // FILE_H
