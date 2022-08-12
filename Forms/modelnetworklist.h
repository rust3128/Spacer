#ifndef MODELNETWORKLIST_H
#define MODELNETWORKLIST_H

#include <QSqlQueryModel>
#include <QObject>

class ModelNetworkList : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit ModelNetworkList(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // MODELNETWORKLIST_H
