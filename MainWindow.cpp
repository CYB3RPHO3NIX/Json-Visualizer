#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    setEditorEnabled(false);
}
void MainWindow::setStatus(const char* statusString)
{
    ui.statusBar->showMessage(statusString);
}

void MainWindow::on_plainTextEdit_textChanged()
{
    currentFile->SetJsonData(ui.plainTextEdit->toPlainText());
    updateEditorTextHash();
    validateJson();
    if(currentFile->isValidJson)
    {
        DrawTreeView(*currentFile->GetJsonData());
        setStatus("Valid Json");
    }else
    {
        QString empty="";
        DrawTreeView(empty);
        setStatus("Invalid Json");
    }
}
void MainWindow::validateJson()
{
    currentFile->isValidJson = worker.IsValid(*currentFile->GetJsonData());
}
void MainWindow::DrawTreeView(QString& jsonString)
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
    if(currentFile->isValidJson)
    {
        JsonSummaryDialog dialog;
        dialog.SetData(summary);
    }else
    {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Critical);
        msg.setDefaultButton(QMessageBox::Ok);
        msg.setText("JSON is invalid and cannot be processed.");
        msg.exec();
    }
}
void MainWindow::updateEditorTextHash()
{
    QByteArray hash = QCryptographicHash::hash(ui.plainTextEdit->toPlainText().toLocal8Bit(), QCryptographicHash::Md5);
    jsonMD5Hash = hash.toHex().toStdString();
}
bool MainWindow::isAnyFileOpen()
{
    if(currentFile != NULL)
    {
        return true;
    }else
    {
        return false;
    }
}
bool MainWindow::isFileSaved()
{
    if(currentFile->jsonMD5Hash == jsonMD5Hash)
    {
        return true;
    }else
    {
        return false;
    }
}
void MainWindow::DestroyFileInstance()
{
    delete currentFile;
    currentFile = NULL;
    ResetLayout();
}
void MainWindow::ResetLayout()
{
    ui.plainTextEdit->clear();
    delete treeModel;
    this->setWindowTitle("JSON Explorer");
}
void MainWindow::on_txtJsonQuery_textChanged(const QString &queryString)
{
    if(queryString != "")
    {
        QString *filtered = new QString();
        *filtered = worker.QueryJson(*currentFile->GetJsonData(), queryString);
        if(*filtered != "")
        {
            DrawTreeView(*filtered);
            ui.treeView->expandAll();
        }
    }else
    {

    }
}
void MainWindow::loadFile(QString filename)
{
    if(isAnyFileOpen())
    {
        if(currentFile->exists())
        {
            if(isFileSaved())
            {
                DestroyFileInstance();
            }else
            {
                switch (PromptSaveChanges())
                {
                  case QMessageBox::Save:
                        saveChanges();
                        DestroyFileInstance();
                      break;
                  case QMessageBox::Discard:
                        DestroyFileInstance();
                      break;
                  case QMessageBox::Cancel:
                      return;
                  default:
                      return;
                }
            }
        }else
        {
            DestroyFileInstance();
        }
    }
    currentFile = new File();
    currentFile->setFileName(filename);
    currentFile->ReadFile();
    ui.plainTextEdit->setPlainText(*currentFile->GetJsonData());
    setEditorEnabled(true);
}
void MainWindow::BrowseFile()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Json File", QDir::homePath(), "Json Files (*.json)");
    if(!filename.isEmpty()) loadFile(filename);
}
void MainWindow::newFile()
{
    if(isAnyFileOpen())
    {
        if(currentFile->exists())
        {
            if(isFileSaved())
            {
                DestroyFileInstance();
            }else
            {
                switch (PromptSaveChanges())
                {
                  case QMessageBox::Save:
                        saveChanges();
                        DestroyFileInstance();
                      break;
                  case QMessageBox::Discard:
                        DestroyFileInstance();
                      break;
                  case QMessageBox::Cancel:
                      return;
                  default:
                      break;
                }
            }
        }else
        {
            DestroyFileInstance();
        }
    }
    createNewFile("Untitled.json");
    setEditorEnabled(true);
}
void MainWindow::createNewFile(QString fname)
{
    currentFile = new File();
    currentFile->setFileName(fname);
}
void MainWindow::saveFile()
{
    if(currentFile->exists())
    {
        saveChanges();
    }else
    {
        saveAsFile();
    }
}
int MainWindow::PromptSaveChanges()
{
    QMessageBox msgBox;
    msgBox.setText("The json has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    return msgBox.exec();
}
void MainWindow::saveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Json File"), QDir::homePath(), tr("Json Files (*.json)"));
    if (fileName.isEmpty())
    {
        return;
    }else
    {
        createNewFile(fileName);
    }
    saveChanges();
}
void MainWindow::saveChanges()
{
    if(!isFileSaved())
    {
        currentFile->SetJsonData(ui.plainTextEdit->toPlainText());
        currentFile->WriteFile();
    }
}
void MainWindow::loadURL(QString url)
{
    //loadFile();
}
void MainWindow::on_actionBrowse_File_triggered()
{
    BrowseFile();
}
void MainWindow::on_actionNew_File_triggered()
{
    newFile();
}
void MainWindow::on_actionSave_As_triggered()
{
    saveAsFile();
}
void MainWindow::on_actionSave_triggered()
{
    saveFile();
}
void MainWindow::setEditorEnabled(bool enable)
{
    ui.plainTextEdit->setHidden(!enable);
    ui.treeView->setHidden(!enable);
}

