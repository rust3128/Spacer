#include "objetslistform.h"
#include "ui_objetslistform.h"
#include "LogginCategories/loggincategories.h"
#include "ObjectWorkplace/objectworkplacewindow.h"

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
    objWin->show();
}

