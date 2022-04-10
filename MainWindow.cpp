#include "MainWindow.h"
#include "JsonSummaryDialog.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QtNetwork/QNetworkAccessManager>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), currentFile(this)
{
    ui.setupUi(this);
}
void MainWindow::setStatus(const char* statusString)
{
    ui.statusBar->showMessage(statusString);
}

void MainWindow::on_plainTextEdit_textChanged()
{
    currentFile.jsonData = ui.plainTextEdit->toPlainText();
    currentFile.validateJson();
    if(currentFile.IsValidJson)
    {
        DrawTreeView(currentFile.jsonData);
        setStatus("Valid Json");
    }else
    {
        QString empty = "";
        DrawTreeView(empty);
        setStatus("Invalid Json");
    }
}
void MainWindow::DrawTreeView(QString &jsonString)
{
    treeModel = new QJsonModel();
    ui.treeView->setModel(treeModel);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    if(jsonString != "")
    {
        worker.GenerateTreeView(jsonString, treeModel);
    }
    QApplication::restoreOverrideCursor();

    summary = treeModel->getJsonSummary();
    summary.setMD5_Hash(jsonString);
    summary.setSHA256_Hash(jsonString);
    summary.setSHA512_Hash(jsonString);

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
    if(currentFile.IsValidJson)
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
        QString filtered = worker.QueryJson(currentFile.jsonData, queryString);
        if(filtered != "")
        {
            DrawTreeView(filtered);
            ui.treeView->expandAll();
        }
    }else
    {

    }

}
void MainWindow::loadFile()
{
    currentFile.LoadFile();
    setEditorEnabled(true);
    ui.plainTextEdit->setPlainText(currentFile.jsonData);
    ui.statusBar->showMessage(tr("File loaded"), 2000);
}

void MainWindow::on_actionBrowse_File_triggered()
{
    loadFile();
}
void MainWindow::on_actionNew_File_triggered()
{
    currentFile.NewFile();
    setEditorEnabled(true);
}
void MainWindow::on_actionSave_As_triggered()
{
    currentFile.SaveAs();
}
void MainWindow::on_actionSave_triggered()
{
    currentFile.Save();
}
void MainWindow::setEditorEnabled(bool enable)
{
    if(enable)
    {
        ui.plainTextEdit->setEnabled(true);
        ui.treeView->setEnabled(true);
    }else
    {
        ui.plainTextEdit->setEnabled(false);
        ui.treeView->setEnabled(false);
    }
}
