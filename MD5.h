#ifndef MD5_H
#define MD5_H
#include "IHash.h"
#include "string"
#include "qcryptographichash.h"

class MD5 : public IHash
{
public:
    std::string GetHash(QString data);
};

#endif // MD5_H
