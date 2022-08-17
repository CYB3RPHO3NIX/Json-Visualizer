#include "File.h"



bool File::OpenFile()
{
    if (!_file.open(QFile::ReadWrite | QFile::Text))
    {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Critical);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.setText("Cannot open File.");
        msg.exec();
        return false;
    }else
    {
        return true;
    }
}
bool File::CloseFile()
{
    try {
    _file.close();
    return true;
    }  catch (...) {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Critical);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.setText("Cannot close File.");
        msg.exec();
        return false;
    }
}
void File::UpdateFileHash()
{
    QByteArray hash = QCryptographicHash::hash(ReadFile().toLocal8Bit(), QCryptographicHash::Md5);
    _fileHash = hash.toHex().toStdString();
}
void File::WriteFile(QString& data)
{
    if(_file.isOpen() && _file.isWritable())
    {
        QTextStream out(&_file);
        out << data.toUtf8();
    }
    else
    {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Critical);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.setText("Cannot write to File");
        msg.exec();
    }
}
QString File::ReadFile()
{
    if(_file.isOpen() && _file.isReadable())
    {
        QTextStream in(&_file);
        QString data = in.readAll();
        return data;
    }else
    {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Critical);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.setText("Cannot read File");
        msg.exec();
    }
}


