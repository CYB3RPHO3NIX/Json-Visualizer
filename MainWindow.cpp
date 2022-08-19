#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), _currentFile(parent)
{
    ui.setupUi(this);
    setEditorEnabled(false);
}
void MainWindow::setStatus(const char* statusString)
{
    ui.statusBar->showMessage(statusString);
}


//plainTextEdit is the variable that holds the actual Json Data.
void MainWindow::on_plainTextEdit_textChanged()
{
    _JsonData = ui.plainTextEdit->toPlainText();
    IsFileSaved = false; //change the flag

    updateJsonDataHash();
    validateJson();
    if(IsValidJson)
    {
        DrawTreeView(_JsonData);
        setStatus("Valid Json");
    }else
    {
        ResetTreeViewPanel();
        setStatus("Invalid Json");
    }
}
void MainWindow::validateJson()
{
    IsValidJson = _worker.IsValid(_JsonData);
}
void MainWindow::DrawTreeView(QString& jsonString)
{
    _treeModel = new QJsonModel();
    ui.treeView->setModel(_treeModel);

    QApplication::setOverrideCursor(Qt::WaitCursor);
    if(jsonString != "")
    {
        _worker.GenerateTreeView(jsonString, _treeModel);
    }
    QApplication::restoreOverrideCursor();
    ui.treeView->show();
}
void MainWindow::UpdateJsonSummary()
{
    _summary = _treeModel->getJsonSummary();
    QByteArray bytes = _JsonData.toUtf8();
    int length = bytes.size();
    _summary->setDataSize(length);
    _summary->setParsingTime(_worker.getParsingTime());
    _summary->setMD5_Hash(_JsonData);
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
    if(IsValidJson)
    {
        Summary* dialog = _treeModel->getJsonSummary();
        dialog->exec();
    }else
    {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Critical);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.setText("JSON is invalid and cannot be processed.");
        msg.exec();
    }
}
void MainWindow::updateJsonDataHash()
{
    QByteArray hash = QCryptographicHash::hash(ui.plainTextEdit->toPlainText().toLocal8Bit(), QCryptographicHash::Md5);
    _JsonDataMD5Hash = hash.toHex().toStdString();
}

void MainWindow::SaveChanges()
{
    _currentFile.WriteFile(_JsonData);
}
void MainWindow::SaveFile()
{
    if(!IsFileSaved)
    {
        if(_currentFile.IsExists())
        {
            SaveChanges();
            IsFileSaved = true;
        }else
        {
            SaveAsFile();
        }
    }
}
void MainWindow::CreateNewFile()
{
    _currentFile.CreateNewFile();

}
void MainWindow::OpenFile()
{
    IsAnyFileOpen = true;
}
void MainWindow::CloseFile()
{
    IsAnyFileOpen = false;
    _currentFile.CloseFile();
    Reset();
    setEditorEnabled(false);
}
void MainWindow::SaveAsFile()
{
    BrowseFile();
    SaveFile();
}
void MainWindow::BrowseFile()
{
    _currentFile.BrowseFile();
}

void MainWindow::on_txtJsonQuery_textChanged(const QString &queryString)
{
    if(queryString != "")
    {
        QString *filtered = new QString();
        *filtered = _worker.QueryJson(_JsonData, queryString);
        if(*filtered != "")
        {
            DrawTreeView(*filtered);
            ui.treeView->expandAll();
        }
    }
}

void MainWindow::PromptSaveChanges()
{
    QMessageBox msgBox;
    msgBox.setText("Json data has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int choice = msgBox.exec();
    if(choice == QMessageBox::Save)
    {
        SaveFile();
    }else if(choice == QMessageBox::Discard)
    {
        Reset();
    }
}

void MainWindow::ResetTreeViewPanel()
{
    QString empty="";
    DrawTreeView(empty);
}
void MainWindow::ResetEditorPanel()
{
    ui.plainTextEdit->clear();
}
void MainWindow::Reset()
{
    delete _summary;
    delete _treeModel;
    _JsonData.clear();
    _JsonDataMD5Hash.clear();
    ResetEditorPanel();
    ResetTreeViewPanel();
}
void MainWindow::on_actionBrowse_File_triggered()
{

}
void MainWindow::on_actionNew_File_triggered()
{
    if(IsAnyFileOpen)
    {
        //if YES
        if(IsFileSaved)
        {

        }else
        {
            QMessageBox msgBox;
            msgBox.setText("Json data has been modified.");
            msgBox.setInformativeText("Do you want to save your changes?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save);
            int choice = msgBox.exec();
            if(choice == QMessageBox::Save)
            {
                SaveFile();
                CloseFile();

            }else if(choice == QMessageBox::Discard)
            {
                Reset();
            }else
            {
                return;
            }
        }
    }else
    {
        //if NO
        CreateNewFile();
    }
}
void MainWindow::on_actionSave_As_triggered()
{

}
void MainWindow::on_actionSave_triggered()
{

}
void MainWindow::setEditorEnabled(bool enable)
{
    ui.plainTextEdit->setHidden(!enable);
    ui.treeView->setHidden(!enable);
}

