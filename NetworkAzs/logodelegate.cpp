#include "logodelegate.h"

#include <QApplication>
#include <QStyledItemDelegate>

LogoDelegate::LogoDelegate(QObject *parent) :QStyledItemDelegate (parent)
{

}


void LogoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &idx) const
{

         QPixmap pixmap;
         pixmap.loadFromData(idx.model()->data(idx,Qt::DisplayRole).toByteArray());
         if(!pixmap.isNull()) {
             pixmap = pixmap.scaled(option.rect.width(), option.rect.height(), Qt::KeepAspectRatio);

             // Position our pixmap
            const int x = option.rect.center().x() - pixmap.rect().width() / 2;
            const int y = option.rect.center().y() - pixmap.rect().height() / 2;

            if (option.state & QStyle::State_Selected) {
                painter->fillRect(option.rect, option.palette.highlight());
            }

         painter->drawPixmap(QRect(x, y, pixmap.rect().width(), pixmap.rect().height()), pixmap);
         }
}
