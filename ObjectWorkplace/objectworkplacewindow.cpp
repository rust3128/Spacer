#include "objectworkplacewindow.h"
#include "ui_objectworkplacewindow.h"
#include "LogginCategories/loggincategories.h"
#include "ObjectWorkplace/edittitleobjectdialog.h"
#include "Forms/workplceform.h"
#include "ObjectWorkplace/editworkplacedialog.h"


#include <QClipboard>
#include <QListWidgetItem>

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
    ui->labelLogo->resize(64,64);
    auto w = ui->labelLogo->width();
    auto h = ui->labelLogo->height();
    outPixmap = outPixmap.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if(!outPixmap.isNull())
        ui->labelLogo->setPixmap(outPixmap);
    ui->labelNenworkName->setText(titleObj->getNetworkName());
    ui->labelAZSNumber->setText(tr("АЗС № ")+QString::number(titleObj->getTerminalID()));
    showTitleObject();
    showWorkpace();
}

void ObjectWorkplaceWindow::showTitleObject()
{

    ui->labelAddress->setText(titleObj->getAddress());
    ui->labelPhone->setText(titleObj->getPhone());
    if(titleObj->getIsActive()){
        switch (titleObj->getRank()) {
        case 1:
            ui->labelCategory->setText(tr("1-я категория"));
            this->setStyleSheet("QMainWindow { background-color: lightgreen; }");
            break;
        case 2:
            ui->labelCategory->setText(tr("2-я категория"));
            this->setStyleSheet("QMainWindow { background-color: lightgoldenrodyellow; }");
            break;
        case 3:
            ui->labelCategory->setText(tr("3-я категория"));
            this->setStyleSheet("QMainWindow { background-color: azure; }");
            break;
        default:
            break;
        }
    } else {
        ui->labelCategory->setText(tr("Не работает"));
        this->setStyleSheet("QMainWindow { background-color: tomato; }");
    }
}

void ObjectWorkplaceWindow::showWorkpace()
{
    listWorkplace = objData->getListWorkplace();
    int sizeWorkplace = listWorkplace.size();
    for(int i = 0; i<sizeWorkplace; ++i){
        auto item = new QListWidgetItem();
        auto wk = new WorkplceForm(listWorkplace.at(i),this);
        item->setSizeHint(wk->sizeHint());
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item,wk);
    }

}

void ObjectWorkplaceWindow::on_toolButtonClipboard_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString clipTitle = ui->labelAZSNumber->text()+"\n"+ui->labelAddress->text()+"\n"+ui->labelPhone->text();
    clipboard->setText(clipTitle);
    ui->statusbar->showMessage(tr("Адрес АЗС скопирован в буфер обмена."),2000);
}


void ObjectWorkplaceWindow::on_toolButtonEditTitle_clicked()
{
    EditTitleObjectDialog *edTitleDlg = new EditTitleObjectDialog(titleObj);
    if(edTitleDlg->exec() == QDialog::Accepted){
        titleObj->getTitleData();
        titleObj = objData->getObjTitle();
        showTitleObject();
        emit signalUpdateObjList();
    }
}


void ObjectWorkplaceWindow::on_toolButtonAddWorkPlace_clicked()
{
    EditWorkplaceDialog *editWork = new EditWorkplaceDialog(titleObj, nullptr, this);
        if(editWork->exec() == QDialog::Accepted) {
            emit signalWorkplaceUpdate(objectID);
            this->close();
        }
}

