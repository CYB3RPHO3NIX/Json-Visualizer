#include "Hash.h"

Hash::Hash(IHash* hash)
{
    _hash = hash;
}

std::string Hash::GetHash(QString data)
{
    return _hash->GetHash(data);
}
