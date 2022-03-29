#include "JsonSummary.h"

JsonSummary::JsonSummary()
{
	this->ObjectCount = 0;
	this->ArrayCount = 0;
	this->StringCount = 0;
	this->NumberCount = 0;
	this->NullCount = 0;
	this->BooleanCount = 0;
}

void JsonSummary::setMD5_Hash(QString json)
{
	QByteArray hash = QCryptographicHash::hash(json.toLocal8Bit(), QCryptographicHash::Md5);
	this->MD5_Hash = hash.toHex().toStdString();
}
void JsonSummary::setSHA256_Hash(QString json)
{
	QByteArray hash = QCryptographicHash::hash(json.toLocal8Bit(), QCryptographicHash::Sha256);
	this->SHA256_Hash = hash.toHex().toStdString();
}
void JsonSummary::setSHA512_Hash(QString json)
{
	QByteArray hash = QCryptographicHash::hash(json.toLocal8Bit(), QCryptographicHash::Sha512);
	this->SHA512_Hash = hash.toHex().toStdString();
}
void JsonSummary::setObjectCount(long long value)
{
	this->ObjectCount = value;
}
void JsonSummary::setArrayCount(long long value)
{
	this->ArrayCount = value;
}
void JsonSummary::setStringCount(long long value)
{
	this->StringCount = value;
}
void JsonSummary::setNumberCount(long long value)
{
	this->NumberCount = value;
}

void JsonSummary::setNullCount(long long value)
{
	this->NullCount = value;
}
void JsonSummary::setBooleanCount(long long value)
{
	this->BooleanCount = value;
}

//Get Functions.
std::string JsonSummary::getMD5_Hash()
{
	return this->MD5_Hash;
}
std::string JsonSummary::getSHA256_Hash()
{
	return this->SHA256_Hash;
}

std::string JsonSummary::getSHA512_Hash()
{
	return this->SHA512_Hash;
}
long long JsonSummary::getObjectCount()
{
	return this->ObjectCount;
}
long long JsonSummary::getArrayCount()
{
	return this->ArrayCount;
}
long long JsonSummary::getStringCount()
{
	return this->StringCount;
}
long long JsonSummary::getNumberCount()
{
	return this->NumberCount;
}
long long JsonSummary::getNullCount()
{
	return this->NullCount;
}
long long JsonSummary::getBooleanCount()
{
	return this->BooleanCount;
}
