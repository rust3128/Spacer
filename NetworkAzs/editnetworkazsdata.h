#ifndef EDITNETWORKAZSDATA_H
#define EDITNETWORKAZSDATA_H
#include "NetworkAzs/networkdata.h"
#include <QObject>

class EditNetworkAzsData : public QObject
{
    Q_OBJECT
public:
    explicit EditNetworkAzsData(int ID, QObject *parent = nullptr);
    NetworkData *getNetData() const;
    void writeNetworkData(NetworkData *newNetData);
signals:

private:
    void readNetworkData();
private:
    int networkID;
    NetworkData *netData;
};

#endif // EDITNETWORKAZSDATA_H
