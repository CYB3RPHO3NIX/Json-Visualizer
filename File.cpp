#include "File.h"

File::File()
{

}

void File::ReadFile()
{
    QFile f(this->fileName());
    if (!f.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::exception("Cannot open File.");
    }
    QTextStream in(&f);
    SetJsonData(in.readAll());
}
void File::UpdateFileHash()
{
    QByteArray hash = QCryptographicHash::hash(jsonData.toLocal8Bit(), QCryptographicHash::Md5);
    jsonMD5Hash = hash.toHex().toStdString();
}
void File::WriteFile()
{
    QFile f(this->fileName());
    if (!f.open(QFile::WriteOnly | QFile::Text))
    {
        throw std::exception("Cannot open File.");
    }
    QTextStream out(&f);
    f.write(GetJsonData()->toUtf8());
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
