#include "networkazsdialog.h"
#include "LogginCategories/loggincategories.h"
#include "ui_networkazsdialog.h"
#include "NetworkAzs/editnetworkazsdialog.h"

#include <QPushButton>
#include <QInputDialog>
#include <QSqlQuery>
#include <QSqlError>

NetworkAzsDialog::NetworkAzsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkAzsDialog)
{
    ui->setupUi(this);
    createModel();
    createUI();
}

NetworkAzsDialog::~NetworkAzsDialog()
{
    delete ui;
}

void NetworkAzsDialog::createUI()
{
    ui->buttonBox->button(QDialogButtonBox::Yes)->setText(tr("Добавить"));
    ui->buttonBox->button(QDialogButtonBox::Yes)->setIcon(QIcon(":/Images/add_plus_icon.png"));

    logoDelegate = new LogoDelegate();
    ui->tableViewNetworks->setModel(modelNetwork);
    ui->tableViewNetworks->setItemDelegateForColumn(2,logoDelegate);
//    ui->tableViewNetworks->verticalHeader()->hide();
    ui->tableViewNetworks->hideColumn(0);
    QHeaderView *headerView = ui->tableViewNetworks->horizontalHeader();
    headerView->swapSections(2, 1);
    ui->tableViewNetworks->resizeColumnToContents(1);
//    ui->tableViewNetworks->resizeColumnToContents(2);
    ui->tableViewNetworks->resizeColumnToContents(3);
    ui->tableViewNetworks->resizeColumnToContents(4);

}

void NetworkAzsDialog::createModel()
{
    modelNetwork = new ModelNetworkAzs(this);

    modelNetwork->setQuery("select n.network_id, n.name, n.logo, n.typeconnect, n.isactive from networkazs n order by n.network_id");
    modelNetwork->setHeaderData(2,Qt::Horizontal,tr("Лого"));
    modelNetwork->setHeaderData(1,Qt::Horizontal,tr("Наименование"));
    modelNetwork->setHeaderData(3,Qt::Horizontal,tr("Подключение\nк АЗС"));
    modelNetwork->setHeaderData(4,Qt::Horizontal,tr("В работе"));
}

void NetworkAzsDialog::on_buttonBox_accepted()
{
    //Новая сеть АЗС

    bool ok;
    QString networkNew = QInputDialog::getText(this, tr("Новая сеть АЗС"), tr("Укажите наименование новой сети АЗС:"),
                                               QLineEdit::Normal,"",&ok);

    if (ok && networkNew.size() >= 3) {
        QSqlQuery q;
        QString strSQL = QString("EXECUTE PROCEDURE add_networkazs('%1')")
                .arg(networkNew.trimmed());
        if(!q.exec(strSQL)){
            qCritical(logCritical()) << tr("Не удалось создать новую сеть АЗС") << q.lastError().text();
            return;
        }
        q.next();
        int _newNetworkID = q.value(0).toInt();
        q.exec("commit work");
        q.finish();
        EditNetworkAzsDialog *editNetDlg = new EditNetworkAzsDialog(_newNetworkID);
        if(editNetDlg->exec() == QDialog::Accepted)
            modelNetwork->setQuery(modelNetwork->query().lastQuery());
    }

}


void NetworkAzsDialog::on_tableViewNetworks_doubleClicked(const QModelIndex &idx)
{
    EditNetworkAzsDialog *editNetDlg = new EditNetworkAzsDialog(modelNetwork->data(modelNetwork->index(idx.row(),0),Qt::DisplayRole).toInt());
    if(editNetDlg->exec() == QDialog::Accepted)
        modelNetwork->setQuery(modelNetwork->query().lastQuery());
}


void NetworkAzsDialog::on_buttonBox_rejected()
{
    this->reject();
}

