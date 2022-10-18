#ifndef JSON_H
#define JSON_H
#include "IJson.h"
#include "qstring.h"
#include "simdjson.h"

class Json : public IJson
{
private:
    long long ObjectCount=0;
    long long ArrayCount=0;
    long long StringCount=0;
    long long NumberCount=0;
    long long BooleanCount=0;
    long long NullCount=0;
public:
    QString* JsonData;
    Json();
    bool IsValidJson();
    long long GetObjectCount();
    long long GetArrayCount();
    long long GetStringCount();
    long long GetNumberCount();
    long long GetBooleanCount();
    long long GetNullCount();
};

#endif // JSON_H
