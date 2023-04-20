#include "objectworkplacewindow.h"
#include "ui_objectworkplacewindow.h"
#include "LogginCategories/loggincategories.h"
#include "ObjectWorkplace/edittitleobjectdialog.h"
#include "Forms/workplceform.h"
#include "ObjectWorkplace/editworkplacedialog.h"
#include "ObjectWorkplace/tanksinfo.h"
#include "ObjectWorkplace/dispenserinfo.h"


#include <QClipboard>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QSqlError>
#include <QThread>

ObjectWorkplaceWindow::ObjectWorkplaceWindow(int ID, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ObjectWorkplaceWindow),
    objectID(ID)
{
    ui->setupUi(this);
    objData = new ObjectData(objectID);
    titleObj = objData->getObjTitle();
    centerDB = new CentralDBConnect(titleObj->getNetworkID());
    centerDB->readFromDB();
    openCentralDatabase();
    createUI();
}

ObjectWorkplaceWindow::~ObjectWorkplaceWindow()
{
    delete ui;
}

void ObjectWorkplaceWindow::openCentralDatabase()
{
    dataBaseConName = "network"+QString::number(titleObj->getNetworkID());

    dbCenter = QSqlDatabase::database(dataBaseConName);
    if(!dbCenter.isValid()){

        dbCenter = QSqlDatabase::addDatabase("QIBASE",dataBaseConName);
        dbCenter.setHostName(centerDB->getServer());
        dbCenter.setPort(centerDB->getPort());
        dbCenter.setDatabaseName(centerDB->getFileDB());
        dbCenter.setUserName(centerDB->getUser());
        dbCenter.setPassword(centerDB->getPass());
        availCenterDB =true;

        if(!dbCenter.open()) {
            qCritical(logCritical()) << "Не могу подключится к центральной базе" << Qt::endl << dbCenter.lastError().text();
            availCenterDB =false;
            QMessageBox msgBox;
            msgBox.setWindowTitle(tr("Ошибка подключения."));
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText(tr("Произошла ошибка при подключении к центральной базе данных!\nИнформацию о конфигурации АЗС получить невозможно"));
            msgBox.setInformativeText(tr("Текст ошибки:\n")+dbCenter.lastError().text());
            QString strDetali = QString("Server:\t"+centerDB->getServer()+":"+QString::number(centerDB->getPort())+
                                        "\nDatabase:\t"+centerDB->getFileDB()+
                                        "\nUser:\t"+centerDB->getUser());
            msgBox.setDetailedText(strDetali);
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
        }
    }
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
    if(availCenterDB){
        tanksTabShow();
        trkTabShow();
        ui->labelTankNotFound->hide();
        ui->labelTRKNotFound->hide();
    } else {
        ui->labelTankNotFound->show();
        ui->tableViewTanks->hide();
        ui->labelWaitingTanks->hide();
        ui->labelTRKNotFound->show();
        ui->labelWaitingDisp->hide();
        ui->treeWidgetTRK->hide();
    }

}



void ObjectWorkplaceWindow::tanksTabShow()
{
    TanksInfo *tanksInfo = new TanksInfo(titleObj->getTerminalID(), dbCenter);

    QThread *thread = new QThread();

    tanksInfo->moveToThread(thread);

    connect(thread,&QThread::started,this,&ObjectWorkplaceWindow::slotStartGetTanksInfo);
    connect(thread,&QThread::started,tanksInfo,&TanksInfo::createTanksQuery);

    connect(tanksInfo,&TanksInfo::queryFinished,this,&ObjectWorkplaceWindow::slotGetQueryTanks);
    connect(tanksInfo,&TanksInfo::finished,thread,&QThread::quit);
    connect(tanksInfo,&TanksInfo::finished,tanksInfo,&TanksInfo::deleteLater);
    connect(tanksInfo,&TanksInfo::finished,this,&ObjectWorkplaceWindow::slotFinishGetTanks);
    connect(thread,&QThread::finished,thread,&QThread::deleteLater);
    thread->start();

}

void ObjectWorkplaceWindow::trkTabShow()
{
    DispenserInfo *dispInfo = new DispenserInfo(titleObj->getTerminalID(), dbCenter);
    QThread *thread = new QThread();
    dispInfo->moveToThread(thread);

    connect(thread,&QThread::started,this,&ObjectWorkplaceWindow::slotStartGetTanksInfo);
    connect(thread,&QThread::started,dispInfo,&DispenserInfo::slotCreateDyspInfo);
    connect(dispInfo,&DispenserInfo::queryFinished,this,&ObjectWorkplaceWindow::slotGetQueryDisp);
    connect(dispInfo,&DispenserInfo::finished,thread,&QThread::quit);
    connect(dispInfo,&DispenserInfo::finished,dispInfo,&DispenserInfo::deleteLater);
    connect(dispInfo,&DispenserInfo::finished,this,&ObjectWorkplaceWindow::slotFinishGetDispInfo);
    connect(thread,&QThread::finished,thread,&QThread::deleteLater);
    thread->start();
}



void ObjectWorkplaceWindow::slotStartGetTanksInfo()
{
       ui->tabWidget->setTabIcon(1,QIcon(":/Images/waiting_icon.png"));
       ui->tableViewTanks->hide();
       ui->labelWaitingTanks->show();
}

void ObjectWorkplaceWindow::slotGetQueryTanks(QList<TankProperty> list)
{
    modelTanks = new TanksInfoModel(list);
    ui->tableViewTanks->setModel(modelTanks);
    ui->tableViewTanks->resizeColumnsToContents();
}


void ObjectWorkplaceWindow::slotFinishGetTanks()
{
    ui->tabWidget->setTabIcon(1,QIcon());
    ui->tableViewTanks->show();
    ui->labelWaitingTanks->hide();
}

void ObjectWorkplaceWindow::slotStartGetDispInfo()
{
    ui->tabWidget->setTabIcon(2,QIcon(":/Images/waiting_icon.png"));
    ui->treeWidgetTRK->hide();
    ui->labelWaitingDisp->show();
}

void ObjectWorkplaceWindow::slotFinishGetDispInfo()
{
    ui->tabWidget->setTabIcon(2,QIcon());
    ui->treeWidgetTRK->show();
    ui->labelWaitingDisp->hide();
}

void ObjectWorkplaceWindow::slotGetQueryDisp(QList<DispenserProperty> disp, QList<PunpProperty> pump)
{
    // Очищаем QTreeWidget перед добавлением новых элементов
    ui->treeWidgetTRK->clear();


    // Определяем количество столбцов
    int columnCount = 5;
    ui->treeWidgetTRK->setColumnCount(columnCount);


    // Устанавливаем заголовки столбцов
    QStringList headerLabels;
    headerLabels << tr("№ ТРК") << tr("Протокол") << tr("Порт") << tr("Скорость") << tr("Адрес");

    ui->treeWidgetTRK->setHeaderLabels(headerLabels);

    // Добавляем элементы в QTreeWidget
    QMap<int, QTreeWidgetItem*> items;
    for (const auto &d : disp) {
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->treeWidgetTRK);
        item->setText(0, QString::number(d.dispenser_id()));
        item->setText(1, d.portName());
        item->setText(2, QString::number(d.chanelProt()));
        item->setText(3, QString::number(d.chanelSpeed()));
        item->setText(4, QString::number(d.netAdress()));
        items[d.dispenser_id()] = item;
    }
    for (const auto &p : pump) {
        QTreeWidgetItem* parentItem = items[p.disp_id()];
        if (!parentItem) continue; // Пропустить pump, если не нашли соответствующий dispenser
        if (parentItem->childCount() == 0) { // Добавляем названия столбцов
            QStringList headerLabels;
            headerLabels << tr("Пистолет") << tr("Резервуар") << tr("Топливо");
                QTreeWidgetItem* headerItem = new QTreeWidgetItem(headerLabels);
            for (int i = 0; i < headerLabels.size(); ++i) {
                headerItem->setBackground(i, Qt::gray);
                headerItem->setForeground(i, Qt::white);
            }
            parentItem->addChild(headerItem);
            headerItem->setFlags(headerItem->flags() & ~Qt::ItemIsEditable); // Флаг "не редактируемый"
        }
        QTreeWidgetItem* item = new QTreeWidgetItem(parentItem);
        item->setText(0, QString::number(p.pump_id()));
        item->setText(1, QString::number(p.tank_id()));
        item->setText(2, p.shortName());
    }
    for (int i = 0; i < ui->treeWidgetTRK->columnCount(); ++i) {
        ui->treeWidgetTRK->resizeColumnToContents(i);
    }

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
        auto wk = new WorkplceForm(listWorkplace.at(i),titleObj, this);
        connect(wk,&WorkplceForm::signalSendUpdateWp,this,&ObjectWorkplaceWindow::slotUpdateWorkplace);
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

void ObjectWorkplaceWindow::slotUpdateWorkplace()
{
    emit signalWorkplaceUpdate(objectID);
    this->close();
}




void ObjectWorkplaceWindow::on_treeWidgetTRK_itemExpanded(QTreeWidgetItem *item)
{
    Q_UNUSED(item);
    // Установка ширины столбцов
    for (int i = 0; i < ui->treeWidgetTRK->columnCount(); ++i) {
            ui->treeWidgetTRK->resizeColumnToContents(i);
    }
}

