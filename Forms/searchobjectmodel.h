#ifndef SEARCHOBJECTMODEL_H
#define SEARCHOBJECTMODEL_H

#include <QSqlQueryModel>
#include <QObject>

class SearchObjectModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit SearchObjectModel(QObject *parent = nullptr);
    QColor calculateColorForRow(QModelIndex idx) const;
    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;

    // QAbstractItemModel interface
public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

#endif // SEARCHOBJECTMODEL_H
