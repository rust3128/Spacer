#ifndef OBJETSLISTFORM_H
#define OBJETSLISTFORM_H
#include "Forms/objectmodel.h"
#include "ObjectWorkplace/objecttitle.h"
#include "ObjectWorkplace/objectdata.h"
#include "NetworkAzs/centraldbconnect.h"
#include "Deploys/deploydata.h"
#include "Deploys/deploysmodel.h"


#include <QSortFilterProxyModel>
#include <QWidget>
#include <QTimer>

namespace Ui {
class ObjetsListForm;
}

class ObjetsListForm : public QWidget
{
    Q_OBJECT

public:
    explicit ObjetsListForm(int ID, QWidget *parent = nullptr);
    ~ObjetsListForm();
public slots:

    void slotUpdateObjList();
    void slotWorkplaceUpdate(int ID);

private slots:
    void deploysShow();
    void slotErrorGetDeploys(QString message);
    void slotStartGetDeploys();
    void slotGetDeploys(QVector<DeployData> dp);
    void slotFinishGetDeploys();
    void on_tableViewObjects_doubleClicked(const QModelIndex &idx);

    void on_toolButtonAddObject_clicked();

    void on_pushButtonRefreshDeploys_clicked();
    void on_spinBoxInterval_valueChanged(int interval);
    void slotPushButtonRdpClicked();
private:
    void createUI();
    void createModel();
    void showDeploysData(bool show);
    bool typeGetTypeConnect();
    void createButtonRDP();
private:
    Ui::ObjetsListForm *ui;
    int netID;
    int m_userID;
    ObjectModel *modelObject;
    ObjectData *newObjData;
    ObjectTitle *newObjTitle;
    CentralDBConnect *centerDB;
    QVector<DeployData> deploys;
    DeploysModel *depModel;
    QSortFilterProxyModel *proxyDep;
    QTimer *timer;
    bool typeConnect;                   //Тип подключения к АЗС 1-Термадм 0 -Сервер

};

#endif // OBJETSLISTFORM_H
