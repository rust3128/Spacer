#include "centraldbconnect.h"
#include "LogginCategories/loggincategories.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QApplication>

CentralDBConnect::CentralDBConnect(int netID) :
    network_id(netID)
{
    crP = new CriptPass();
}

void CentralDBConnect::readFromDB()
{
    QSqlQuery q;
    q.prepare("select c.server_db, c.port_db, c.file_db, c.user_db, c.pass_db from  centrealdb c "
              "where c.network_id = :ntID");
    q.bindValue(0, network_id);
    if(!q.exec()) {
        qCritical(logCritical())<< QApplication::tr("Не удалось получить данные о центральной базе данных") << q.lastError().text();
        return;
    }
    if (!q.next()) {
        qCritical(logCritical())<< QApplication::tr("Нет данных о центральной базе данных для данного идентификатора сети");
        server = fileDB = user = pass = QApplication::tr("Нет данных");
        port =0;
        return;
    }
    server = q.value(0).toString();
    port = q.value(1).toInt();
    fileDB = q.value(2).toString();
    user = q.value(3).toString();
    pass = crP->decriptPass(q.value(4).toString());
    q.finish();
}

void CentralDBConnect::writeToDB()
{
    QSqlQuery q;
    q.prepare("update or insert into centrealdb (network_id, server_db, port_db, file_db, user_db, pass_db) "
              "values (:netID, :server, :port, :file, :user, :pass) "
              "matching(network_id)");
    q.bindValue(0,network_id);
    q.bindValue(1, server);
    q.bindValue(2,port);
    q.bindValue(3,fileDB);
    q.bindValue(4,user);
    q.bindValue(5,crP->criptPass(pass));
    if(!q.exec()) {
        qCritical(logCritical())<< QApplication::tr("Не удалось обновить данные о центральной базе данных") << q.lastError().text();
        return;
    }
    q.finish();
}

int CentralDBConnect::getNetwork_id() const
{
    return network_id;
}

QString CentralDBConnect::getServer() const
{
    return server;
}

void CentralDBConnect::setServer(const QString &newServer)
{
    server = newServer;
}

int CentralDBConnect::getPort() const
{
    return port;
}

void CentralDBConnect::setPort(int newPort)
{
    port = newPort;
}

QString CentralDBConnect::getFileDB() const
{
    return fileDB;
}

void CentralDBConnect::setFileDB(const QString &newFileDB)
{
    fileDB = newFileDB;
}

QString CentralDBConnect::getUser() const
{
    return user;
}

void CentralDBConnect::setUser(const QString &newUser)
{
    user = newUser;
}

QString CentralDBConnect::getPass() const
{
    return pass;
}

void CentralDBConnect::setPass(const QString &newPass)
{
    pass = newPass;
}
