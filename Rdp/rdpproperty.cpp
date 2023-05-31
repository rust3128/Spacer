
#include "rdpproperty.h"

RdpProperty::RdpProperty()
{

}

QString RdpProperty::getHost() const
{
    return host;
}

void RdpProperty::setHost(const QString &newHost)
{
    host = newHost;
}

int RdpProperty::getPort() const
{
    return port;
}

void RdpProperty::setPort(int newPort)
{
    port = newPort;
}

QString RdpProperty::getUser() const
{
    return user;
}

void RdpProperty::setUser(const QString &newUser)
{
    user = newUser;
}

QString RdpProperty::getPass() const
{
    return pass;
}

void RdpProperty::setPass(const QString &newPass)
{
    pass = newPass;
}

int RdpProperty::getW() const
{
    return w;
}

void RdpProperty::setW(int newW)
{
    w = newW;
}

int RdpProperty::getH() const
{
    return h;
}

void RdpProperty::setH(int newH)
{
    h = newH;
}

