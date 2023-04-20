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
    q.prepare("select s.hostname, s.port, s.server_type, s.isactive from servers s where s.server_id =:id");
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
    ui->checkBox->setChecked(q.value(3).toBool());

    QSqlQuery query("SELECT TYPE_ID, DESCRIPTION FROM SERVER_TYPE");
    QGridLayout* layout = new QGridLayout(ui->groupBoxType);
    int row = 0;
    int column = 0;
    while (query.next())
    {
        int typeId = query.value(0).toInt();
        QString typeName = query.value(1).toString();

        QCheckBox* checkBox = new QCheckBox(typeName);
        checkBox->setProperty("typeId", typeId);

        layout->addWidget(checkBox, row, column);

        column++;
        if (column == 2)
        {
            column = 0;
            row++;
        }
    }
    ui->groupBoxType->setLayout(layout);

    QString strType = q.value(2).toString();
    QStringList typeList = strType.split(",");
    foreach (QString typeId, typeList)
    {
        for (int i = 0; i < ui->groupBoxType->layout()->count(); i++)
        {
            QCheckBox* checkBox = qobject_cast<QCheckBox*>(ui->groupBoxType->layout()->itemAt(i)->widget());
            if (checkBox && checkBox->property("typeId").toInt() == typeId.toInt())
            {
                checkBox->setChecked(true);
                break;
            }
        }
    }

}

void EditServerDialog::on_buttonBox_rejected()
{
    this->reject();
}


void EditServerDialog::on_buttonBox_accepted()
{
    QString strType;
    for (int i = 0; i < ui->groupBoxType->layout()->count(); i++)
    {
        QCheckBox* checkBox = qobject_cast<QCheckBox*>(ui->groupBoxType->layout()->itemAt(i)->widget());
        if (checkBox)
        {
            if (checkBox->isChecked())
            {
                if (!strType.isEmpty())
                    strType += ",";
                strType += QString::number(checkBox->property("typeId").toInt());
            }
        }
    }

    QSqlQuery q;
    q.prepare("UPDATE SERVERS SET HOSTNAME = :host, PORT = :port, SERVER_TYPE = :sType, ISACTIVE = :isActive WHERE (SERVER_ID = :ID)");
    q.bindValue(0,ui->lineEditHost->text().trimmed());
    q.bindValue(1,ui->lineEditPort->text().trimmed());
    q.bindValue(2, strType);
    q.bindValue(3,QVariant(ui->checkBox->isChecked()).toInt());
    q.bindValue(4,serverID);
    if(!q.exec()){
        qCritical(logCritical()) << tr("Не удалось обновить данные о сервере.") << q.lastError().text();
        return;
    }
    this->accept();
}

