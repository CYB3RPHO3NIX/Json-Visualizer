#pragma once
#include "simdjson.h"
#include "qjsonmodel.h"
#include <string>
#include <jsoncons/json.hpp>
#include <jsoncons_ext/jsonpath/jsonpath.hpp>

using json = jsoncons::json;
namespace jsonpath = jsoncons::jsonpath;

class JsonWorker
{
public:
	bool IsValid(QString&);
	void GenerateTreeView(QString&, QJsonModel*);
    QString QueryJson(QString jsonString, QString queryString);
private:
};

