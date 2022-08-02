#include "database.h"
#include "LogginCategories/loggincategories.h"
#include "GlobalSettings/globalsettings.h"
#include "Settings/criptpass.h"
#include "Settings/settingsdialog.h"

#include <QSqlDatabase>
#include <QApplication>
#include <QSettings>
#include <QSqlError>
#include <QMessageBox>

Database::Database()
{
    openDataBase();
}

bool Database::getIsOpen() const
{
    return isOpen;
}

void Database::openDataBase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QIBASE");
    QSettings settings(GlobalSettings::CONFIG_FILE_NAME, QSettings::IniFormat);
    CriptPass *crP = new CriptPass();

    settings.beginGroup("DATABASE");
    db.setHostName(settings.value("Server").toString());
    QString strPort = settings.value("Port").toString();
    if(!strPort.isEmpty()){
        db.setPort(strPort.toInt());
    }
    db.setDatabaseName(settings.value("DataBase").toString());
    db.setUserName(settings.value("User").toString());
    db.setPassword(crP->decriptPass(settings.value("Password").toString()));
    settings.endGroup();
    if(!db.open()) {
        qCritical(logCritical()) << QApplication::tr("Не возможно подключиться к базе данных.") << Qt::endl << QApplication::tr("Причина:") << db.lastError().text();

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText(QApplication::tr("Ошибка подключения к базе данных!"));
        msgBox.setInformativeText(QApplication::tr("Проверить настройки подключения?"));
        msgBox.setStandardButtons(QMessageBox::Yes |  QMessageBox::No);
        msgBox.setDetailedText(db.lastError().text());
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes){
            SettingsDialog *setDlg = new SettingsDialog(false);
            setDlg->exec();
        }
        isOpen = false;
    } else {
        isOpen = true;
    }

}
