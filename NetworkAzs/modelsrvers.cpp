#include "modelsrvers.h"

ModelSrvers::ModelSrvers(QObject *parent)
    : QSqlQueryModel{parent}
{

}

QVariant ModelSrvers::data(const QModelIndex &idx, int role) const
{
    if(role == Qt::DisplayRole){
        if(idx.column() == 4) {
            if(QSqlQueryModel::data(this->index(idx.row(),4)).toBool()){
                return tr("Да");
            } else {
                return tr("Нет");
            }
        }
    }

    if(role == Qt::TextAlignmentRole){
        if(idx.column() == 3 || idx.column() == 4){
             return Qt::AlignCenter;
        }
    }
    return QSqlQueryModel::data(idx,role);
}
