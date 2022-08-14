#include "File.h"


QString File::ReadFile()
{
    QFile *file = new QFile(_filePath);
    if (!file->open(QFile::ReadOnly | QFile::Text))
    {
        throw std::exception("Cannot open File.");
    }
    QTextStream in(this);
    QString data = in.readAll();
    file->close();
    delete file;
    return data;
}// This function is done.

void File::UpdateFileHash()
{
    QByteArray hash = QCryptographicHash::hash(jsonData.toLocal8Bit(), QCryptographicHash::Md5);
    jsonMD5Hash = hash.toHex().toStdString();
}
void File::WriteFile(QString& data)
{
    QFile *file = new QFile(_filePath);
    if (!file->open(QFile::WriteOnly | QFile::Text))
    {
        throw std::exception("Cannot open File.");
    }
    QTextStream out(file);
    out << data.toUtf8();
    file->close();
    delete file;
}
void File::SetJsonData(QString jsonString)
{
    UpdateFileHash();
    jsonData = jsonString;
}
QString* File::GetJsonData()
{
    return &jsonData;
}
void File::ClearJsonData()
{
    SetJsonData("");
}
void File::Save()
{
    WriteFile();
}
