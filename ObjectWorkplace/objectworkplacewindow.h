#ifndef OBJECTWORKPLACEWINDOW_H
#define OBJECTWORKPLACEWINDOW_H

#include "ObjectWorkplace/objectdata.h"
#include "ObjectWorkplace/objecttitle.h"
#include "ObjectWorkplace/workpalce.h"
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

private slots:
    void on_toolButtonClipboard_clicked();

    void on_toolButtonEditTitle_clicked();

private:
    void createUI();
    void showTitleObject();
    void showWorkpace();
private:
    Ui::ObjectWorkplaceWindow *ui;
    int objectID;
    ObjectData *objData;
    ObjectTitle *titleObj;
    QList<Workpalce> listWorkplace;
};

#endif // OBJECTWORKPLACEWINDOW_H
