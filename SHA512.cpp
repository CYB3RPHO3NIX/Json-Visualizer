#include "SHA512.h"

std::string SHA512::GetHash(QString data)
{
    QByteArray hash = QCryptographicHash::hash(data.toLocal8Bit(), QCryptographicHash::Sha256);
    return hash.toHex().toStdString();
}
