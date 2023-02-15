#include "searchobjectmodel.h"

#include <QColor>
#include <QBrush>

SearchObjectModel::SearchObjectModel(QObject *parent)
    : QSqlQueryModel{parent}
{

}

QColor SearchObjectModel::calculateColorForRow(QModelIndex idx) const
{
    QColor color = QColor("azure");
    if(!QSqlQueryModel::data(this->index(idx.row(),8)).toBool()){
        color = QColor("tomato");
    }
    switch (QSqlQueryModel::data(this->index(idx.row(),7)).toInt()) {
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

QVariant SearchObjectModel::data(const QModelIndex &idx, int role) const
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


QVariant SearchObjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //Cоздаем заголовки столбцов модели
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return section;
    }

    switch( section ) {
    case 1:
        return tr( "" );
    case 2:
        return tr( "Сеть" );
    case 3:
        return tr( "Терминал" );
    case 4:
        return tr( "Адрес" );
    case 5:
        return tr( "Телефон" );
    case 6:
        return tr( "Примечание" );
    }
    return QSqlQueryModel::headerData(section,orientation,role);
}
