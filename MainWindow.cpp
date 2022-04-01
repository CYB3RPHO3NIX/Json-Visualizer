#include "MainWindow.h"
#include "jsonsummarydialog.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QtNetwork/QNetworkAccessManager>

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
    DrawTreeView(jsonString);
}
void MainWindow::DrawTreeView(QString &jsonString)
{
    treeModel = new QJsonModel();
    ui.treeView->setModel(treeModel);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    if (worker.IsValid(jsonString))
    {
        IsCurrentJsonValid = true;
        setStatus("Valid Json");
        worker.GenerateTreeView(jsonString, treeModel);
        QApplication::restoreOverrideCursor();
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


void MainWindow::on_txtJsonQuery_textChanged(const QString &queryString)
{
    if(queryString != "")
    {
        QString filtered = worker.QueryJson(ui.plainTextEdit->toPlainText(), queryString);
        if(filtered != "")
        {
            DrawTreeView(filtered);
            ui.treeView->expandAll();
        }
    }else
    {

    }

}
void MainWindow::loadFile(QString &filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Read Error"),
                                     tr("Cannot read file %1:\n%2.")
                                     .arg(filename)
                                     .arg(file.errorString()));
        return;
    }
    QTextStream inputStream(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    currentJson = inputStream.readAll();
    ui.plainTextEdit->setPlainText(currentJson);
    QApplication::restoreOverrideCursor();
    ui.statusBar->showMessage(tr("File loaded"), 2000);
}

void MainWindow::on_actionBrowse_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select json file.", "/", "Json files (*.json)");
    if (!fileName.isEmpty())
    {
        //QNetworkAccessManager manager;
        //manager.get("") -->need to code this next day.
        QFileInfo info(fileName);
        this->setWindowTitle("JSON Explorer - " + info.fileName());
        loadFile(fileName);
    }
}


