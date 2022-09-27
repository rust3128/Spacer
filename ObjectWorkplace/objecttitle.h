#ifndef OBJECTTITLE_H
#define OBJECTTITLE_H

#include <QObject>
#include <QApplication>


class ObjectTitle
{

public:
    ObjectTitle(int ID);
    int getNetworkID() const;
    int getTerminalID() const;
    const QString &getAddress() const;
    const QString &getPhone() const;
    int getRank() const;
    bool getIsActive() const;
    const QString &getComments() const;

    const QString &getNetworkName() const;

    const QByteArray &getLogo() const;

private:
    void getTitleData();
private:
    int objectID;
    int networkID;
    QString networkName;
    int terminalID;
    QString address;
    QString phone;
    int rank;
    bool isActive;
    QString comments;
    QByteArray logo;
};

#endif // OBJECTTITLE_H
