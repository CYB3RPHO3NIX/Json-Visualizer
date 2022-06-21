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
    ui->txt_md5Hash->setText(QString::fromUtf8(hash.toHex()));
}

void Summary::setObjectCount(long long value)
{
    this->ObjectCount = value;
    ui->txt_objects->setText(QString::number(this->ObjectCount));
}
void Summary::setArrayCount(long long value)
{
    this->ArrayCount = value;
    ui->txt_arrays->setText(QString::number(this->ArrayCount));
}
void Summary::setStringCount(long long value)
{
    this->StringCount = value;
    ui->txt_strings->setText(QString::number(this->StringCount));
}
void Summary::setNumberCount(long long value)
{
    this->NumberCount = value;
    ui->txt_numbers->setText(QString::number(this->NumberCount));
}

void Summary::setNullCount(long long value)
{
    this->NullCount = value;
    ui->txt_nulls->setText(QString::number(this->NullCount));
}
void Summary::setBooleanCount(long long value)
{
    this->BooleanCount = value;
    ui->txt_booleans->setText(QString::number(this->BooleanCount));
}
void Summary::setParsingTime(int time)
{
    this->ParsingTime = time;
    ui->txt_parsingTime->setText(QString::number(this->ParsingTime));
}
void Summary::setDataSize(int size)
{
    this->DataSize = size;
    ui->txt_dataSize->setText(QString::number(this->DataSize));
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
int Summary::getParsingTime()
{
    return this->ParsingTime;
}
int Summary::getDataSize()
{
    return this->DataSize;
}
