#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Settings/settingsdialog.h"
#include "NetworkAzs/networkazsdialog.h"
#include "Forms/listnetworkform.h"
#include "LogginCategories/loggincategories.h"
#include "Forms/objetslistform.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createUI();
    createConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotGetNetID(int netID, QString netName)
{

    int currTab =0;
    for(qsizetype i =0; i<tabList.size();++i){
        if(tabList.at(i) == netID){
            currTab = i;
        }
    }
    if(currTab > 0) {
        ui->tabWidget->setCurrentIndex(currTab);
    } else {
        ObjetsListForm *objList =  new ObjetsListForm(netID,this);
        int tabIdx = ui->tabWidget->addTab(objList,netName);
        tabList.append(netID);
        ui->tabWidget->setCurrentIndex(tabIdx);
    }

//    int idxIns = ui->tabWidget->insertTab(netID,tabWidget,QString::number(netID));
//    ui->tabWidget->setCurrentIndex(idxIns);
//    qInfo(logInfo()) << "TabIndx" << idxIns << "Net ID" << netID;

}


void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog *settDlg = new SettingsDialog(false);
    settDlg->exec();
}


void MainWindow::on_actionNetworkAzs_triggered()
{
    NetworkAzsDialog *netAzs = new NetworkAzsDialog();
    netAzs->exec();

}

void MainWindow::createUI()
{
    ui->widgetSearch->resize(QSize(258,114));
    tabList.append(0);
    ui->toolButtonGoHome->hide();

}

void MainWindow::createConnections()
{
    connect(ui->widgetListNetworks,&ListNetworkForm::signalSendNetID,this,&MainWindow::slotGetNetID);
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 0){
        ui->toolButtonGoHome->hide();
    } else {
        ui->toolButtonGoHome->show();
    }

}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
//    ui->tabWidget->removeTab(index);
    if(index !=0){
        ui->tabWidget->setCurrentIndex(index);
        ui->tabWidget->currentWidget()->deleteLater();
        tabList.removeAt(index);
    }
}


void MainWindow::on_toolButtonGoHome_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

