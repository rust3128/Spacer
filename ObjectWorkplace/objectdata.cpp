#include "objectdata.h"
#include "LogginCategories/loggincategories.h"

#include <QSqlQuery>
#include <QSqlError>

ObjectData::ObjectData(int ID, QObject *parent)
    : QObject{parent}
    ,objectID(ID)
{
    titleObj = new ObjectTitle(objectID);
    getListWorkpace();
}

ObjectTitle *ObjectData::getObjTitle()
{
    return titleObj;
}

void ObjectData::getListWorkpace()
{

    QSqlQuery q;
    q.prepare("select w.workplace_id, w.version_type_id, w.pos_id, w.ipadr from workplaces w "
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
        wk.setPosID(q.value(2).toInt());
        wk.setIPADR(q.value(3).toString());
        listWorkplace.append(wk);
    }
    qInfo(logInfo()) << "Workplace ist count =" << listWorkplace.size();

}
