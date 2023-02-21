#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Settings/settingsdialog.h"
#include "NetworkAzs/networkazsdialog.h"
#include "Forms/listnetworkform.h"
#include "LogginCategories/loggincategories.h"
#include "Forms/objetslistform.h"
#include "Forms/resultsearchform.h"
#include "Settings/userlistdialog.h"

#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(int id, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      userID(id)
{
    ui->setupUi(this);
    getUserStatus();
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

void MainWindow::slotGetSearchTermID(int termID)
{
    searchTermID = termID;
    qInfo(logInfo()) << "Search term ID = " << searchTermID;
    ResultSearchForm *searchRes = new ResultSearchForm(searchTermID);
    int tabIdx = ui->tabWidget->insertTab(1,searchRes,tr("Поиск"));
    tabList.append(0);
    ui->tabWidget->setCurrentIndex(tabIdx);
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
    ui->actionSettings->setEnabled(isAdmin);
    ui->actionNetworkAzs->setEnabled(isAdmin);
}

void MainWindow::createConnections()
{
    connect(ui->widgetListNetworks,&ListNetworkForm::signalSendNetID,this,&MainWindow::slotGetNetID);
    connect(ui->widgetSearch,&SearchForm::signalSendSearchTerminalID,this,&MainWindow::slotGetSearchTermID);
}

void MainWindow::getUserStatus()
{
    QSqlQuery q;
    q.prepare("select u.isadmin from users u  where u.user_id = :userID");
    q.bindValue(0, userID);
    if(!q.exec()){
        qCritical(logCritical()) << q.lastError().text();
        isAdmin = false;
        return;
    }
    q.next();
    isAdmin = q.value(0).toBool();
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


void MainWindow::on_actionUsers_triggered()
{
    UserListDialog *userList = new UserListDialog(userID, this);
    userList->exec();
}

