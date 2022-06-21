#ifndef SUMMARY_H
#define SUMMARY_H

#include <QDialog>
#include <QTime>
#include <QCryptographicHash>

namespace Ui {
class Summary;
}

class Summary : public QDialog
{
    Q_OBJECT

public:
    explicit Summary(QWidget *parent = nullptr);
    ~Summary();

private:
    Ui::Summary *ui;
    std::string MD5_Hash;

    long long ObjectCount;
    long long ArrayCount;
    long long StringCount;
    long long NumberCount;
    long long NullCount;
    long long BooleanCount;

public:

    void setMD5_Hash(QString);
    void setObjectCount(long long);
    void setArrayCount(long long);
    void setStringCount(long long);
    void setNumberCount(long long);
    void setNullCount(long long);
    void setBooleanCount(long long);

    std::string getMD5_Hash();
    long long getObjectCount();
    long long getArrayCount();
    long long getStringCount();
    long long getNumberCount();
    long long getNullCount();
    long long getBooleanCount();
};

#endif // SUMMARY_H
