#ifndef SHA512_H
#define SHA512_H
#include "IHash.h"
#include "string"
#include "qcryptographichash.h"

class SHA512 : public IHash
{
public:
    std::string GetHash(QString data);
};

#endif // SHA512_H
