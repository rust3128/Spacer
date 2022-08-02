#ifndef MODELNETWORKAZS_H
#define MODELNETWORKAZS_H

#include <QSqlQueryModel>
#include <QObject>

class ModelNetworkAzs : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit ModelNetworkAzs(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // MODELNETWORKAZS_H
