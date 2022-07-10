QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GlobalSettings/globalsettings.cpp \
    LogginCategories/loggincategories.cpp \
    Settings/settingsdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    GlobalSettings/globalsettings.h \
    LogginCategories/loggincategories.h \
    Settings/settingsdialog.h \
    mainwindow.h

FORMS += \
    Settings/settingsdialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    Spacer_uk_UA.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
