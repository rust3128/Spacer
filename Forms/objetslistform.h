#ifndef OBJETSLISTFORM_H
#define OBJETSLISTFORM_H
#include "Forms/objectmodel.h"
#include "ObjectWorkplace/objecttitle.h"
#include "ObjectWorkplace/objectdata.h"


#include <QWidget>

namespace Ui {
class ObjetsListForm;
}

class ObjetsListForm : public QWidget
{
    Q_OBJECT

public:
    explicit ObjetsListForm(int ID, QWidget *parent = nullptr);
    ~ObjetsListForm();
public slots:
    void slotUpdateObjList();
    void slotWorkplaceUpdate(int ID);
private slots:
    void on_tableViewObjects_doubleClicked(const QModelIndex &idx);

    void on_toolButtonAddObject_clicked();

private:
    void createUI();
    void createModel();
private:
    Ui::ObjetsListForm *ui;
    int netID;
    ObjectModel *modelObject;
    ObjectData *newObjData;
    ObjectTitle *newObjTitle;

};

#endif // OBJETSLISTFORM_H
