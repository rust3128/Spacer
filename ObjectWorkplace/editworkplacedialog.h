#ifndef EDITWORKPLACEDIALOG_H
#define EDITWORKPLACEDIALOG_H

#include "ObjectWorkplace/objecttitle.h"
#include "ObjectWorkplace/workpalce.h"

#include <QDialog>
#include <QSqlQueryModel>

namespace Ui {
class EditWorkplaceDialog;
}

class EditWorkplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditWorkplaceDialog(ObjectTitle *objT, Workpalce *w, QWidget *parent = nullptr);
    ~EditWorkplaceDialog();

private slots:
    void on_comboBoxArmType_activated(int idx);

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    void createUI();
    void createModel();
private:
    Ui::EditWorkplaceDialog *ui;
    ObjectTitle *objTitle;
    Workpalce *wk;
    QSqlQueryModel *modelVersion;
    int verType;
};

#endif // EDITWORKPLACEDIALOG_H
