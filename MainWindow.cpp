#include "MainWindow.h"
#include "JsonWorker.h"
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
    JsonWorker worker;
    QString jsonString = ui.plainTextEdit->toPlainText();
    QJsonModel* treeModel = new QJsonModel();
    ui.treeView->setModel(treeModel);
    if (worker.IsValid(jsonString))
    {
        setStatus("Valid Json");
        worker.GenerateTreeView(jsonString, treeModel);
        summary = treeModel->getJsonSummary();
        summary.setMD5_Hash(jsonString);
        summary.setSHA256_Hash(jsonString);
        summary.setSHA512_Hash(jsonString);
        auto md5hash = summary.getMD5_Hash();
        auto sha256 = summary.getSHA256_Hash();
        auto sha512 = summary.getSHA512_Hash();
    }
    else
    {
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
