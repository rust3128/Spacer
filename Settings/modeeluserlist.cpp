#include "modeeluserlist.h"

#include <QColor>
#include <QBrush>

ModeelUserList::ModeelUserList(QObject *parent)
    : QSqlQueryModel{parent}
{

}

QColor ModeelUserList::calculateColorForRow(QModelIndex idx) const
{
    QColor color = QColor("azure");
    switch (QSqlQueryModel::data(this->index(idx.row(),8)).toInt()) {
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

QVariant ModeelUserList::data(const QModelIndex &idx, int role) const
{
    if ( !idx.isValid() ) {
        return QVariant();
    }
    if(role == Qt::DisplayRole){
        if(idx.column() == 6){
            switch (QSqlQueryModel::data(this->index(idx.row(),6)).toInt()) {
            case 1:
                return tr("Украинский");
                break;
            case 2:
                return tr("Английский");
                break;
            case 3:
                return tr("Русский");
                break;
            default:
                break;
            }
        }
        if(idx.column() == 7){
            if(QSqlQueryModel::data(this->index(idx.row(),7)).toBool()){
                return tr("Да");
            } else {
                return tr("Нет");
            }
        }
        if(idx.column() == 8) {
            if(QSqlQueryModel::data(this->index(idx.row(),8)).toBool()){
                return tr("ADMIN");
            } else {
                return tr("USER");
            }
        }
    }
    if (role == Qt::BackgroundRole) {
       QColor color = calculateColorForRow(idx);
       return QBrush(color);
    }

    if(role == Qt::TextAlignmentRole){
        if(idx.column() == 7 || idx.column() == 8){
             return Qt::AlignCenter;
        }
    }

    return QSqlQueryModel::data(idx,role);
}

QVariant ModeelUserList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return section;
    }
    switch( section ) {
    case 1:
        return tr( "Логин" );
    case 2:
        return tr( "ФИО" );
    case 3:
        return tr( "Мобильный" );
    case 4:
        return tr( "Внутренний" );
    case 5:
        return tr( "E-mail" );
    case 6:
        return tr( "Интерфейс" );
    case 7:
        return tr( "Работает" );
    case 8:
        return tr( "Права" );
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}
