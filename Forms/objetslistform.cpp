#include "objetslistform.h"
#include "ui_objetslistform.h"
#include "LogginCategories/loggincategories.h"
#include "ObjectWorkplace/objectworkplacewindow.h"
#include "ObjectWorkplace/edittitleobjectdialog.h"
#include "Deploys/getdeploys.h"
#include "global.h"
#include "Rdp/rdpconnecteditdialog.h"

#include <QInputDialog>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QThread>

ObjetsListForm::ObjetsListForm(int ID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjetsListForm),
    netID(ID)
{
    ui->setupUi(this);
    m_userID = globalUserID;
    typeConnect = typeGetTypeConnect();
    if(typeConnect) {
        centerDB = new CentralDBConnect(netID);
        centerDB->readFromDB();
        timer = new QTimer();
        connect(timer,&QTimer::timeout,this,&ObjetsListForm::deploysShow);

        timer->setInterval(ui->spinBoxInterval->value()*60000);
        timer->start(); // И запустим таймер
    }

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
    ui->labelNotConnectAZS->setHidden(typeConnect);
    if(typeConnect){
        deploysShow();
    } else {
        ui->groupBoxDeploys->hide();
    }
    createButtonRDP();
}

void ObjetsListForm::createButtonRDP()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM servers WHERE network_id = :netID");
    query.bindValue(0, netID);
    query.exec();

    QHBoxLayout *layout = new QHBoxLayout(ui->groupBoxRDP);
    ui->groupBoxRDP->setLayout(layout);

    while (query.next()) {
        int serverId = query.value("server_id").toInt();
        QString hostname = query.value("hostname").toString();

        QString ids = query.value("server_type").toString();
        QString names;
        QSqlQuery q;
        q.prepare("SELECT DESCRIPTION FROM server_type WHERE type_id IN (" + ids + ")");
        if (q.exec() && q.next())
        {
            names = QStringLiteral("\u2022")+q.value(0).toString();
            while (q.next())
            {
                names += "\n" + QStringLiteral("\u2022") + q.value(0).toString();
            }
        }

        QPushButton *button = new QPushButton(names, ui->groupBoxRDP);
        button->setObjectName(QString::number(serverId));
        connect(button, &QPushButton::clicked, this, &ObjetsListForm::slotPushButtonRdpClicked);

        QIcon icon(":/Images/rdp.png");
        button->setIcon(icon);
        button->setIconSize(QSize(32, 32));

        QSize size = button->sizeHint();
        size.setWidth(size.width() + 20); // добавляем небольшой отступ для красоты
        button->setFixedSize(size);

        button->setToolTip(hostname);
        button->setToolTipDuration(0);
        layout->addWidget(button);
    }
}


void ObjetsListForm::slotPushButtonRdpClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (button) {
        int serverID = button->objectName().toInt();
        QSqlQuery q;
        q.prepare("select r.rdp_id from rdpinfo r where r.user_id = ? and r.server_id = ?");
        q.bindValue(0, m_userID);
        q.bindValue(1, serverID);
        q.exec();
        if (!q.next()) {
            qInfo(logInfo()) << "Create new rdp connection;";
            RdpConnectEditDialog *rdpConDlg = new RdpConnectEditDialog(0, m_userID, serverID);
            if(rdpConDlg->exec() == QDialog::Accepted){

            }

        }
    }

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

void ObjetsListForm::deploysShow()
{
    // Создаем объект класса и передаем ему параметры
    GetDeploys *getDeps = new GetDeploys(ui->spinBoxPorog->value(), centerDB);
    // Создаем поток в которм будут производиться наша выборка
    QThread *thread = new QThread();
    // Перемещаем объект класса в поток
    getDeps->moveToThread(thread);

    //// Сигналы и слоты для взаимидействия с потоком

    // при старте потока выполняем некоторые действия в текущем потоке.
    // В моем случае на просто засекаю начало выбоки данных
    connect(thread,&QThread::started,this,&ObjetsListForm::slotStartGetDeploys);
    // При старте потока начинаем выборку данных
    connect(thread,&QThread::started,getDeps,&GetDeploys::createListDeploys);
    // Передача сообщения об ошибке при подключении к БД
    connect(getDeps, &GetDeploys::signalError, this, &ObjetsListForm::slotErrorGetDeploys);
    // Передача результирующего объекта QVertor из дочернего потока в основной
    connect(getDeps, &GetDeploys::signalSendDeployList, this, &ObjetsListForm::slotGetDeploys);
    // Окончание работы потока по завершению выбрки данных
    connect(getDeps, &GetDeploys::finish,thread,&QThread::quit);
    // Удаляем объект в потоке
    connect(getDeps, &GetDeploys::finish,getDeps, &GetDeploys::deleteLater);
    // Вы полняем действия по в основном потоке после завершения дочернего
    connect(getDeps, &GetDeploys::finish,this,&ObjetsListForm::slotFinishGetDeploys);
    // Прощаемся с дочерним потоком
    connect(thread,&QThread::finished,thread,&QThread::deleteLater);
    // Запускаем поток
    thread->start();

}

void ObjetsListForm::slotErrorGetDeploys(QString message)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Ошибка подключения."));
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText(tr("Произошла ошибка при подключении к центральной базе данных!"));
    msgBox.setInformativeText(tr("Текст ошибки:\n")+message);
    QString strDetali = QString("Server:\t"+centerDB->getServer()+":"+QString::number(centerDB->getPort())+
                                "\nDatabase:\t"+centerDB->getFileDB()+
                                "\nUser:\t"+centerDB->getUser());
    msgBox.setDetailedText(strDetali);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void ObjetsListForm::showDeploysData(bool show)
{
    ui->labelWaiting->setHidden(show);
    ui->labelDep1->setVisible(show);
    ui->labelLastDeploys->setVisible(show);
    ui->tableViewDeploys->setVisible(show);
    ui->labelDap2->setVisible(show);
    ui->spinBoxInterval->setVisible(show);
    ui->labelDep3->setVisible(show);
    ui->spinBoxPorog->setVisible(show);
    ui->pushButtonRefreshDeploys->setVisible(show);
}

bool ObjetsListForm::typeGetTypeConnect()
{
    QSqlQuery q;
    q.prepare("select n.typeconnect from networkazs n where n.network_id = ?");
    q.bindValue(0,netID);
    q.exec();
    q.next();
    return q.value(0).toBool();
}



void ObjetsListForm::slotStartGetDeploys()
{
    showDeploysData(false);
}

void ObjetsListForm::slotGetDeploys(QVector<DeployData> dp)
{
    deploys = dp;

}

void ObjetsListForm::slotFinishGetDeploys()
{
    ui->labelLastDeploys->setText(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss"));
    showDeploysData(true);

    depModel = new DeploysModel(deploys);
    proxyDep = new QSortFilterProxyModel();
    proxyDep->setSourceModel(depModel);
    ui->tableViewDeploys->setModel(proxyDep);
    ui->tableViewDeploys->resizeColumnsToContents();
    ui->tableViewDeploys->verticalHeader()->setDefaultSectionSize(ui->tableViewDeploys->verticalHeader()->minimumSectionSize());

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


void ObjetsListForm::on_pushButtonRefreshDeploys_clicked()
{
    deploysShow();
}


void ObjetsListForm::on_spinBoxInterval_valueChanged(int interval)
{
    timer->setInterval(interval*60000);
}



