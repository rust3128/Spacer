#ifndef OBJECTWORKPLACEWINDOW_H
#define OBJECTWORKPLACEWINDOW_H

#include "ObjectWorkplace/dispenserproperty.h"
#include "ObjectWorkplace/objectdata.h"
#include "ObjectWorkplace/objecttitle.h"
#include "ObjectWorkplace/punpproperty.h"
#include "ObjectWorkplace/tanksinfomodel.h"
#include "ObjectWorkplace/workpalce.h"
#include "NetworkAzs/centraldbconnect.h"
#include "ObjectWorkplace/tankproperty.h"
#include "qtreewidget.h"

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
    void slotGetQueryDisp(QList<DispenserProperty> disp, QList<PunpProperty> pump);
private slots:
    void slotUpdateWorkplace();
    void slotStartGetTanksInfo();
    void slotFinishGetTanks();
    void slotStartGetDispInfo();
    void slotFinishGetDispInfo();
    void on_toolButtonClipboard_clicked();
    void on_toolButtonEditTitle_clicked();
    void on_toolButtonAddWorkPlace_clicked();

    void on_treeWidgetTRK_itemExpanded(QTreeWidgetItem *item);

private:
    void createUI();
    void showTitleObject();
    void showWorkpace();
    void openCentralDatabase();
    void tanksTabShow();
    void trkTabShow();

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
    bool availCenterDB;
};

#endif // OBJECTWORKPLACEWINDOW_H
