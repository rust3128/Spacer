#ifndef OBJETSLISTFORM_H
#define OBJETSLISTFORM_H
#include "Forms/objectmodel.h"

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

private:
    void createUI();
    void createModel();
private:
    Ui::ObjetsListForm *ui;
    int netID;
    ObjectModel *modelObject;

};

#endif // OBJETSLISTFORM_H
