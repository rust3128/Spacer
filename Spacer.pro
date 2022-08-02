QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
win32: RC_ICONS = $$PWD/Images/Spacer.ico

SOURCES += \
    Database/database.cpp \
    GlobalSettings/globalsettings.cpp \
    LogginCategories/loggincategories.cpp \
    NetworkAzs/clickablelabel.cpp \
    NetworkAzs/editnetworkazsdata.cpp \
    NetworkAzs/editnetworkazsdialog.cpp \
    NetworkAzs/editserverdialog.cpp \
    NetworkAzs/logodelegate.cpp \
    NetworkAzs/modelnetworkazs.cpp \
    NetworkAzs/modelsrvers.cpp \
    NetworkAzs/networkazsdialog.cpp \
    NetworkAzs/networkdata.cpp \
    Settings/criptpass.cpp \
    Settings/edituserdata.cpp \
    Settings/settingsdialog.cpp \
    Settings/userdata.cpp \
    Settings/userdatadialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Database/database.h \
    GlobalSettings/globalsettings.h \
    LogginCategories/loggincategories.h \
    NetworkAzs/clickablelabel.h \
    NetworkAzs/editnetworkazsdata.h \
    NetworkAzs/editnetworkazsdialog.h \
    NetworkAzs/editserverdialog.h \
    NetworkAzs/logodelegate.h \
    NetworkAzs/modelnetworkazs.h \
    NetworkAzs/modelsrvers.h \
    NetworkAzs/networkazsdialog.h \
    NetworkAzs/networkdata.h \
    Settings/criptpass.h \
    Settings/edituserdata.h \
    Settings/settingsdialog.h \
    Settings/userdata.h \
    Settings/userdatadialog.h \
    mainwindow.h

FORMS += \
    NetworkAzs/editnetworkazsdialog.ui \
    NetworkAzs/editserverdialog.ui \
    NetworkAzs/networkazsdialog.ui \
    Settings/settingsdialog.ui \
    Settings/userdatadialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    Spacer_RU_en.ts
TRANSLATIONS += \
    Spacer_RU_ua.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    Spacer_RU_en.qm \
    Spacer_RU_en.ts \
    Spacer_RU_ua.qm \
    Spacer_RU_ua.ts
