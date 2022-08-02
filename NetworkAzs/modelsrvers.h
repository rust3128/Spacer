#ifndef MODELSRVERS_H
#define MODELSRVERS_H

#include <QSqlQueryModel>

class ModelSrvers : public QSqlQueryModel
{
public:
    explicit ModelSrvers(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // MODELSRVERS_H
