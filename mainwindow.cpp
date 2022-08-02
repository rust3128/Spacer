#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Settings/settingsdialog.h"
#include "NetworkAzs/networkazsdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
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

}

