#include "connstatusvnc.h"
#include <QTcpSocket>

ConnStatusVNC::ConnStatusVNC(QString IP, int port, QObject *parent)
    : QObject{parent},
      ipAdress(IP),
      portVNC(port)
{
    statusVNC =false;
}

void ConnStatusVNC::getConnStatus()
{
    QTcpSocket *tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(ipAdress,portVNC);
    if(tcpSocket->waitForConnected(2000)) {
        statusVNC = true;
    }
    tcpSocket->abort();
    emit signalSendStatus(statusVNC);
    emit finish();
}
