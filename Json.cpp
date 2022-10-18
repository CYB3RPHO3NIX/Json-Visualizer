#include "Json.h"

Json::Json()
{

}
bool Json::IsValidJson()
{
    simdjson::error_code error;
    simdjson::dom::parser parser;
    error = parser.parse(simdjson::padded_string(JsonData->toStdString())).error();
    if (error)
    {
        return false;
    }
    else
    {
        return true;
    }
}
long long Json::GetObjectCount()
{
    return ObjectCount;
}
long long Json::GetArrayCount()
{
    return ArrayCount;
}
long long Json::GetStringCount()
{
    return StringCount;
}
long long Json::GetNumberCount()
{
    return NumberCount;
}
long long Json::GetBooleanCount()
{
    return BooleanCount;
}
long long Json::GetNullCount()
{
    return NullCount;
}
