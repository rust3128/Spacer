#include "networkdata.h"

NetworkData::NetworkData()
{

}

int NetworkData::getNetID() const
{
    return netID;
}

void NetworkData::setNetID(int newNetID)
{
    netID = newNetID;
}

const QString &NetworkData::getNetName() const
{
    return netName;
}

void NetworkData::setNetName(const QString &newNetName)
{
    netName = newNetName;
}

bool NetworkData::getTypeConnect() const
{
    return typeConnect;
}

void NetworkData::setTypeConnect(bool newTypeConnect)
{
    typeConnect = newTypeConnect;
}

bool NetworkData::getIsActive() const
{
    return isActive;
}

void NetworkData::setIsActive(bool newIsActive)
{
    isActive = newIsActive;
}

const QByteArray &NetworkData::getLogo() const
{
    return logo;
}

void NetworkData::setLogo(const QByteArray &newLogo)
{
    logo = newLogo;
}
