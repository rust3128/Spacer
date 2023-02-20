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
    if(wk == nullptr){
        this->setWindowTitle(tr("Новое рабочее место"));
    } else {
        this->setWindowTitle(tr("Редактирование рабочего места"));
    }
    QString strTitle = tr("Терминал ")+QString::number(objTitle->getTerminalID())+"\n"+objTitle->getAddress();
    ui->label->setText(strTitle);
    ui->comboBoxArmType->setModel(modelVersion);
    ui->comboBoxArmType->setModelColumn(1);
    ui->comboBoxArmType->setCurrentIndex(-1);
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

    this->accept();
}

