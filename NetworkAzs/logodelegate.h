#ifndef LOGODELEGATE_H
#define LOGODELEGATE_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QSize>
#include <QPixmap>
#include <QPainter>

class LogoDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
     LogoDelegate(QObject *parent = nullptr);

     // QAbstractItemDelegate interface
public:
     void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &idx) const;
};

#endif // LOGODELEGATE_H
