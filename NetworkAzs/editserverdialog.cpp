#include "editserverdialog.h"
#include "ui_editserverdialog.h"
#include "LogginCategories/loggincategories.h"

#include <QSqlQuery>
#include <QSqlError>

EditServerDialog::EditServerDialog(int ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditServerDialog),
    serverID(ID)
{
    ui->setupUi(this);
    createUI();
}

EditServerDialog::~EditServerDialog()
{
    delete ui;
}

void EditServerDialog::createUI()
{
    QSqlQuery q;
    q.prepare("select s.hostname, s.port, s.comments, s.isactive from servers s where s.server_id =:id");
    q.bindValue(0, serverID);
    if(!q.exec()){
        qCritical(logCritical()) << tr("Не удалось полчить данные о сервере.") << q.lastError().text();
        return;
    }
    q.next();
    ui->lineEditHost->setText(q.value(0).toString());
    if(q.value(1).toInt() != 0){
        ui->lineEditPort->setText(q.value(1).toString());
    }
    ui->lineEditComments->setText(q.value(2).toString());
    ui->checkBox->setChecked(q.value(3).toBool());

}

void EditServerDialog::on_buttonBox_rejected()
{
    this->reject();
}


void EditServerDialog::on_buttonBox_accepted()
{
    QSqlQuery q;
    q.prepare("UPDATE SERVERS SET HOSTNAME = :host, PORT = :port, COMMENTS = :comm, ISACTIVE = :isActive WHERE (SERVER_ID = :ID)");
    q.bindValue(0,ui->lineEditHost->text().trimmed());
    q.bindValue(1,ui->lineEditPort->text().trimmed());
    q.bindValue(2,ui->lineEditComments->text().trimmed());
    q.bindValue(3,QVariant(ui->checkBox->isChecked()).toInt());
    q.bindValue(4,serverID);
    if(!q.exec()){
        qCritical(logCritical()) << tr("Не удалось обновить данные о сервере.") << q.lastError().text();
        return;
    }
    this->accept();
}

