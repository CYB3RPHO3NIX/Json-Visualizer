#ifndef TREEVIEW_H
#define TREEVIEW_H
#include "ITreeView.h"
#include "qstring.h"
#include "qjsonmodel.h"

class TreeView : public ITreeView
{
public:
    void CreateTreeView(QString &data, QJsonModel& model);
    void ClearTreeView(QJsonModel& model);
};

#endif // TREEVIEW_H
