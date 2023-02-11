#include "workplceform.h"
#include "ui_workplceform.h"
#include "LogginCategories/loggincategories.h"

WorkplceForm::WorkplceForm(Workpalce wk, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkplceForm),
    curWorplace(wk)
{
    ui->setupUi(this);
    createUI();
}

WorkplceForm::~WorkplceForm()
{
    delete ui;
}

void WorkplceForm::createUI()
{
    QString verType = "MPos"+curWorplace.getVerTypeName();
    if(curWorplace.getVerTypeID() == 4){
        verType += " PosID = " + QString::number(curWorplace.getPosID());
    }
    ui->labelVerType->setText(verType);
    ui->labelIP->setText(curWorplace.getIPADR());
}
