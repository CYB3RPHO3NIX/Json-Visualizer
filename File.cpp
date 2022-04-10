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
    file.setFileName("Untitled.json");
    jsonData = "";
    validateJson();
    updateWindowTitle();
}
void File::resetFile()
{
    jsonData.clear();
    file.remove();
}
void File::promptSaveChanges()
{
    QMessageBox msg;
    msg.setText("Do you want to save the changes to "+file.fileName()+" ?");
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
    QTextStream inputStream(&file);
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
        file.setFileName(fileName);
    }
    saveFile();
}
void File::saveFile()
{
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
    QString fileName = QFileDialog::getOpenFileName(parent, "Select json file.", "/", "Json files (*.json)");
    if (!fileName.isEmpty())
    {
        setFile(fileName);
        updateWindowTitle();
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
void File::updateWindowTitle()
{
    if(IsSaved())
    {
        parent->setWindowTitle("JSON Explorer - " + fileInfo.fileName());
    }else
    {
        parent->setWindowTitle("JSON Explorer - " + fileInfo.fileName()+"*");
    }

}
void File::setFile(QString& fileName)
{
    file.setFileName(fileName);
    fileInfo.setFile(file);
}
bool File::doesFileExists()
{
   return file.exists();
}
void File::updateFileInfo()
{
    fileInfo.setFile(file.fileName());
}
