#include "Summary.h"
#include "ui_Summary.h"

Summary::Summary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Summary)
{
    ui->setupUi(this);
    this->ObjectCount = 0;
    this->ArrayCount = 0;
    this->StringCount = 0;
    this->NumberCount = 0;
    this->NullCount = 0;
    this->BooleanCount = 0;
}

Summary::~Summary()
{
    delete ui;
}

void Summary::setMD5_Hash(QString json)
{
    QByteArray hash = QCryptographicHash::hash(json.toLocal8Bit(), QCryptographicHash::Md5);
    this->MD5_Hash = hash.toHex().toStdString();
}

void Summary::setObjectCount(long long value)
{
    this->ObjectCount = value;
}
void Summary::setArrayCount(long long value)
{
    this->ArrayCount = value;
}
void Summary::setStringCount(long long value)
{
    this->StringCount = value;
}
void Summary::setNumberCount(long long value)
{
    this->NumberCount = value;
}

void Summary::setNullCount(long long value)
{
    this->NullCount = value;
}
void Summary::setBooleanCount(long long value)
{
    this->BooleanCount = value;
}

//Get Functions.
std::string Summary::getMD5_Hash()
{
    return this->MD5_Hash;
}
long long Summary::getObjectCount()
{
    return this->ObjectCount;
}
long long Summary::getArrayCount()
{
    return this->ArrayCount;
}
long long Summary::getStringCount()
{
    return this->StringCount;
}
long long Summary::getNumberCount()
{
    return this->NumberCount;
}
long long Summary::getNullCount()
{
    return this->NullCount;
}
long long Summary::getBooleanCount()
{
    return this->BooleanCount;
}
