#pragma once
#include "simdjson.h"
#include "qjsonmodel.h"
#include <string>
class JsonWorker
{
public:
	bool IsValid(QString&);
	void GenerateTreeView(QString&, QJsonModel*);
private:
};

