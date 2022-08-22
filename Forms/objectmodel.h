#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include <QSqlQueryModel>
#include <QObject>
#include <QColor>

class ObjectModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit ObjectModel(QObject *parent = nullptr);

private:
    QColor calculateColorForRow(QModelIndex idx) const;
    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // OBJECTMODEL_H
