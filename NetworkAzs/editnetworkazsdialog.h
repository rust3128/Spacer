#ifndef EDITNETWORKAZSDIALOG_H
#define EDITNETWORKAZSDIALOG_H

#include "NetworkAzs/networkdata.h"
#include "NetworkAzs/editnetworkazsdata.h"
#include "modelsrvers.h"
#include "centraldbconnect.h"
#include <QDialog>


namespace Ui {
class EditNetworkAzsDialog;
}

class EditNetworkAzsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditNetworkAzsDialog(int ID, QWidget *parent = nullptr);
    ~EditNetworkAzsDialog();

private slots:
    void actionOpenDBTrigered();
    void slotLogoFileOpen();
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_pushButtonAddServer_clicked();

    void on_tableViewServers_doubleClicked(const QModelIndex &idx);



private:
    void createUI();
    void createModel();
    void updateCentralDB();
private:
    Ui::EditNetworkAzsDialog *ui;
    int networkID;
    NetworkData *netData;
    EditNetworkAzsData *editNetAzs;
    ModelSrvers *modelServers;
    CentralDBConnect *centralDB;
};

#endif // EDITNETWORKAZSDIALOG_H
