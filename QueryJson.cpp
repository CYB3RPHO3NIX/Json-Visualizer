#include "QueryJson.h"

QString QueryJson::Query(QString& jsonString, QString queryString)
{
    try
    {
        json data = json::parse(jsonString.toStdString());
        std::string query = queryString.toStdString();
        jsoncons::basic_json<char> temp = jsonpath::json_query(data, query);
        std::string result = temp.as_string();
        return QString::fromUtf8(result.c_str());
    }
    catch (...)  {
        return QString::fromStdString("");
    }
}
