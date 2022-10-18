#include "SHA256.h"

std::string SHA256::GetHash(QString data)
{
    QByteArray hash = QCryptographicHash::hash(data.toLocal8Bit(), QCryptographicHash::Sha256);
    return hash.toHex().toStdString();
}


