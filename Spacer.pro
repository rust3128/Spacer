QT       += core gui sql network core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
win32: RC_ICONS = $$PWD/Images/Spacer.ico

SOURCES += \
    Database/database.cpp \
    Forms/listnetworkform.cpp \
    Forms/modelnetworklist.cpp \
    Forms/objectmodel.cpp \
    Forms/objetslistform.cpp \
    Forms/resultsearchform.cpp \
    Forms/searchform.cpp \
    Forms/searchobjectmodel.cpp \
    Forms/workplceform.cpp \
    GlobalSettings/globalsettings.cpp \
    LogginCategories/loggincategories.cpp \
    NetworkAzs/centraldbconnect.cpp \
    NetworkAzs/clickablelabel.cpp \
    NetworkAzs/editnetworkazsdata.cpp \
    NetworkAzs/editnetworkazsdialog.cpp \
    NetworkAzs/editserverdialog.cpp \
    NetworkAzs/logodelegate.cpp \
    NetworkAzs/modelnetworkazs.cpp \
    NetworkAzs/modelsrvers.cpp \
    NetworkAzs/networkazsdialog.cpp \
    NetworkAzs/networkdata.cpp \
    ObjectWorkplace/connstatusvnc.cpp \
    ObjectWorkplace/edittitleobjectdialog.cpp \
    ObjectWorkplace/editworkplacedialog.cpp \
    ObjectWorkplace/objectdata.cpp \
    ObjectWorkplace/objecttitle.cpp \
    ObjectWorkplace/objectworkplacewindow.cpp \
    ObjectWorkplace/pingdialog.cpp \
    ObjectWorkplace/pingmodel.cpp \
    ObjectWorkplace/workpalce.cpp \
    Settings/criptpass.cpp \
    Settings/edituserdata.cpp \
    Settings/modeeluserlist.cpp \
    Settings/qaesencryption.cpp \
    Settings/settingsdialog.cpp \
    Settings/userdata.cpp \
    Settings/userdatadialog.cpp \
    Settings/userlistdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Database/database.h \
    Forms/listnetworkform.h \
    Forms/modelnetworklist.h \
    Forms/objectmodel.h \
    Forms/objetslistform.h \
    Forms/resultsearchform.h \
    Forms/searchform.h \
    Forms/searchobjectmodel.h \
    Forms/workplceform.h \
    GlobalSettings/globalsettings.h \
    LogginCategories/loggincategories.h \
    NetworkAzs/centraldbconnect.h \
    NetworkAzs/clickablelabel.h \
    NetworkAzs/editnetworkazsdata.h \
    NetworkAzs/editnetworkazsdialog.h \
    NetworkAzs/editserverdialog.h \
    NetworkAzs/logodelegate.h \
    NetworkAzs/modelnetworkazs.h \
    NetworkAzs/modelsrvers.h \
    NetworkAzs/networkazsdialog.h \
    NetworkAzs/networkdata.h \
    ObjectWorkplace/connstatusvnc.h \
    ObjectWorkplace/edittitleobjectdialog.h \
    ObjectWorkplace/editworkplacedialog.h \
    ObjectWorkplace/objectdata.h \
    ObjectWorkplace/objecttitle.h \
    ObjectWorkplace/objectworkplacewindow.h \
    ObjectWorkplace/pingdialog.h \
    ObjectWorkplace/pingmodel.h \
    ObjectWorkplace/workpalce.h \
    Settings/criptpass.h \
    Settings/edituserdata.h \
    Settings/modeeluserlist.h \
    Settings/qaesencryption.h \
    Settings/settingsdialog.h \
    Settings/userdata.h \
    Settings/userdatadialog.h \
    Settings/userlistdialog.h \
    mainwindow.h

FORMS += \
    Forms/listnetworkform.ui \
    Forms/objetslistform.ui \
    Forms/resultsearchform.ui \
    Forms/searchform.ui \
    Forms/workplceform.ui \
    NetworkAzs/editnetworkazsdialog.ui \
    NetworkAzs/editserverdialog.ui \
    NetworkAzs/networkazsdialog.ui \
    ObjectWorkplace/edittitleobjectdialog.ui \
    ObjectWorkplace/editworkplacedialog.ui \
    ObjectWorkplace/objectworkplacewindow.ui \
    ObjectWorkplace/pingdialog.ui \
    Settings/settingsdialog.ui \
    Settings/userdatadialog.ui \
    Settings/userlistdialog.ui \
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
