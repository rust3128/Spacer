#include "pingdialog.h"
#include "qclipboard.h"
#include "ui_pingdialog.h"

#include <QTextCodec>

PingDialog::PingDialog(Workpalce *wk, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PingDialog),
    curWorplace(wk)
{
    ui->setupUi(this);
    modelPing = new PingModel();
    connect(modelPing,&PingModel::signalSendOutPing,this,&PingDialog::slotGetPingString);
    connect(this,&PingDialog::signalSendHost,modelPing,&PingModel::getHostName);
    createUI();
    auto host = curWorplace->getIPADR();
    emit signalSendHost(&host);
    modelPing->start_command();

}

PingDialog::~PingDialog()
{
    delete ui;
}

void PingDialog::createUI()
{
    QString strTitle = "АЗС "+QString::number(curWorplace->getTerminalID());
    strTitle += " MPos"+curWorplace->getVerTypeName();
    if(curWorplace->getVerTypeID() == 4){
        strTitle += " PosID = " + QString::number(curWorplace->getPosID());
    }
    this->setWindowTitle(strTitle);
    ui->lineEditHost->setText(curWorplace->getIPADR());
}
void PingDialog::slotGetPingString(QByteArray output)
{
    QTextCodec *codec = QTextCodec::codecForName("cp-866");
    QString pStr = codec->toUnicode(output.data());
    ui->plainTextEditPing->appendPlainText(pStr.trimmed());
}

void PingDialog::on_toolButtonCopyHost_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->lineEditHost->text());

}


void PingDialog::on_buttonBox_rejected()
{
    this->reject();
}

