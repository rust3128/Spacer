
#ifndef RDPPROPERTY_H
#define RDPPROPERTY_H


#include <QObject>


class RdpProperty
{

public:
    RdpProperty();
    QString getHost() const;
    void setHost(const QString &newHost);

    int getPort() const;
    void setPort(int newPort);

    QString getUser() const;
    void setUser(const QString &newUser);

    QString getPass() const;
    void setPass(const QString &newPass);

    int getW() const;
    void setW(int newW);

    int getH() const;
    void setH(int newH);

private:
    QString host;
    int port;
    QString user;
    QString pass;
    int w;
    int h;

};

#endif // RDPPROPERTY_H
