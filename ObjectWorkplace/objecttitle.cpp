#include "objecttitle.h"
#include "LogginCategories/loggincategories.h"
#include <QSqlQuery>
#include <QSqlError>

ObjectTitle::ObjectTitle(int ID) :
    objectID(ID)
{
    getTitleData();
}

void ObjectTitle::getTitleData()
{
    QSqlQuery q;
    q.prepare("select o.network_id, n.name, o.terminal_id, o.adress, o.phone, o.rank, o.isactive, o.comments, n.logo from objects o "
              "left join networkazs n on n.network_id = o.network_id "
              "where o.object_id = :objID");
    q.bindValue(":objID",objectID);
    if(!q.exec()) {
        qCritical(logCritical()) << QApplication::tr("Не возможно получить данные об АЗС!") << q.lastError().text();
        return;
    }
    q.next();
    networkID = q.value(0).toInt();
    networkName = q.value(1).toString();
    terminalID = q.value(2).toInt();
    address = q.value(3).toString();
    phone = q.value(4).toString();
    rank = q.value(5).toInt();
    isActive = q.value(6).toBool();
    comments = q.value(7).toString();
    logo = q.value(8).toByteArray();
}

const QByteArray &ObjectTitle::getLogo() const
{
    return logo;
}

const QString &ObjectTitle::getNetworkName() const
{
    return networkName;
}

const QString &ObjectTitle::getComments() const
{
    return comments;
}

bool ObjectTitle::getIsActive() const
{
    return isActive;
}

int ObjectTitle::getRank() const
{
    return rank;
}

const QString &ObjectTitle::getPhone() const
{
    return phone;
}

const QString &ObjectTitle::getAddress() const
{
    return address;
}

int ObjectTitle::getTerminalID() const
{
    return terminalID;
}

int ObjectTitle::getNetworkID() const
{
    return networkID;
}
