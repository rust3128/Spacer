#include "workpalce.h"

Workpalce::Workpalce()
{

}

int Workpalce::getVerTypeID() const
{
    return verTypeID;
}

void Workpalce::setVerTypeID(int newVerTypeID)
{
    verTypeID = newVerTypeID;
}

const QString &Workpalce::getVerTypeName() const
{
    return verTypeName;
}

void Workpalce::setVerTypeName(const QString &newVerTypeName)
{
    verTypeName = newVerTypeName;
}

int Workpalce::getPosID() const
{
    return posID;
}

void Workpalce::setPosID(int newPosID)
{
    posID = newPosID;
}

const QString &Workpalce::getIPADR() const
{
    return IPADR;
}

void Workpalce::setIPADR(const QString &newIPADR)
{
    IPADR = newIPADR;
}

int Workpalce::getWorrplaceID() const
{
    return worrplaceID;
}

void Workpalce::setWorrplaceID(int newWorrplaceID)
{
    worrplaceID = newWorrplaceID;
}

int Workpalce::getPortVNC() const
{
    return portVNC;
}

void Workpalce::setPortVNC(int newPortVNC)
{
    portVNC = newPortVNC;
}
