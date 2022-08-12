#include "modelnetworklist.h"

#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include <QBitmap>

ModelNetworkList::ModelNetworkList(QObject *parent)
    : QSqlQueryModel{parent}
{

}


QVariant ModelNetworkList::data(const QModelIndex &idx, int role) const
{
    QVariant value = QSqlQueryModel::data(idx,role);;

        switch ( role )
        {
            case Qt::DisplayRole: //string
            {
                value = QSqlQueryModel::data(this->index(idx.row(),1)).toString();
            }
            break;

            case Qt::DecorationRole: //image
            {

                QPixmap outPixmap = QPixmap();
                outPixmap.loadFromData(QSqlQueryModel::data(this->index(idx.row(),2)).toByteArray());
                QPixmap logo = outPixmap.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                QPixmap mask(64,64);
                QPainter painter (&mask);
                mask.fill(Qt::white);
                painter.drawPixmap(
                            (mask.width()-logo.width())/2,
                            (mask.height()-logo.height())/2,
                             logo);

                value = mask;
            }
            break;

            default:
                break;
        }

    return value;
}
