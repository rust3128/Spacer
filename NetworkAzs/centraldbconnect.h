#ifndef CENTRALDBCONNECT_H
#define CENTRALDBCONNECT_H

#include "Settings/criptpass.h"

#include <QString>


class CentralDBConnect
{
public:
    CentralDBConnect(int netID);
    void readFromDB();
    void writeToDB();

    int getNetwork_id() const;

    QString getServer() const;
    void setServer(const QString &newServer);

    int getPort() const;
    void setPort(int newPort);

    QString getFileDB() const;
    void setFileDB(const QString &newFileDB);

    QString getUser() const;
    void setUser(const QString &newUser);

    QString getPass() const;
    void setPass(const QString &newPass);

private:
    int network_id;
    QString server;
    int port;
    QString fileDB;
    QString user;
    QString pass;

    CriptPass *crP;

};

#endif // CENTRALDBCONNECT_H
