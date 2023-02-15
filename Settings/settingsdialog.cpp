#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "GlobalSettings/globalsettings.h"

#include <QFileDialog>
#include <QSettings>

SettingsDialog::SettingsDialog(bool isNew, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    isNew(isNew)
{
    ui->setupUi(this);
    crP = new CriptPass();
    createUI();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::actionOpenDBTrigered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Файл базы данных"), "",
                                                    tr("База данных (*.gdb *.fdb);;Все файлы (*.*)"),nullptr,QFileDialog::DontUseNativeDialog);
    ui->lineEditDBFile->setText(fileName);
}

void SettingsDialog::actionOpenVNCrigered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("VNC Viever"), "",
                                                    tr("Программы (*.exe);;Все файлы (*.*)"),nullptr,QFileDialog::DontUseNativeDialog);
    ui->lineEditVNC->setText(fileName);
}

void SettingsDialog::createUI()
{
    QAction *openDBAction = ui->lineEditDBFile->addAction(QIcon(":/Images/folder_icon.png"),QLineEdit::TrailingPosition);
    QAction *openVNCAction = ui->lineEditVNC->addAction(QIcon(":/Images/folder_icon.png"),QLineEdit::TrailingPosition);

    connect(openDBAction,&QAction::triggered,this,&SettingsDialog::actionOpenDBTrigered);
    connect(openVNCAction,&QAction::triggered,this,&SettingsDialog::actionOpenVNCrigered);
    if(isNew){
        ui->lineEditServerName->setFocus();
    } else {
        readSettings();
    }
}

void SettingsDialog::readSettings()
{
    QSettings settings(GlobalSettings::CONFIG_FILE_NAME, QSettings::IniFormat);

    settings.beginGroup("DATABASE");
    ui->lineEditServerName->setText(settings.value("Server").toString());
    ui->lineEditPort->setText(settings.value("Port").toString());
    ui->lineEditDBFile->setText(settings.value("DataBase").toString());
    ui->lineEditUser->setText(settings.value("User").toString());
    ui->lineEditPass->setText(crP->decriptPass(settings.value("Password").toString()));
    settings.endGroup();
    settings.beginGroup("VNC");
    ui->lineEditVNC->setText(settings.value("VNCPath").toString());
    settings.endGroup();
}

void SettingsDialog::writeSettings()
{
    QSettings settings(GlobalSettings::CONFIG_FILE_NAME, QSettings::IniFormat);
    settings.beginGroup("DATABASE");
    settings.setValue("Server",ui->lineEditServerName->text().trimmed());
    settings.setValue("Port",ui->lineEditPort->text().trimmed());
    settings.setValue("DataBase", ui->lineEditDBFile->text().trimmed());
    settings.setValue("User",ui->lineEditUser->text().trimmed());
    settings.setValue("Password", crP->criptPass(ui->lineEditPass->text().trimmed()));
    settings.endGroup();
    settings.beginGroup("VNC");
    settings.setValue("VNCPath", ui->lineEditVNC->text().trimmed());
    settings.endGroup();
}



void SettingsDialog::on_buttonBox_accepted()
{
    writeSettings();
    this->accept();
}


void SettingsDialog::on_buttonBox_rejected()
{
    this->reject();
}

