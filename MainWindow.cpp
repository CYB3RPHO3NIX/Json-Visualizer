#include "MainWindow.h"


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
    *currentFile->jsonData = ui.plainTextEdit->toPlainText();
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

}
void MainWindow::newFile()
{

}
void MainWindow::saveFile()
{

}
void MainWindow::saveAsFile()
{

}
void MainWindow::loadURL(QString url)
{

}
void MainWindow::on_actionBrowse_File_triggered()
{

}
void MainWindow::on_actionNew_File_triggered()
{

}
void MainWindow::on_actionSave_As_triggered()
{

}
void MainWindow::on_actionSave_triggered()
{

}
void MainWindow::setEditorEnabled(bool enable)
{
    ui.plainTextEdit->setEnabled(enable);
    ui.treeView->setEnabled(enable);
}
