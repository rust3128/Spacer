#ifndef WORKPALCE_H
#define WORKPALCE_H
#include "qobject.h"
#include <QString>

class Workpalce
{
public:
    Workpalce();
    int getVerTypeID() const;
    void setVerTypeID(int newVerTypeID);

    const QString &getVerTypeName() const;
    void setVerTypeName(const QString &newVerTypeName);

    int getPosID() const;
    void setPosID(int newPosID);

    const QString &getIPADR() const;
    void setIPADR(const QString &newIPADR);

    int getWorrplaceID() const;
    void setWorrplaceID(int newWorrplaceID);

    int getPortVNC() const;
    void setPortVNC(int newPortVNC);

    QString getPassVNC() const;
    void setPassVNC(const QString &newPassVNC);

    int getTerminalID() const;
    void setTerminalID(int newTerminalID);

private:
    int worrplaceID;
    int terminalID;
    int verTypeID;
    QString verTypeName;
    int posID;
    QString IPADR;
    int portVNC;
    QString passVNC;
};

#endif // WORKPALCE_H
