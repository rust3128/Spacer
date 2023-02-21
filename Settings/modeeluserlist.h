#ifndef MODEELUSERLIST_H
#define MODEELUSERLIST_H

#include <QSqlQueryModel>
#include <QObject>

class ModeelUserList : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit ModeelUserList(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
private:
    QColor calculateColorForRow(QModelIndex idx) const;
};

#endif // MODEELUSERLIST_H
