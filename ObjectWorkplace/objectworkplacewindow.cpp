#include "objectworkplacewindow.h"
#include "ui_objectworkplacewindow.h"
#include "LogginCategories/loggincategories.h"

ObjectWorkplaceWindow::ObjectWorkplaceWindow(int ID, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ObjectWorkplaceWindow),
    objectID(ID)
{
    ui->setupUi(this);
    objData = new ObjectData(objectID);
    titleObj = objData->getObjTitle();
    createUI();
}

ObjectWorkplaceWindow::~ObjectWorkplaceWindow()
{
    delete ui;
}

void ObjectWorkplaceWindow::createUI()
{
    QString winTitle = titleObj->getNetworkName() + " "
            + QString::number(titleObj->getTerminalID());
    this->setWindowTitle(winTitle);
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData(titleObj->getLogo());
    auto w = ui->labelLogo->width();
    auto h = ui->labelLogo->height();
    outPixmap = outPixmap.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//    ui->labelLogo->setPixmap(inPixmap);
    if(!outPixmap.isNull())
        ui->labelLogo->setPixmap(outPixmap);
}
