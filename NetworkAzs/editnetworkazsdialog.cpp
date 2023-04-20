#include "editnetworkazsdialog.h"
#include "ui_editnetworkazsdialog.h"
#include "LogginCategories/loggincategories.h"
#include "editserverdialog.h"


#include <QFileDialog>
#include <QBuffer>
#include <QInputDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QTcpSocket>

EditNetworkAzsDialog::EditNetworkAzsDialog(int ID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditNetworkAzsDialog),
    networkID(ID)
{
    ui->setupUi(this);
    connect(ui->labelLogo,&ClickableLabel::clicked,this,&EditNetworkAzsDialog::slotLogoFileOpen);
    editNetAzs = new EditNetworkAzsData(networkID);
    netData = editNetAzs->getNetData();
    centralDB = new CentralDBConnect(networkID);
    createModel();
    createUI();

}

EditNetworkAzsDialog::~EditNetworkAzsDialog()
{
    delete ui;
}

void EditNetworkAzsDialog::actionOpenDBTrigered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Файл базы данных"), "",
                                                    tr("База данных (*.gdb *.fdb);;Все файлы (*.*)"),nullptr,QFileDialog::DontUseNativeDialog);
    ui->lineEditDataBaseFile->setText(fileName);
}

void EditNetworkAzsDialog::slotLogoFileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Загрузка логотипа"), "",
                                                    tr("Файлы изображений (*.png *.jpg *.jpeg);;Все файлы (*.*)"),nullptr,QFileDialog::DontUseNativeDialog);
    if(fileName.size() >0) {
        QPixmap inPixmap(fileName);
        auto w = ui->labelLogo->width();
        auto h = ui->labelLogo->height();
        inPixmap = inPixmap.scaled(w,h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->labelLogo->setPixmap(inPixmap);
        QByteArray inByteArray;
        QBuffer inBuffer( &inByteArray );                   // Сохранение изображения производим через буффер
        inBuffer.open( QIODevice::WriteOnly );              // Открываем буффер
        inPixmap.save( &inBuffer, "PNG" );                  // Записываем inPixmap в inByteArray
        netData->setLogo(inByteArray);
    }
}

void EditNetworkAzsDialog::createUI()
{
    ui->lineEditName->setText(netData->getNetName());
    ui->checkBoxConnFromTerm->setChecked(netData->getTypeConnect());
    ui->checkBoxIsActive->setChecked(netData->getIsActive());
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData(netData->getLogo());
    if(!outPixmap.isNull())
        ui->labelLogo->setPixmap(outPixmap);
    ui->tableViewServers->setModel(modelServers);
    ui->tableViewServers->hideColumn(0);
    ui->tableViewServers->resizeColumnsToContents();
    ui->tableViewServers->resizeRowsToContents();

    QAction *openDBAction = ui->lineEditDataBaseFile->addAction(QIcon(":/Images/folder_icon.png"),QLineEdit::TrailingPosition);
    connect(openDBAction,&QAction::triggered,this,&EditNetworkAzsDialog::actionOpenDBTrigered);
    centralDB->readFromDB();
    ui->lineEditServer->setText(centralDB->getServer());
    if(centralDB->getPort() != 0)
        ui->spinBoxPort->setValue(centralDB->getPort());
    ui->lineEditDataBaseFile->setText(centralDB->getFileDB());
    ui->lineEditUser->setText(centralDB->getUser());
    ui->lineEditPass->setText(centralDB->getPass());

}

void EditNetworkAzsDialog::createModel()
{
    modelServers = new ModelSrvers(this);
    QString strSQL = QString("select s.server_id, s.hostname, s.port, s.server_type, s.isactive from servers s where s.network_id = %1")
            .arg(networkID);
    modelServers->setQuery(strSQL);
    modelServers->setHeaderData(1,Qt::Horizontal,tr("Хост/IP"));
    modelServers->setHeaderData(2,Qt::Horizontal,tr("Порт"));
    modelServers->setHeaderData(3,Qt::Horizontal,tr("Роль"));
    modelServers->setHeaderData(4,Qt::Horizontal,tr("Работает"));
}

void EditNetworkAzsDialog::updateCentralDB()
{
    centralDB->setServer(ui->lineEditServer->text().trimmed());
    centralDB->setPort(ui->spinBoxPort->value());
    centralDB->setFileDB(ui->lineEditDataBaseFile->text().trimmed());
    centralDB->setUser(ui->lineEditUser->text().trimmed());
    centralDB->setPass(ui->lineEditPass->text().trimmed());
}

void EditNetworkAzsDialog::on_buttonBox_rejected()
{
    this->reject();
}

void EditNetworkAzsDialog::on_buttonBox_accepted()
{
    netData->setNetName(ui->lineEditName->text().trimmed());
    netData->setTypeConnect(ui->checkBoxConnFromTerm->isChecked());
    netData->setIsActive(ui->checkBoxIsActive->isChecked());
    editNetAzs->writeNetworkData(netData);
    updateCentralDB();
    centralDB->writeToDB();
    this->accept();
}

void EditNetworkAzsDialog::on_pushButtonAddServer_clicked()
{
    bool ok;
    QString serverNew = QInputDialog::getText(this, tr("Новый сервер"), tr("Укажите хост или IP адрес нового сервера:"),
                                               QLineEdit::Normal,"",&ok);
    if(ok && serverNew.size() >=3){
        QSqlQuery q;
        q.prepare("EXECUTE PROCEDURE ADD_SERVER(:host, :netID)");
        q.bindValue(0,serverNew);
        q.bindValue(1,networkID);
        if(!q.exec()){
            qCritical(logCritical()) << tr("Не удлось добавить новый сервер.") << q.lastError().text();
            return;
        }
        q.next();
        int newServerID = q.value(0).toInt();
        q.exec("commit work");
        q.finish();
        EditServerDialog *editServer = new EditServerDialog(newServerID,this);
        if(editServer->exec() == QDialog::Accepted){
            modelServers->setQuery(modelServers->query().lastQuery());
            ui->tableViewServers->resizeColumnsToContents();
            ui->tableViewServers->resizeRowsToContents();
        }
    }
}


void EditNetworkAzsDialog::on_tableViewServers_doubleClicked(const QModelIndex &idx)
{
    EditServerDialog *editServerDlg = new EditServerDialog(modelServers->data(modelServers->index(idx.row(),0),Qt::DisplayRole).toInt());
    if(editServerDlg->exec() == QDialog::Accepted){
        modelServers->setQuery(modelServers->query().lastQuery());
        ui->tableViewServers->resizeRowsToContents();
        ui->tableViewServers->resizeColumnsToContents();
    }
}



