#ifndef MEMORYFILE_H
#define MEMORYFILE_H

#include<QString>
#include<QFile>
#include<QFileInfo>

class MemoryFile : public QFile, public QFileInfo
{
    public:
        MemoryFile();
        QString *jsonData;
        bool IsValidJson;
};

#endif // MEMORYFILE_H
