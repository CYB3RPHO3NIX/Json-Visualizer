#ifndef JSONSUMMARYDIALOG_H
#define JSONSUMMARYDIALOG_H

#include <QDialog>
#include "JsonSummary.h"
#include <QString>
#include <QClipboard>

namespace Ui {
class JsonSummaryDialog;
}

class JsonSummaryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JsonSummaryDialog(QWidget *parent = nullptr);
    void SetData(JsonSummary data);
    ~JsonSummaryDialog();

private slots:
    void on_pushButton_clicked();

    void on_btnCopyMD5Hash_clicked();

    void on_btnCopySHA256Hash_clicked();

    void on_btnCopySHA512Hash_clicked();

private:
    Ui::JsonSummaryDialog *ui;
    JsonSummary summary;
    QClipboard *clipboard;
};

#endif // JSONSUMMARYDIALOG_H
