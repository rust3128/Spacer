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
    ui->labelVerType->setText("MPos"+curWorplace.getVerTypeName());
    ui->labelIP->setText(curWorplace.getIPADR());
}
