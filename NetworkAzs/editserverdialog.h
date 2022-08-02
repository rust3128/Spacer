#ifndef EDITSERVERDIALOG_H
#define EDITSERVERDIALOG_H

#include <QDialog>

namespace Ui {
class EditServerDialog;
}

class EditServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditServerDialog(int ID, QWidget *parent = nullptr);
    ~EditServerDialog();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    void createUI();
private:
    Ui::EditServerDialog *ui;
    int serverID;
};

#endif // EDITSERVERDIALOG_H
