#include "editnetworkazsdata.h"
#include "LogginCategories/loggincategories.h"

#include <QSqlQuery>
#include <QSqlError>

EditNetworkAzsData::EditNetworkAzsData(int ID, QObject *parent)
    : QObject{parent},
      networkID(ID)
{
    netData = new NetworkData();
    readNetworkData();
}

NetworkData *EditNetworkAzsData::getNetData() const
{
    return netData;
}

void EditNetworkAzsData::writeNetworkData(NetworkData *newNetData)
{
    QSqlQuery q;
    q.prepare("UPDATE NETWORKAZS SET NAME = :netName, LOGO = :logo, TYPECONNECT = :typeConnect, ISACTIVE = :isActive WHERE (NETWORK_ID = :netID)");
    q.bindValue(":netName", newNetData->getNetName());
    q.bindValue(":logo", newNetData->getLogo());
    q.bindValue(":typeConnect",newNetData->getTypeConnect());
    q.bindValue(":isActive", newNetData->getIsActive());
    q.bindValue(":netID",newNetData->getNetID());
    if(!q.exec()) {
         qCritical(logCritical()) << tr("Не возможно обновить данные о сети АЗС.") << q.lastError().text();
    } else {
         qInfo(logInfo()) << tr("Информация о сети АЗС обновлена.");
    }

}

void EditNetworkAzsData::readNetworkData()
{
    QSqlQuery q;
    q.prepare("select n.name, n.logo, n.typeconnect, n.isactive from networkazs n where n.network_id = :ID");
    q.bindValue(0,networkID);
    if(!q.exec()){
        qCritical(logCritical()) << tr("Не удалось получить данные о сети АЗС.") << q.lastError().text();
        return;
    }
    q.next();
    netData->setNetID(networkID);
    netData->setNetName(q.value(0).toString());
    netData->setLogo(q.value(1).toByteArray());
    netData->setTypeConnect(q.value(2).toBool());
    netData->setIsActive(q.value(3).toBool());
}
