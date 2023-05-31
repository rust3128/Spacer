#include "rdpconnecteditdialog.h"
#include "ui_rdpconnecteditdialog.h"

#include "LogginCategories/loggincategories.h"

#include <QApplication>
#include <QScreen>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QProcess>

RdpConnectEditDialog::RdpConnectEditDialog(int rdpID, int userID, int serverID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RdpConnectEditDialog),
    m_rdpID(rdpID), m_userID(userID), m_serverID(serverID)
{
    ui->setupUi(this);
    m_screenSizes = {
        {640, 480},
        {800, 600},
        {1024, 768},
        {1280, 720},
        {1280, 768},
        {1280, 800},
        {1280, 960},
        {1280, 1024},
        {1366, 768},
        {1440, 900},
        {1600, 900},
        {1680, 1050},
        {1920, 1080},
        {1920, 1200}
    };
    rdpPr = new RdpProperty();
    createUI();
}

RdpConnectEditDialog::~RdpConnectEditDialog()
{
    delete ui;
}

void RdpConnectEditDialog::createUI()
{
    QSqlQuery query;
    query.prepare("select n.name, s.hostname, s.port, s.server_type from servers s "
              "left join networkazs n on n.network_id = s.network_id "
              "where s.server_id= ?");
    query.bindValue(0,m_serverID);

    query.exec();
    query.next();

    ui->labelNetworkName->setText(query.value(0).toString());
    rdpPr->setHost(query.value(1).toString());
    rdpPr->setPort(query.value(2).toInt());
    ui->labelHost->setText(rdpPr->getHost()+":"+QString::number(rdpPr->getPort()));

    QString ids = query.value(3).toString();
    QString names;
    QSqlQuery q;
    q.prepare("SELECT DESCRIPTION FROM server_type WHERE type_id IN (" + ids + ")");
    if (q.exec() && q.next())
    {
        names = q.value(0).toString();
        while (q.next())
        {
            names += "\n" + q.value(0).toString();
        }
    }
    ui->labelServerType->setText(names);

    // Установка максимального и минимального значений слайдера
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(m_screenSizes.size()-1);

    // Установка шага изменения значений слайдера
    ui->horizontalSlider->setSingleStep(1);
    ui->horizontalSlider->setValue(m_screenSizes.size()-2);

    ui->checkBoxPanel->setChecked(false);
    ui->spinBoxPanel->setEnabled(false);



}



void RdpConnectEditDialog::on_horizontalSlider_valueChanged(int value)
{
    // Ищем пару значений ширины и высоты, соответствующую выбранному значению слайдера
    QPair<int, int> size = m_screenSizes.at(value);

    // Обновляем текст метки
    ui->spinBoxWidth->setValue(size.first);
    ui->spinBoxHeight->setValue(size.second);

}

void RdpConnectEditDialog::on_checkBoxPanel_clicked(bool checked)
{
    ui->checkBoxPanel->setChecked(checked);
    ui->spinBoxPanel->setEnabled(checked);
    if(checked) {
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        QRect availableGeometry = screen->availableGeometry();

        m_taskbarHeight = screenGeometry.height() - availableGeometry.height();
        ui->spinBoxPanel->setValue(m_taskbarHeight);
    } else {
        ui->spinBoxPanel->setValue(0);
    }
}

void RdpConnectEditDialog::on_pushButtonClose_clicked()
{
    this->reject();
}


void RdpConnectEditDialog::on_pushButtonConnect_clicked()
{
    if(!validateUserData()){
        return;
    }
    settingsRdpConnect();
}

void RdpConnectEditDialog::settingsRdpConnect()
{
    rdpPr->setUser(ui->lineEditUser->text().trimmed());
    rdpPr->setPass(ui->lineEditPass->text().trimmed());
    rdpPr->setW(ui->spinBoxWidth->value());
    rdpPr->setH(ui->spinBoxHeight->value()-ui->spinBoxPanel->value()*2);
    connectToRdp();
}

bool RdpConnectEditDialog::validateUserData()
{
    bool result = true;
    if (ui->lineEditUser->text().size() == 0 || ui->lineEditPass->text().size() == 0){
        QMessageBox::critical(this,tr("Оибка в учетных данных"),tr("Не указанно иммя пользователя либо пароль!"));
        result = false;
    }
    return result;
}

void RdpConnectEditDialog::connectToRdp()
{
    QProcess myRDP;
    QString program = "d:/Develop/rdp/wfreerdp.exe";
    QStringList argum;
    argum << "/v:termadm.itbi.corp" << "/size:1900x1035";
    myRDP.start(program, argum);
}
