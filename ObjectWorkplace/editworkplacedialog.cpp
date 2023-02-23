#include "editworkplacedialog.h"
#include "ui_editworkplacedialog.h"
#include "LogginCategories/loggincategories.h"

#include <QSqlQuery>
#include <QSqlError>

EditWorkplaceDialog::EditWorkplaceDialog(ObjectTitle *objT, Workpalce *w, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditWorkplaceDialog),
    objTitle(objT),
    wk(w)
{
    ui->setupUi(this);
    createModel();
    createUI();
}

EditWorkplaceDialog::~EditWorkplaceDialog()
{
    delete ui;
}

void EditWorkplaceDialog::createUI()
{
    QString strTitle = tr("Терминал ")+QString::number(objTitle->getTerminalID())+"\n"+objTitle->getAddress();
    ui->label->setText(strTitle);
    ui->comboBoxArmType->setModel(modelVersion);
    ui->comboBoxArmType->setModelColumn(1);if(wk == nullptr){
        this->setWindowTitle(tr("Новое рабочее место"));
        ui->comboBoxArmType->setCurrentIndex(-1);
    } else {
        this->setWindowTitle(tr("Редактирование рабочего места"));
        ui->comboBoxArmType->setCurrentIndex(wk->getVerTypeID()-1);
        ui->labelTypeName->setText("MPos"+wk->getVerTypeName());
        ui->spinBoxPosID->setValue(wk->getPosID());
        ui->lineEditIP->setText(wk->getIPADR());
        ui->spinBoxVNCPort->setValue(wk->getPortVNC());
        ui->lineEditVNCPass->setText(wk->getPassVNC());
    }



}

void EditWorkplaceDialog::createModel()
{
    modelVersion = new QSqlQueryModel();
    modelVersion->setQuery("select v.version_type_id, v.version_name from version_type v");

}

void EditWorkplaceDialog::on_comboBoxArmType_activated(int idx)
{
    verType = modelVersion->data(modelVersion->index(idx,0)).toInt();
    ui->labelTypeName->setText("MPos"+ui->comboBoxArmType->itemText(idx));
}


void EditWorkplaceDialog::on_buttonBox_rejected()
{
    this->reject();
}


void EditWorkplaceDialog::on_buttonBox_accepted()
{
    QSqlQuery q;
    if(wk == nullptr){
        q.prepare("INSERT INTO WORKPLACES (NETWORK_ID, TERMINAL_ID, VERSION_TYPE_ID, POS_ID, IPADR, VNC_PORT, VNC_PASS) "
                  "VALUES (:net, :term, :type, :pos, :ip, :port, :pass);");
        q.bindValue(0,objTitle->getNetworkID());
        q.bindValue(1,objTitle->getTerminalID());
        q.bindValue(2,verType);
        q.bindValue(3,ui->spinBoxPosID->value());
        q.bindValue(4,ui->lineEditIP->text().trimmed());
        q.bindValue(5,ui->spinBoxVNCPort->value());
        q.bindValue(6,ui->lineEditVNCPass->text().trimmed());
        if(!q.exec()){
            qCritical(logCritical()) << tr("Не удалось добававить рабочее место. Терминал") << objTitle->getTerminalID() << q.lastError();
            return;
        }
    } else {
        q.prepare("UPDATE WORKPLACES SET VERSION_TYPE_ID = :verType, POS_ID = :posID, IPADR = :IP, VNC_PORT = :port, VNC_PASS = :pass "
                  "WHERE (WORKPLACE_ID = :wrID)");
        q.bindValue(0,verType);
        q.bindValue(1,ui->spinBoxPosID->value());
        q.bindValue(2,ui->lineEditIP->text().trimmed());
        q.bindValue(3,ui->spinBoxVNCPort->value());
        q.bindValue(4,ui->lineEditVNCPass->text().trimmed());
        q.bindValue(5,wk->getWorrplaceID());
        if(!q.exec()){
            qCritical(logCritical()) << tr("Не удалось обновить данніе о рабочем месте. Терминал") << objTitle->getTerminalID() << q.lastError();
            return;
        }
    }
    this->accept();
}

