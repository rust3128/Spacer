#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

#include <QString>

class GlobalSettings
{
public:
    GlobalSettings();
    static const QString CONFIG_FILE_NAME;
    static const QString LOG_FILE_NAME;
    static const QString VNC_RUN_PATH;
private:
    static QString getVNCRunPath();
};

#endif // GLOBALSETTINGS_H
