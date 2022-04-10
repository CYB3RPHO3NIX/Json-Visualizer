#include "File.h"

File::File(QWidget* hnd)
{
    parent = hnd;
}
void File::validateJson()
{
    if(worker.IsValid(jsonData))
    {
        IsValidJson = true;
    }else
    {
        IsValidJson = false;
    }
}
void File::NewFile()
{
    if(doesFileExists())
    {
        if(IsSaved())
        {
            resetFile();
        }else
        {
            Save();
        }
    }
    LoadEmptyFile();
}
void File::LoadEmptyFile()
{
    fileName = "Untitled.json";
    jsonData = "";
    validateJson();
    updateWindowTitle(fileName);
}
void File::resetFile()
{
    jsonData.clear();
}
void File::promptSaveChanges()
{
    QMessageBox msg;
    msg.setText("Do you want to save the changes to "+fileName+" ?");
    msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Save);
    int res = msg.exec();
    switch(res)
    {
        case QMessageBox::Save:
            saveFile();
          break;
        case QMessageBox::Discard:
            discardChanges();
          break;
        case QMessageBox::Cancel:
            return;
          break;
        default:    break;
    }
}
bool File::IsSaved()
{
    QTextStream inputStream(&filePath);
    if(inputStream.readAll() == jsonData)
    {
        return true;
    }else
    {
        return false;
    }
}
void File::Save()
{
    if(doesFileExists())
    {
        saveFile();
    }else
    {
        SaveAs();
    }
}
void File::discardChanges()
{
    resetFile();
}
void File::SaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(parent, "Select destination.", "/", "Json Files (*.json)");
    if (fileName.isEmpty())
    {
        return;
    }else
    {
        this->filePath = fileName;
        updateFileInfo();
    }
    saveFile();
}
void File::saveFile()
{
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox msg(parent);
        msg.setWindowTitle("Error");
        msg.setText("Cannot Save file "+file.fileName());
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        return;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << jsonData;
    updateFileInfo();
    QApplication::restoreOverrideCursor();
}
void File::LoadFile()
{
    QFile file;
    QString fileName = QFileDialog::getOpenFileName(parent, "Select json file.", "/", "Json files (*.json)");
    file.setFileName(fileName);
    if (!fileName.isEmpty())
    {
        updateWindowTitle(fileInfo.fileName());
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox msg(parent);
            msg.setWindowTitle("Error");
            msg.setText("Cannot read file "+file.fileName());
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
            return;
        }
        QTextStream inputStream(&file);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        jsonData = inputStream.readAll();
        validateJson();
        updateFileInfo();
        QApplication::restoreOverrideCursor();
    }
}
void File::updateWindowTitle(QString filename)
{
    parent->setWindowTitle("JSON Explorer - " + filename);
}
bool File::doesFileExists()
{
   return QFile::exists(filePath);
}
void File::updateFileInfo()
{
    fileInfo.setFile(filePath);
}
