#include "userdata.h"

UserData::UserData()
{

}

unsigned int UserData::getUserID() const
{
    return userID;
}

void UserData::setUserID(unsigned int newUserID)
{
    userID = newUserID;
}

const QString &UserData::getUserName() const
{
    return userName;
}

void UserData::setUserName(const QString &newUserName)
{
    userName = newUserName;
}

const QString &UserData::getFullName() const
{
    return fullName;
}

void UserData::setFullName(const QString &newFullName)
{
    fullName = newFullName;
}

const QString &UserData::getPhone() const
{
    return phone;
}

void UserData::setPhone(const QString &newPhone)
{
    phone = newPhone;
}

const QString &UserData::getPhoneAster() const
{
    return phoneAster;
}

void UserData::setPhoneAster(const QString &newPhoneAster)
{
    phoneAster = newPhoneAster;
}

const QString &UserData::getEmail() const
{
    return email;
}

void UserData::setEmail(const QString &newEmail)
{
    email = newEmail;
}

unsigned int UserData::getUiLang() const
{
    return uiLang;
}

void UserData::setUiLang(unsigned int newUiLang)
{
    uiLang = newUiLang;
}

bool UserData::getIsActive() const
{
    return isActive;
}

void UserData::setIsActive(bool newIsActive)
{
    isActive = newIsActive;
}

bool UserData::getIsChanged() const
{
    return isChanged;
}

void UserData::setIsChanged(bool newIsChanged)
{
    isChanged = newIsChanged;
}

bool UserData::getIsAdmin() const
{
    return isAdmin;
}

void UserData::setIsAdmin(bool newIsAdmin)
{
    isAdmin = newIsAdmin;
}
