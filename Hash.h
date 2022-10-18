#ifndef HASH_H
#define HASH_H
#include "IHash.h"

class Hash : public IHash
{
private:
    IHash* _hash;
public:
    Hash(IHash* hash);
    std::string GetHash(QString data);
};

#endif // HASH_H
