#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <QString>

class NetworkData
{
public:
    NetworkData();

    int getNetID() const;
    void setNetID(int newNetID);

    const QString &getNetName() const;
    void setNetName(const QString &newNetName);

    bool getTypeConnect() const;
    void setTypeConnect(bool newTypeConnect);

    bool getIsActive() const;
    void setIsActive(bool newIsActive);

    const QByteArray &getLogo() const;
    void setLogo(const QByteArray &newLogo);

private:
    int netID;
    QString netName;
    QByteArray logo;
    bool typeConnect;
    bool isActive;

};

#endif // NETWORKDATA_H
