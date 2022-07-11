#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "LogginCategories/loggincategories.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    createUI();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::actionOpenDBTrigered()
{
    qInfo(logInfo()) << "openClicked";
}

void SettingsDialog::createUI()
{
    QAction *openDBAction = ui->lineEditDBFile->addAction(QIcon(":/Images/folder_icon.png"),QLineEdit::TrailingPosition);
    connect(openDBAction,&QAction::triggered,this,&SettingsDialog::actionOpenDBTrigered);
}
