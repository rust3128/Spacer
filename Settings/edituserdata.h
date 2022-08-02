#ifndef EDITUSERDATA_H
#define EDITUSERDATA_H

#include "userdata.h"
#include <QObject>


class EditUserData : public QObject
{
    Q_OBJECT
public:
    explicit EditUserData(uint ID, QObject *parent = nullptr);

    UserData *getUserData() const;
    void setUserData(UserData *newUserData);

signals:

private:
    void readUserDataFromDB();
private:
    uint userID;
    UserData *userData;
};

#endif // EDITUSERDATA_H
