#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include "Settings/criptpass.h"

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(bool isNew, QWidget *parent = nullptr);
    ~SettingsDialog();
private slots:
    void actionOpenDBTrigered();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    void createUI();
    void readSettings();
    void writeSettings();
private:
    Ui::SettingsDialog *ui;
    bool isNew;
    CriptPass *crP;
};

#endif // SETTINGSDIALOG_H
