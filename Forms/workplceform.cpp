#include "workplceform.h"
#include "ui_workplceform.h"
#include "LogginCategories/loggincategories.h"
#include "GlobalSettings/globalsettings.h"
#include "ObjectWorkplace/connstatusvnc.h"
#include "ObjectWorkplace/pingdialog.h"
#include "ObjectWorkplace/editworkplacedialog.h"

#include <QThread>

WorkplceForm::WorkplceForm(Workpalce wk, ObjectTitle *title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkplceForm),
    curWorplace(wk),
    titleObject(title)

{
    ui->setupUi(this);
    createUI();
}

WorkplceForm::~WorkplceForm()
{
    delete ui;
}

void WorkplceForm::createUI()
{
    QString verType = "MPos"+curWorplace.getVerTypeName();
    if(curWorplace.getVerTypeID() == 4){
        verType += " PosID = " + QString::number(curWorplace.getPosID());
    }
    ui->labelVerType->setText(verType);
    ui->labelIP->setText(curWorplace.getIPADR());
    ui->toolButtonVNC->setEnabled(false);
    getConnStatus();
}

void WorkplceForm::getConnStatus()
{
    ConnStatusVNC *statusVNC = new ConnStatusVNC(curWorplace.getIPADR(), curWorplace.getPortVNC());

    QThread *thread = new QThread();

    statusVNC->moveToThread(thread);

    connect(thread,&QThread::started,this,&WorkplceForm::slotStartConStatus);
    connect(thread,&QThread::started,statusVNC,&ConnStatusVNC::getConnStatus);
    connect(statusVNC,&ConnStatusVNC::signalSendStatus,this,&WorkplceForm::slotGetStatus);
    connect(statusVNC,&ConnStatusVNC::finish,thread,&QThread::quit);
    connect(statusVNC,&ConnStatusVNC::finish,statusVNC,&ConnStatusVNC::deleteLater);
    connect(statusVNC,&ConnStatusVNC::finish,this,&WorkplceForm::slotFinishConStatus);
    connect(thread,&QThread::finished,thread,&QThread::deleteLater);

    thread->start();
}

void WorkplceForm::slotStartConStatus()
{
    ui->labelStatus->setPixmap(QPixmap(":/Images/waiting_icon.png"));
}

void WorkplceForm::slotGetStatus(bool st)
{
    isReadyVNC = st;
}

void WorkplceForm::slotFinishConStatus()
{
    QPixmap pixmap;

    if(isReadyVNC){
        pixmap = QPixmap(":/Images/online_network_icon.png");
        setStyleSheet("background-color: #E6F3E6;"); // светло-зеленый цвет
    } else {
        pixmap = QPixmap(":/Images/offline_network_icon.png");
        setStyleSheet("background-color: #ff5252;"); // красный цвет
    }
    ui->labelStatus->setPixmap(pixmap);
    ui->toolButtonVNC->setEnabled(isReadyVNC);

}

void WorkplceForm::on_toolButtonPing_clicked()
{
    PingDialog *pingDlg = new PingDialog(&curWorplace);
    pingDlg->exec();
}

void WorkplceForm::on_toolButtonVNC_clicked()
{
    QStringList argum;
    argum << "-host="+curWorplace.getIPADR() << "-port="+QString::number(curWorplace.getPortVNC())
          << "-password="+curWorplace.getPassVNC();
    connectVNC = new QProcess(this);
    connect(connectVNC,&QProcess::finished,this,&WorkplceForm::slotFinishVNC);
    connectVNC->setReadChannel(QProcess::StandardError);
    connectVNC->start(GlobalSettings::VNC_RUN_PATH,argum);
}

void WorkplceForm::slotFinishVNC()
{
    QByteArray *arr = new QByteArray;
    *arr = connectVNC->readAllStandardError();
    qInfo(logInfo()) << "VNC Error" << arr->data();
}


void WorkplceForm::on_toolButtonRefresh_clicked()
{
    getConnStatus();
}


void WorkplceForm::on_toolButtonEdit_clicked()
{
    EditWorkplaceDialog *editWork = new EditWorkplaceDialog(titleObject, &curWorplace);
    if(editWork->exec() == QDialog::Accepted){
        emit signalSendUpdateWp();
    }

}

