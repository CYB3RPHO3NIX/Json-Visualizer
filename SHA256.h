#ifndef SHA256_H
#define SHA256_H
#include "IHash.h"
#include "string"
#include "qcryptographichash.h"

class SHA256 : public IHash
{
public:
    std::string GetHash(QString data);
};

#endif // SHA256_H
