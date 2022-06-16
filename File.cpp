#include "File.h"

File::File()
{

}

void File::ReadFile()
{
    if (!this->open(QFile::ReadOnly | QFile::Text))
    {
        throw std::exception("Cannot open File.");
    }
    QTextStream in(this);
    SetJsonData(in.readAll());
}
void File::UpdateFileHash()
{
    QByteArray hash = QCryptographicHash::hash(jsonData.toLocal8Bit(), QCryptographicHash::Md5);
    jsonMD5Hash = hash.toHex().toStdString();
}
void File::WriteFile()
{

    if (!this->open(QFile::WriteOnly | QFile::Text))
    {
        throw std::exception("Cannot open File.");
    }
    QTextStream out(this);
    this->write(GetJsonData()->toUtf8());
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
