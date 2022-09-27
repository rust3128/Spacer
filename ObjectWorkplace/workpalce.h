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

private:
    int worrplaceID;
    int verTypeID;
    QString verTypeName;
    int posID;
    QString IPADR;
};

#endif // WORKPALCE_H
