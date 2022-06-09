#ifndef FILE_H
#define FILE_H

#include<QFile>
#include<QFileInfo>
#include<QTextStream>

class File : QFile, QFileInfo
{
private:
    QString *jsonData;
    QString fileName;
public:

    File();
    //Json Data related operations.
    QString* GetJsonData();
    void SetJsonData(QString);
    void ClearJsonData();
    //Json Data related operations.

    void ReadFile();
    void WriteFile();
};

#endif // FILE_H
