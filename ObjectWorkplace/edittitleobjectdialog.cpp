#include "edittitleobjectdialog.h"
#include "ui_edittitleobjectdialog.h"
#include "LogginCategories/loggincategories.h"

#include <QSqlQuery>
#include <QSqlError>



EditTitleObjectDialog::EditTitleObjectDialog(ObjectTitle *obj, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTitleObjectDialog),
    titleData(obj)
{
    ui->setupUi(this);
    createUI();
}

EditTitleObjectDialog::~EditTitleObjectDialog()
{
    delete ui;
}

void EditTitleObjectDialog::createUI()
{
    this->setWindowTitle(titleData->getNetworkName()+tr(", АЗС ")+QString::number(titleData->getTerminalID()));
    group = new QButtonGroup(this);
    group->addButton(ui->radioButton_1,1);
    group->addButton(ui->radioButton_2,2);
    group->addButton(ui->radioButton_3,3);

    ui->labelNetwork->setText(titleData->getNetworkName());
    ui->labelAZS->setText(tr("АЗС ")+QString::number(titleData->getTerminalID()));
    ui->lineEditAdres->setText(titleData->getAddress());
    ui->lineEditPhone->setText(titleData->getPhone());
    ui->plainTextEditComments->setPlainText(titleData->getComments());
    ui->checkBoxIIsActive->setChecked(titleData->getIsActive());
    switch (titleData->getRank()) {
    case 1:
        ui->radioButton_1->setChecked(true);
        break;
    case 2:
        ui->radioButton_2->setChecked(true);
        break;
    case 3:
        ui->radioButton_3->setChecked(true);
        break;
    default:
        break;
    }
}

void EditTitleObjectDialog::on_plainTextEditComments_textChanged()
{
    QString strComments = ui->plainTextEditComments->toPlainText().trimmed();
    if(strComments.length() > 200)
    {
        ui->plainTextEditComments->setPlainText(strComments.first(200));
    }
}


void EditTitleObjectDialog::on_buttonBox_rejected()
{
    this->reject();
}


void EditTitleObjectDialog::on_buttonBox_accepted()
{
   QSqlQuery q;
   q.prepare("UPDATE OBJECTS SET ADRESS = ?, PHONE = ?, RANK = ?, ISACTIVE = ?, COMMENTS = ?  WHERE (OBJECT_ID = ?)");
   q.bindValue(0,ui->lineEditAdres->text().trimmed());
   q.bindValue(1,ui->lineEditPhone->text().trimmed());
   q.bindValue(2,group->checkedId());
   q.bindValue(3,QVariant(ui->checkBoxIIsActive->isChecked()).toInt());
   q.bindValue(4,ui->plainTextEditComments->toPlainText().trimmed());
   q.bindValue(5,titleData->getObjectID());
   if(!q.exec()){
       qCritical(logCritical()) << tr("Не удалось обновить данные об объекте.") << q.lastError().text();
   }
   this->accept();
   emit signalUpdateObjData();
}

