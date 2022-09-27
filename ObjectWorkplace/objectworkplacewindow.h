#ifndef OBJECTWORKPLACEWINDOW_H
#define OBJECTWORKPLACEWINDOW_H

#include "ObjectWorkplace/objectdata.h"
#include "ObjectWorkplace/objecttitle.h"

#include <QMainWindow>

namespace Ui {
class ObjectWorkplaceWindow;
}

class ObjectWorkplaceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ObjectWorkplaceWindow(int ID, QWidget *parent = nullptr);
    ~ObjectWorkplaceWindow();

private:
    void createUI();
private:
    Ui::ObjectWorkplaceWindow *ui;
    int objectID;
    ObjectData *objData;
    ObjectTitle *titleObj;
};

#endif // OBJECTWORKPLACEWINDOW_H
