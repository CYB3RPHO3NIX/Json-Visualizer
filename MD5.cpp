#include "MD5.h"

std::string MD5::GetHash(QString data)
{
    QByteArray hash = QCryptographicHash::hash(data.toLocal8Bit(), QCryptographicHash::Md5);
    return hash.toHex().toStdString();
}
