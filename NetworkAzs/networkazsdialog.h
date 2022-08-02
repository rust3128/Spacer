#ifndef NETWORKAZSDIALOG_H
#define NETWORKAZSDIALOG_H

#include "modelnetworkazs.h"
#include "logodelegate.h"


#include <QDialog>

namespace Ui {
class NetworkAzsDialog;
}

class NetworkAzsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkAzsDialog(QWidget *parent = nullptr);
    ~NetworkAzsDialog();

private slots:
    void on_buttonBox_accepted();

    void on_tableViewNetworks_doubleClicked(const QModelIndex &idx);

    void on_buttonBox_rejected();

private:
    void createUI();
    void createModel();
private:
    Ui::NetworkAzsDialog *ui;
    ModelNetworkAzs *modelNetwork;
    LogoDelegate *logoDelegate;

};

#endif // NETWORKAZSDIALOG_H
