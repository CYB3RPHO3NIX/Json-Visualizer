#include "File.h"

File::File()
{

}

void File::NewFile(QWidget* parent)
{
    IsSaved = false;
    QString fileName = "Untitled.json";
    //this part needs to be coded next day. Good Night
}
void File::Save(QWidget* parent)
{
    if(!IsSaved)
    {
        SaveAs(parent);
    }else
    {
        saveFile(parent, file.fileName());
    }
}
void File::SaveAs(QWidget* parent)
{
    QString fileName = QFileDialog::getSaveFileName(parent);
    if (fileName.isEmpty())
    {
        return;
    }
    saveFile(parent, fileName);
}
void File::saveFile(QWidget* parent, const QString &fileName)
{
    QFile file(fileName);
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
    QApplication::restoreOverrideCursor();
    file.setFileName(fileName);
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
        QApplication::restoreOverrideCursor();
    }
}
