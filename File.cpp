#include "File.h"

File::File()
{

}

void File::ReadFile()
{
    QFile f(fileName);
    if (!f.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::exception("Cannot open File.");
    }
    QTextStream in(&f);
    SetJsonData(in.readAll());
}
void File::WriteFile()
{
    QFile f(fileName);
    if (!f.open(QFile::WriteOnly | QFile::Text))
    {
        throw std::exception("Cannot open File.");
    }
    QTextStream out(&f);
    f.write(GetJsonData()->toUtf8());
}
void File::SetJsonData(QString jsonString)
{
    *jsonData = jsonString;
}
QString* File::GetJsonData()
{
    return jsonData;
}
void File::ClearJsonData()
{
    delete jsonData;
}
