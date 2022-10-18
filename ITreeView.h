#ifndef ITREEVIEW_H
#define ITREEVIEW_H

#include "qtreeview.h"
#include "qstring.h"
#include "qjsonmodel.h"

class ITreeView
{
public:
    virtual void CreateTreeView(QString &data, QJsonModel& model) = 0;
    virtual void ClearTreeView(QJsonModel& model) = 0;
};

#endif // ITREEVIEW_H
