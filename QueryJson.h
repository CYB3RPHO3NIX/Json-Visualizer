#ifndef QUERYJSON_H
#define QUERYJSON_H
#include "qstring.h"
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpath/jsonpath.hpp>

using json = jsoncons::json;
namespace jsonpath = jsoncons::jsonpath;

class QueryJson
{
public:
    QString Query(QString& jsonString, QString queryString);
};

#endif // QUERYJSON_H
