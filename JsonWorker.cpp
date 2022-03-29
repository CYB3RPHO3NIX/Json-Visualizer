#include "JsonWorker.h"
#include <string.h>


bool JsonWorker::IsValid(QString& jsonString)
{
	simdjson::error_code error;
	simdjson::dom::parser parser;
	error = parser.parse(simdjson::padded_string(jsonString.toStdString())).error();
	if (error)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void JsonWorker::GenerateTreeView(QString& jsonString, QJsonModel* jsonModel)
{
	jsonModel->loadJson(QByteArray::fromStdString(jsonString.toStdString()));
}