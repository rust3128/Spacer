#ifndef USERDATADIALOG_H
#define USERDATADIALOG_H

#include "edituserdata.h"
#include "userdata.h"

#include <QDialog>

namespace Ui {
class UserDataDialog;
}

class UserDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserDataDialog(uint ID, bool isAdmin, QWidget *parent = nullptr);
    ~UserDataDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    void createUI();
private:
    Ui::UserDataDialog *ui;
    uint userID;
    EditUserData *editUserData;
    UserData *userData;
    bool isAdmin;
};

#endif // USERDATADIALOG_H
