#ifndef IHASH_H
#define IHASH_H
#include "string"
#include "qstring.h"

class IHash
{
public:
    virtual std::string GetHash(QString data) = 0;
};

#endif // IHASH_H
