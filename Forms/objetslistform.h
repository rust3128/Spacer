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
    void slotStartGetDeploys();
    void slotGetDeploys(QVector<DeployData> dp);
    void slotFinishGetDeploys();
    void on_tableViewObjects_doubleClicked(const QModelIndex &idx);

    void on_toolButtonAddObject_clicked();

    void on_pushButtonRefreshDeploys_clicked();

private:
    void createUI();
    void createModel();
    void deploysShow();
    void showDeploysData(bool show);
private:
    Ui::ObjetsListForm *ui;
    int netID;
    ObjectModel *modelObject;
    ObjectData *newObjData;
    ObjectTitle *newObjTitle;
    CentralDBConnect *centerDB;
    QVector<DeployData> deploys;
    DeploysModel *depModel;
    QSortFilterProxyModel *proxyDep;

};

#endif // OBJETSLISTFORM_H
