#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "JsonSummary.h"
#include "JsonWorker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
    
private:
    Ui::MainWindowClass ui;
    JsonSummary summary;
    JsonWorker worker;
    bool IsCurrentJsonValid;
    QJsonModel* treeModel;
private slots:
    void DrawTreeView(QString &jsonString);
    void setStatus(const char* statusString);
    void on_plainTextEdit_textChanged();
    void on_actionZoom_In_triggered();
    void on_actionZoom_Out_triggered();
    void on_actionSummary_triggered();
    void on_txtJsonQuery_textChanged(const QString &arg1);
};
