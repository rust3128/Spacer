#include "listnetworkform.h"
#include "ui_listnetworkform.h"
#include "LogginCategories/loggincategories.h"


#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


ListNetworkForm::ListNetworkForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListNetworkForm)
{
    ui->setupUi(this);
    createModel();
    createUI();
}

ListNetworkForm::~ListNetworkForm()
{
    delete ui;
}

void ListNetworkForm::createUI()
{
    ui->listViewNetwork->setModel(modelNetwork);


}

void ListNetworkForm::createModel()
{
    modelNetwork = new ModelNetworkList(this);
    modelNetwork->setQuery("select n.network_id, n.name, n.logo from networkazs n");
}

void ListNetworkForm::on_listViewNetwork_doubleClicked(const QModelIndex &idx)
{
    emit signalSendNetID(modelNetwork->record(idx.row()).value(0).toInt(),modelNetwork->record(idx.row()).value(1).toString());
}

