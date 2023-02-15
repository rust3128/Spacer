#ifndef PINGDIALOG_H
#define PINGDIALOG_H
#include "ObjectWorkplace/workpalce.h"
#include "ObjectWorkplace/pingmodel.h"

#include <QDialog>

namespace Ui {
class PingDialog;
}

class PingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PingDialog(Workpalce *wk, QWidget *parent = nullptr);
    ~PingDialog();
signals:
    void signalStartPing();
    void signalSendHost(QString *);
private slots:
    void slotGetPingString(QByteArray output);
    void on_toolButtonCopyHost_clicked();

    void on_buttonBox_rejected();

private:
    void createUI();
private:
    Ui::PingDialog *ui;
    Workpalce *curWorplace;
    PingModel *modelPing;
};

#endif // PINGDIALOG_H
