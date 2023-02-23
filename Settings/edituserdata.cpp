#include "edituserdata.h"
#include "LogginCategories/loggincategories.h"

#include <QSqlQuery>
#include <QSqlError>

EditUserData::EditUserData(uint ID, QObject *parent)
    : QObject{parent},
      userID(ID)
{
    userData = new UserData();
    readUserDataFromDB();
}

void EditUserData::readUserDataFromDB()
{
    QSqlQuery q;
    q.prepare("SELECT u.username, u.fio, u.phone, u.phoneaster, u.email, u.ui_lang, u.isactive, u.isadmin FROM users u WHERE u.user_id = :userID");
    q.bindValue(0,userID);
    if(!q.exec()){
        qCritical(logCritical()) << tr("Не удалось получить данные пользователя.") << q.lastError().text();
        return;
    }
    q.next();
    userData->setUserID(userID);
    userData->setUserName(q.value(0).toString());
    userData->setFullName(q.value(1).toString());
    userData->setPhone(q.value(2).toString());
    userData->setPhoneAster(q.value(3).toString());
    userData->setEmail(q.value(4).toString());
    userData->setUiLang(q.value(5).toUInt());
    userData->setIsActive(q.value(6).toBool());
    userData->setIsAdmin(q.value(7).toBool());
}

UserData *EditUserData::getUserData() const
{
    return userData;
}

void EditUserData::setUserData(UserData *newUserData)
{
    userData = newUserData;
    QSqlQuery q;
    q.prepare("UPDATE USERS SET FIO = :fio, PHONE = :phone, PHONEASTER = :aster, EMAIL = :email, "
              "UI_LANG = :lang, ISACTIVE = :isactive, ISADMIN = :isAdmin WHERE (USER_ID = :userID)");
    q.bindValue(":fio", userData->getFullName());
    q.bindValue(":phone", userData->getPhone());
    q.bindValue(":aster", userData->getPhoneAster());
    q.bindValue(":email", userData->getEmail());
    q.bindValue(":lang", userData->getUiLang());
    q.bindValue(":isactive", QVariant(userData->getIsActive()).toInt());
    q.bindValue(":isAdmin", QVariant(userData->getIsAdmin()).toInt());
    q.bindValue(":userID", userData->getUserID());
    if(q.exec()){
        qInfo(logInfo()) << tr("Данные пользователя успешно обновлены.");
    } else {
        qCritical(logCritical()) << tr("Не удалось обновить данные пользователя.") << q.lastError().text();
    }
}
