#ifndef EDITTITLEOBJECTDIALOG_H
#define EDITTITLEOBJECTDIALOG_H
#include "ObjectWorkplace/objecttitle.h"

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class EditTitleObjectDialog;
}

class EditTitleObjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTitleObjectDialog(ObjectTitle *obj, QWidget *parent = nullptr);
    ~EditTitleObjectDialog();

private slots:
    void on_plainTextEditComments_textChanged();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    void createUI();
private:
    Ui::EditTitleObjectDialog *ui;
    ObjectTitle *titleData;
    QButtonGroup *group;

};

#endif // EDITTITLEOBJECTDIALOG_H
