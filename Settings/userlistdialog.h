#ifndef USERLISTDIALOG_H
#define USERLISTDIALOG_H

#include "Settings/modeeluserlist.h"

#include <QDialog>

namespace Ui {
class UserListDialog;
}

class UserListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserListDialog(int id, QWidget *parent = nullptr);
    ~UserListDialog();
private slots:
    void on_buttonBox_rejected();

    void on_tableViewUsers_doubleClicked(const QModelIndex &idx);

private:
    void createUI();
    void createModel();
    void getUserRole();
private:
    Ui::UserListDialog *ui;
    int curUserID;
    bool isAdmin;
    ModeelUserList *modelUsers;
};

#endif // USERLISTDIALOG_H
