#include "userdatadialog.h"
#include "ui_userdatadialog.h"

UserDataDialog::UserDataDialog(uint ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserDataDialog),
    userID(ID)
{
    ui->setupUi(this);
    editUserData = new EditUserData(userID);
    userData = editUserData->getUserData();
    createUI();
}

UserDataDialog::~UserDataDialog()
{
    delete ui;
}

void UserDataDialog::createUI()
{
    ui->lineEditLogin->setText(userData->getUserName());
    ui->lineEditFIO->setText(userData->getFullName());
    ui->lineEditPhone->setText(userData->getPhone());
    ui->lineEditAsterPhone->setText(userData->getPhone());
    ui->lineEditEMail->setText(userData->getEmail());
    switch (userData->getUiLang()) {
    case 1:
        ui->radioButtonUA->setChecked(true);
        break;
    case 2:
        ui->radioButtonEN->setChecked(true);
        break;
    case 3:
        ui->radioButtonRU->setChecked(true);
        break;
    default:
        break;
    }
}

void UserDataDialog::on_buttonBox_accepted()
{
    userData->setFullName(ui->lineEditFIO->text().trimmed());
    userData->setPhone(ui->lineEditPhone->text().trimmed());
    userData->setPhoneAster(ui->lineEditAsterPhone->text().trimmed());
    userData->setEmail(ui->lineEditEMail->text().trimmed());
    uint langUI;
    if(ui->radioButtonUA->isChecked()) langUI = 1;
    if(ui->radioButtonEN->isChecked()) langUI = 2;
    if(ui->radioButtonRU->isChecked()) langUI = 3;
    userData->setUiLang(langUI);
    editUserData->setUserData(userData);

    this->accept();
}


void UserDataDialog::on_buttonBox_rejected()
{
    this->reject();
}

