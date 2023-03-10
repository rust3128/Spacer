#include "objetslistform.h"
#include "ui_objetslistform.h"
#include "LogginCategories/loggincategories.h"
#include "ObjectWorkplace/objectworkplacewindow.h"
#include "ObjectWorkplace/edittitleobjectdialog.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

ObjetsListForm::ObjetsListForm(int ID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjetsListForm),
    netID(ID)
{
    ui->setupUi(this);
    createModel();
    createUI();
}

ObjetsListForm::~ObjetsListForm()
{
    delete ui;
}

void ObjetsListForm::slotUpdateObjList()
{
    modelObject->setQuery(modelObject->query().lastQuery());
    ui->tableViewObjects->resizeColumnsToContents();
    ui->tableViewObjects->resizeRowsToContents();
}

void ObjetsListForm::createUI()
{
    ui->tableViewObjects->setModel(modelObject);
    QList<int> _hideColumn = {0,5,6};
    for(int i=0; i<_hideColumn.size();++i){
        ui->tableViewObjects->hideColumn(_hideColumn.at(i));
    }
    ui->tableViewObjects->verticalHeader()->hide();
    ui->tableViewObjects->resizeColumnsToContents();
    ui->tableViewObjects->horizontalHeader()->setStretchLastSection(true);
    ui->tableViewObjects->resizeRowsToContents();
    ui->splitter->setStretchFactor(0,2);
    ui->splitter->setStretchFactor(1,1);
}

void ObjetsListForm::createModel()
{
    modelObject = new ObjectModel(this);
    QString strSQL = QString("select o.object_id, o.terminal_id, o.adress, o.phone, o.comments, o.rank, o.isactive from objects o where o.network_id = %1"
                             "order by o.terminal_id").arg(netID);
    modelObject->setQuery(strSQL);

    QMap<int, QString> _headers;
    _headers.insert(1, tr("Терминал"));
    _headers.insert(2, tr("Адрес"));
    _headers.insert(3, tr("Телефон"));
    _headers.insert(4, tr("Комментарии"));
    QMapIterator<int, QString> _head(_headers);
    while(_head.hasNext()){
        _head.next();
        modelObject->setHeaderData(_head.key(),Qt::Horizontal,_head.value());
    }
}

void ObjetsListForm::on_tableViewObjects_doubleClicked(const QModelIndex &idx)
{
    int objID = modelObject->data(modelObject->index(idx.row(),0),Qt::DisplayRole).toInt();
    ObjectWorkplaceWindow *objWin = new ObjectWorkplaceWindow(objID,this);
    connect(objWin,&ObjectWorkplaceWindow::signalUpdateObjList,this,&ObjetsListForm::slotUpdateObjList);
    connect(objWin,&ObjectWorkplaceWindow::signalWorkplaceUpdate,this,&ObjetsListForm::slotWorkplaceUpdate);
    objWin->show();
}

void ObjetsListForm::slotWorkplaceUpdate(int ID)
{
    ObjectWorkplaceWindow *objWin = new ObjectWorkplaceWindow(ID,this);
    connect(objWin,&ObjectWorkplaceWindow::signalUpdateObjList,this,&ObjetsListForm::slotUpdateObjList);
    connect(objWin,&ObjectWorkplaceWindow::signalWorkplaceUpdate,this,&ObjetsListForm::slotWorkplaceUpdate);
    objWin->show();
}

void ObjetsListForm::on_toolButtonAddObject_clicked()
{
    bool ok;

    int newTermID = QInputDialog::getInt(this, tr("Добавление нового терминала"),
                                 tr("Terminal ID:"), 0, 0, 99999, 1, &ok);
    if (!ok){
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Добавление нового терминала"),
                          tr("Вы действительно хотите добвать терминал ")+QString::number(newTermID)+tr(" для этой сети АЗС?\nОперация не обратима."),
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::No){
        return;
    }
    QSqlQuery q;
    q.prepare("INSERT INTO OBJECTS (NETWORK_ID, TERMINAL_ID) VALUES (:netID, :termID)");
    q.bindValue(0,netID);
    q.bindValue(1,newTermID);
    if(!q.exec()){
        qCritical(logCritical()) << tr("Не удалось добавмть новый терминал ")+QString::number(newTermID) << q.lastError().text();
        return;
    }
    q.finish();
    q.prepare("select o.object_id from objects o where o.network_id = :netID and o.terminal_id = :termID");
    q.bindValue(0,netID);
    q.bindValue(1,newTermID);
    if(!q.exec()){
        qCritical(logCritical()) << tr("Не удалось получить данные о терминале ")+QString::number(newTermID) << q.lastError().text();
        return;
    }
    q.next();
    auto newObjID = q.value(0).toInt();
    newObjData = new ObjectData(newObjID);
    newObjTitle = new ObjectTitle(newObjID);
    newObjTitle = newObjData->getObjTitle();
    EditTitleObjectDialog *editNewObj =new  EditTitleObjectDialog(newObjTitle);
    connect(editNewObj,&EditTitleObjectDialog::signalUpdateObjData,this,&ObjetsListForm::slotUpdateObjList);
    editNewObj->exec();
}

