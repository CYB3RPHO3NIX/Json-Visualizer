#include "File.h"

File::File()
{

}

void File::NewFile(QWidget* parent)
{

}
void File::LoadFile(QWidget* parent)
{
    QString fileName = QFileDialog::getOpenFileName(parent, "Select json file.", "/", "Json files (*.json)");
    if (!fileName.isEmpty())
    {
        file.setFileName(fileName);
        fileInfo.setFile(file);
        parent->setWindowTitle("JSON Explorer - " + fileInfo.fileName());
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox msg(parent);
            msg.setWindowTitle("File Read Error");
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
