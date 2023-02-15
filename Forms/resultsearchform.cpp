#include "resultsearchform.h"
#include "ui_resultsearchform.h"
#include "ObjectWorkplace/objectworkplacewindow.h"

ResultSearchForm::ResultSearchForm(int ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultSearchForm),
    terminalID(ID)
{
    ui->setupUi(this);
    createModels();
    createUI();
}

ResultSearchForm::~ResultSearchForm()
{
    delete ui;
}

void ResultSearchForm::createModels()
{
    modelObjects = new SearchObjectModel(this);
    QString strSQL = QString("select o.object_id, n.logo, n.name, o.terminal_id, o.adress, o.phone, o.comments, o.rank, o.isactive from objects o "
                             "left join networkazs n on n.network_id = o.network_id "
                             "where o.terminal_id = %1 "
                             "order by o.network_id").arg(terminalID);
    modelObjects->setQuery(strSQL);
}

void ResultSearchForm::createUI()
{
    auto strTitle = tr("Результаты поиска ")+QString::number(terminalID)+tr(".\nНайдено объектов: ")+QString::number(modelObjects->rowCount());
    ui->labelInfo->setText(strTitle);
    ui->tableViewObjects->setModel(modelObjects);

    logoDelegate = new LogoDelegate();
    ui->tableViewObjects->setItemDelegateForColumn(1,logoDelegate);

    ui->tableViewObjects->verticalHeader()->hide();
    QList<int> _resizeColumn = {2,3,4,5};
    for(int i=0; i<_resizeColumn.size();++i){
        ui->tableViewObjects->resizeColumnToContents(_resizeColumn.at(i));
    }
//    ui->tableViewObjects->resizeColumnsToContents();
    ui->tableViewObjects->horizontalHeader()->setStretchLastSection(true);
//    ui->tableViewObjects->resizeRowsToContents();
    ui->tableViewObjects->hideColumn(0);
    ui->tableViewObjects->hideColumn(7);
    ui->tableViewObjects->hideColumn(8);
}

void ResultSearchForm::on_tableViewObjects_doubleClicked(const QModelIndex &idx)
{
    int objID = modelObjects->data(modelObjects->index(idx.row(),0),Qt::DisplayRole).toInt();
    ObjectWorkplaceWindow *objWin = new ObjectWorkplaceWindow(objID,this);
    objWin->show();
}

