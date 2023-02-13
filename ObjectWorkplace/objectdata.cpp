#include "objectdata.h"
#include "LogginCategories/loggincategories.h"

#include <QSqlQuery>
#include <QSqlError>

ObjectData::ObjectData(int ID, QObject *parent)
    : QObject{parent}
    ,objectID(ID)
{
    titleObj = new ObjectTitle(objectID);
    ListWorkpace();
}

ObjectTitle *ObjectData::getObjTitle()
{
    return titleObj;
}

void ObjectData::ListWorkpace()
{

    QSqlQuery q;
    q.prepare("select w.workplace_id, w.version_type_id, t.version_name, w.pos_id, w.ipadr, w.vnc_port from workplaces w "
              "left join version_type t on t.version_type_id = w.version_type_id "
              "where w.network_id = :netID and w.terminal_id = :termID "
              "order by w.version_type_id, w.pos_id");
    q.bindValue(":netID", titleObj->getNetworkID());
    q.bindValue(":termID", titleObj->getTerminalID());
    if(!q.exec()){
        qCritical(logCritical()) << tr("Не возможно подлучить данные о рабочих местах") << q.lastError().text();
        return;
    }
    Workpalce wk;
    while(q.next()){
        wk.setWorrplaceID(q.value(0).toInt());
        wk.setVerTypeID(q.value(1).toInt());
        wk.setVerTypeName(q.value(2).toString());
        wk.setPosID(q.value(3).toInt());
        wk.setIPADR(q.value(4).toString());
        wk.setPortVNC(q.value(5).toInt());
        listWorkplace.append(wk);
    }
}

const QList<Workpalce> &ObjectData::getListWorkplace() const
{
    return listWorkplace;
}
