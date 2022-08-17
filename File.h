#ifndef FILE_H
#define FILE_H

#include<QFile>
#include<QFileInfo>
#include<QTextStream>
#include<QMessageBox>
#include<QCryptographicHash>

class File
{
private:
    QFile _file;
public:
    //Variables
    QString _fileName;//this will store only the file name.
    QString _filePath;//this will store the fully qualified filename.
    std::string _fileHash;


    //Flags
    bool IsAnyFileOpen;

    //functions

    //This function will only create a Abstract file, by just assigning the the value of _fileName as Untitled.json.
    void CreateAbstractFile(); //this will create a new Untitled.json file. it will just set the value of _fileName.

    //This function will open the file by taking the _filePath as input.
    bool OpenFile(); //when this gets triggered then change the IsAnyFileOpen status to true;

    //This function will close the file and clear the _fileName and _filePath variables.
    bool CloseFile();//when this gets triggered then change the IsAnyFileOpen status to false;



    //Read the entire file.
    QString ReadFile();
    //Write into the file.
    void WriteFile(QString& data);


    QString* GetJsonData();
    void SetJsonData(QString);
    void ClearJsonData();
    //Json Data related operations.
    void UpdateFileHash();
    void Save();



};

#endif // FILE_H
