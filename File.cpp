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
    this->close();
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
    out << GetJsonData()->toUtf8();
    this->close();
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
