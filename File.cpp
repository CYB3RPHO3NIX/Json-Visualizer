#include "File.h"

File::File()
{
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
void File::NewFile(QWidget* parent)
{
    IsSaved = false;
    QString fileName = "Untitled.json";
    jsonData = "";
    //check if there is any file that is currently loaded.
    if(file.isOpen())
    {
        //check if that loaded file is saved or not.
        if(IsSaved)
        {
            file.close();

        }else
        {
            //show a user prompt to ask whether to save the changes or not.
            //then unload.
            //then load a new file.
            QMessageBox msg;
            msg.setText("Do you want to save the changes to "+file.fileName()+" ?");
            msg.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msg.setDefaultButton(QMessageBox::Save);
            int res = msg.exec();
            switch(res)
            {
                case QMessageBox::Save:
                    Save(parent);
                  break;
                case QMessageBox::Discard:

                  break;
                case QMessageBox::Cancel:
                  break;
                default:    break;
            }
        }
    }
    else
    {
        //load a new File.
    }
    //call the validate function.
}
void File::Save(QWidget* parent)
{

    if(!IsSaved)
    {
        SaveAs(parent);
    }else
    {
        saveFile(parent);
    }
}
void File::SaveAs(QWidget* parent)
{
    QString fileName = QFileDialog::getSaveFileName(parent, "Select destination.", "/", "Json Files (*.json)");
    if (fileName.isEmpty())
    {
        return;
    }else
    {
        file.setFileName(fileName);
    }
    saveFile(parent);
}
void File::saveFile(QWidget* parent)
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
void File::LoadFile(QWidget* parent)
{
    QString fileName = QFileDialog::getOpenFileName(parent, "Select json file.", "/", "Json files (*.json)");
    if (!fileName.isEmpty())
    {
        IsSaved = true;
        file.setFileName(fileName);
        fileInfo.setFile(file);
        parent->setWindowTitle("JSON Explorer - " + fileInfo.fileName());
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
void File::updateFileInfo()
{
    fileInfo.setFile(file.fileName());
}
