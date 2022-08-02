#ifndef USERDATA_H
#define USERDATA_H

#include <QString>

class UserData
{
public:
    UserData();
    unsigned int getUserID() const;
    void setUserID(unsigned int newUserID);

    const QString &getUserName() const;
    void setUserName(const QString &newUserName);

    const QString &getFullName() const;
    void setFullName(const QString &newFullName);

    const QString &getPhone() const;
    void setPhone(const QString &newPhone);

    const QString &getPhoneAster() const;
    void setPhoneAster(const QString &newPhoneAster);

    const QString &getEmail() const;
    void setEmail(const QString &newEmail);

    unsigned int getUiLang() const;
    void setUiLang(unsigned int newUiLang);

    bool getIsActive() const;
    void setIsActive(bool newIsActive);

    bool getIsChanged() const;
    void setIsChanged(bool newIsChanged);

private:
    unsigned int userID;
    QString userName;
    QString fullName;
    QString phone;
    QString phoneAster;
    QString email;
    unsigned int uiLang;
    bool isActive;
    bool isChanged;
};

#endif // USERDATA_H
