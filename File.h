#ifndef FILE_H
#define FILE_H

#include<QFile>
#include<QFileInfo>
#include<QTextStream>
#include<QCryptographicHash>

class File : public QFile
{
public:
    QString jsonData;
    std::string jsonMD5Hash;
    bool isValidJson;

    File();
    //Json Data related operations.
    QString* GetJsonData();
    void SetJsonData(QString);
    void ClearJsonData();
    //Json Data related operations.
    void UpdateFileHash();

    void ReadFile();
    void WriteFile();
};

#endif // FILE_H
