#include "MainWindow.h"

#include "jsonsummarydialog.h"
#include <QMessageBox>

#include<chrono>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
}
void MainWindow::setStatus(const char* statusString)
{
    ui.statusBar->showMessage(statusString);
}

void MainWindow::on_plainTextEdit_textChanged()
{
    QString jsonString = ui.plainTextEdit->toPlainText();
    treeModel = new QJsonModel();
    ui.treeView->setModel(treeModel);
    if (worker.IsValid(jsonString))
    {
        IsCurrentJsonValid = true;
        setStatus("Valid Json");
        worker.GenerateTreeView(jsonString, treeModel);
        summary = treeModel->getJsonSummary();
        summary.setMD5_Hash(jsonString);
        summary.setSHA256_Hash(jsonString);
        summary.setSHA512_Hash(jsonString);
    }
    else
    {
        IsCurrentJsonValid = false;
        setStatus("Invalid Json");
    }
    ui.treeView->show();
}
void MainWindow::on_actionZoom_In_triggered()
{
    ui.plainTextEdit->zoomIn();
}

void MainWindow::on_actionZoom_Out_triggered()
{
    ui.plainTextEdit->zoomOut();
}

void MainWindow::on_actionSummary_triggered()
{
    QString jsonString = ui.plainTextEdit->toPlainText();
    if(worker.IsValid(jsonString))
    {
        JsonSummaryDialog dialog;
        dialog.SetData(summary);
        dialog.exec();
    }else
    {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Critical);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.setText("JSON is invalid and cannot be processed.");
        msg.exec();
    }
}

