#include "modelsrvers.h"
#include "qsqlquery.h"

ModelSrvers::ModelSrvers(QObject *parent)
    : QSqlQueryModel{parent}
{

}

QVariant ModelSrvers::data(const QModelIndex &idx, int role) const
{

    if (role == Qt::DisplayRole && idx.column() == 3) // 1 - номер столбца с данными для запроса
    {
        QString ids = QSqlQueryModel::data(idx, role).toString();
//        QStringList typeList = ids.split(",");

//        QVector <int> typeID;
//        for(const QString& curID : typeList) {
//            bool ok;
//            int value = curID.toInt(&ok);
//            if(ok) {
//                typeID.append(value);
//            }
//        }

        QString names;

        QSqlQuery query;
        query.prepare("SELECT DESCRIPTION FROM server_type WHERE type_id IN (" + ids + ")");
        if (query.exec() && query.next())
        {
            names = QStringLiteral("\u2022")+query.value(0).toString();
            while (query.next())
            {
                names += "\n" + QStringLiteral("\u2022") + query.value(0).toString();
            }
        }

        return QVariant::fromValue(names);
    }

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
        if(idx.column() == 4){
             return Qt::AlignCenter;
        }
    }
    return QSqlQueryModel::data(idx,role);
}
