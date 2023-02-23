#include "userlistdialog.h"
#include "qsqlquery.h"
#include "ui_userlistdialog.h"
#include "LogginCategories/loggincategories.h"
#include "Settings/userdatadialog.h"

#include <QMessageBox>

UserListDialog::UserListDialog(int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserListDialog),
    curUserID(id)
{
    ui->setupUi(this);
    createModel();
    getUserRole();
    createUI();
}

UserListDialog::~UserListDialog()
{
    delete ui;
}

void UserListDialog::createUI()
{
    ui->tableViewUsers->setModel(modelUsers);

    ui->tableViewUsers->hideColumn(0);
    ui->tableViewUsers->resizeColumnsToContents();
}

void UserListDialog::createModel()
{
    modelUsers = new ModeelUserList(this);
    modelUsers->setQuery("select u.user_id, u.username, u.fio, u.phone, u.phoneaster, u.email, u.ui_lang, u.isactive, u.isadmin from users u");

}

void UserListDialog::getUserRole()
{

    for (int i = 0; i < modelUsers->rowCount(); ++i) {
        QModelIndex index = modelUsers->index(i, 0); // первый столбец
        auto value = modelUsers->data(index,Qt::DisplayRole).toInt();

        if (value == curUserID) {
            isAdmin = (modelUsers->data(modelUsers->index(i,8),Qt::DisplayRole).toString() == "ADMIN") ? true : false;
            break;
        }
    }
}

void UserListDialog::on_buttonBox_rejected()
{
    this->reject();
}


void UserListDialog::on_tableViewUsers_doubleClicked(const QModelIndex &idx)
{
    auto editUserID = modelUsers->data(modelUsers->index(idx.row(),0),Qt::DisplayRole).toInt();
    if(editUserID == curUserID || isAdmin){
        UserDataDialog *editUserDlg = new UserDataDialog(editUserID,isAdmin,this);
        if(editUserDlg->exec() == QDialog::Accepted){
            modelUsers->setQuery(modelUsers->query().lastQuery());
            ui->tableViewUsers->resizeColumnsToContents();
        }

    } else {
        QMessageBox msgBox(QMessageBox::Warning, tr("Доступ запрещен"),
                                  tr("Вы можете редакитровать только свои данные."), { }, this);
        msgBox.setDetailedText("Для изменеия данных других пользователей необходимо получить права Администратора.");
        msgBox.exec();
    }
}

