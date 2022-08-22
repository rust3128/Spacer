#include "objectmodel.h"

#include <QBrush>

ObjectModel::ObjectModel(QObject *parent)
    : QSqlQueryModel{parent}
{

}

QColor ObjectModel::calculateColorForRow(QModelIndex idx) const
{
    QColor color = QColor("azure");
    if(!QSqlQueryModel::data(this->index(idx.row(),6)).toBool()){
        color = QColor("tomato");
    }
    switch (QSqlQueryModel::data(this->index(idx.row(),5)).toInt()) {
    case 1:
        color = QColor("lightgreen");
        break;
    case 2:
        color = QColor("lightgoldenrodyellow");
        break;
    default:
        break;
    }
    return color;
}

QVariant ObjectModel::data(const QModelIndex &idx, int role) const
{
    if (role == Qt::BackgroundRole) {
       QColor color = calculateColorForRow(idx);
       return QBrush(color);
    }

    if(role == Qt::TextAlignmentRole){
         if(idx.column() == 1)
              return Qt::AlignCenter;
     }
    return QSqlQueryModel::data(idx,role);
}
