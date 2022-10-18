#include "TreeView.h"

void TreeView::CreateTreeView(QString &data, QJsonModel& model)
{
    model.loadJson(QByteArray::fromStdString(data.toStdString()));
}
void TreeView::ClearTreeView(QJsonModel& model)
{
    model.loadJson(QByteArray::fromStdString(""));
}
