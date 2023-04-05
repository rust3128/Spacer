#ifndef OBJECTWORKPLACEWINDOW_H
#define OBJECTWORKPLACEWINDOW_H

#include "ObjectWorkplace/objectdata.h"
#include "ObjectWorkplace/objecttitle.h"
#include "ObjectWorkplace/tanksinfomodel.h"
#include "ObjectWorkplace/workpalce.h"
#include "NetworkAzs/centraldbconnect.h"
#include "ObjectWorkplace/tankproperty.h"

#include <QMainWindow>
#include <QSqlQueryModel>

namespace Ui {
class ObjectWorkplaceWindow;
}

class ObjectWorkplaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ObjectWorkplaceWindow(int ID, QWidget *parent = nullptr);
    ~ObjectWorkplaceWindow();
signals:
    void signalUpdateObjList();
    void signalWorkplaceUpdate(int);
public slots:
    void slotGetQueryTanks(QList<TankProperty> list);
private slots:
    void slotUpdateWorkplace();
    void slotStartGetTanksInfo();

    void slotFinishGetTanks();
    void on_toolButtonClipboard_clicked();
    void on_toolButtonEditTitle_clicked();
    void on_toolButtonAddWorkPlace_clicked();

private:
    void createUI();
    void showTitleObject();
    void showWorkpace();
    void openCentralDatabase();
    void tanksTabShow();

private:
    Ui::ObjectWorkplaceWindow *ui;
    int objectID;
    ObjectData *objData;
    ObjectTitle *titleObj;
    QList<Workpalce> listWorkplace;
    TanksInfoModel *modelTanks;
    CentralDBConnect *centerDB;
    QSqlDatabase dbCenter;
    QString dataBaseConName;
};

#endif // OBJECTWORKPLACEWINDOW_H
