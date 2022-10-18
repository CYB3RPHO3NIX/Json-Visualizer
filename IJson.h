#ifndef IJSON_H
#define IJSON_H

class IJson
{
public:
    virtual bool IsValidJson() = 0;

    virtual long long GetObjectCount() = 0;
    virtual long long GetArrayCount() = 0;
    virtual long long GetStringCount() = 0;
    virtual long long GetNumberCount() = 0;
    virtual long long GetNullCount() = 0;
    virtual long long GetBooleanCount() = 0;
};

#endif // IJSON_H
