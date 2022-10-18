#include "jsonsummarydialog.h"
#include "ui_jsonsummarydialog.h"

JsonSummaryDialog::JsonSummaryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JsonSummaryDialog)
{
    ui->setupUi(this);
    clipboard = QGuiApplication::clipboard();
}
void JsonSummaryDialog::SetData(JsonSummary data)
{
    summary.setObjectCount(data.getObjectCount());
    summary.setArrayCount(data.getArrayCount());
    summary.setNumberCount(data.getNumberCount());
    summary.setNullCount(data.getNullCount());
    summary.setBooleanCount(data.getBooleanCount());
    summary.setStringCount(data.getStringCount());
    summary.setMD5_Hash(QString::fromStdString(data.getMD5_Hash()));
    summary.setSHA256_Hash(QString::fromStdString(data.getSHA256_Hash()));
    summary.setSHA512_Hash(QString::fromStdString(data.getSHA512_Hash()));

    ui->txtObjects->setText(QString::number(summary.getObjectCount()));
    ui->txtArrays->setText(QString::number(summary.getArrayCount()));
    ui->txtNumbers->setText(QString::number(summary.getNumberCount()));
    ui->txtStrings->setText(QString::number(summary.getStringCount()));
    ui->txtBooleans->setText(QString::number(summary.getBooleanCount()));
    ui->txtNulls->setText(QString::number(summary.getNullCount()));
    ui->txtMD5Hash->setText(QString::fromStdString(summary.getMD5_Hash()));
    ui->txtSHA256Hash->setText(QString::fromStdString(summary.getSHA256_Hash()));
    ui->txtSHA512Hash->setText(QString::fromStdString(summary.getSHA512_Hash()));
}
JsonSummaryDialog::~JsonSummaryDialog()
{
    delete ui;
}

void JsonSummaryDialog::on_pushButton_clicked()
{
    this->close();
}

void JsonSummaryDialog::on_btnCopyMD5Hash_clicked()
{
    clipboard->clear(QClipboard::Clipboard);
    clipboard->setText(QString::fromStdString(summary.getMD5_Hash()) , QClipboard::Clipboard);
}

void JsonSummaryDialog::on_btnCopySHA256Hash_clicked()
{
    clipboard->clear(QClipboard::Clipboard);
    clipboard->setText(QString::fromStdString(summary.getSHA256_Hash()) , QClipboard::Clipboard);
}

void JsonSummaryDialog::on_btnCopySHA512Hash_clicked()
{
    clipboard->clear(QClipboard::Clipboard);
    clipboard->setText(QString::fromStdString(summary.getSHA512_Hash()) , QClipboard::Clipboard);
}
