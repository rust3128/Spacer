#include "globalsettings.h"
#include <QSettings>



const QString GlobalSettings::CONFIG_FILE_NAME = "Spacer.ini";          //Файл настроек
const QString GlobalSettings::LOG_FILE_NAME = "Spacer.log";             //Лог файл
const QString GlobalSettings::VNC_RUN_PATH = getVNCRunPath();           //Путь запуска VNC
const QString GlobalSettings::KEY_SOLT = "SapForever";
const QString GlobalSettings::VEKTOR_KEY = "Poltava1970Rust";

GlobalSettings::GlobalSettings()
{

}

 QString GlobalSettings::getVNCRunPath()
{
    QSettings settings (GlobalSettings::CONFIG_FILE_NAME, QSettings::IniFormat);
    settings.beginGroup("VNC");
    QString pathVNC = settings.value("VNCPath").toString();
    return pathVNC;
 }


