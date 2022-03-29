#pragma once
#include<qstring.h>
#include<QCryptographicHash>
class JsonSummary
{
private:
	std::string MD5_Hash;
	std::string SHA256_Hash;
	std::string SHA512_Hash;
	long long ObjectCount;
	long long ArrayCount;
	long long StringCount;
	long long NumberCount;
	long long NullCount;
	long long BooleanCount;
	
public:
	JsonSummary();
	//Set Functions.
	void setMD5_Hash(QString);
	void setSHA256_Hash(QString);
	void setSHA512_Hash(QString);
	void setObjectCount(long long);
	void setArrayCount(long long);
	void setStringCount(long long);
	void setNumberCount(long long);
	void setNullCount(long long);
	void setBooleanCount(long long);

	//Get Functions.
	std::string getMD5_Hash();
	std::string getSHA256_Hash();
	std::string getSHA512_Hash();
	long long getObjectCount();
	long long getArrayCount();
	long long getStringCount();
	long long getNumberCount();
	long long getNullCount();
	long long getBooleanCount();

};
