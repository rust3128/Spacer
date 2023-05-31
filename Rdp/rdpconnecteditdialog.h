#ifndef RDPCONNECTEDITDIALOG_H
#define RDPCONNECTEDITDIALOG_H

#include "Rdp/rdpproperty.h"

#include <QDialog>

namespace Ui {
class RdpConnectEditDialog;
}

class RdpConnectEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RdpConnectEditDialog(int rdpID, int userID, int serverID, QWidget *parent = nullptr);
    ~RdpConnectEditDialog();
private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_checkBoxPanel_clicked(bool checked);

    void on_pushButtonClose_clicked();

    void on_pushButtonConnect_clicked();

private:
    void createUI();
    void settingsRdpConnect();
    bool validateUserData();
    void connectToRdp();
private:
    Ui::RdpConnectEditDialog *ui;
    int m_rdpID;
    int m_userID;
    int m_serverID;
    QList<QPair<int, int>> m_screenSizes;
    int m_taskbarHeight;
    RdpProperty *rdpPr;
};

#endif // RDPCONNECTEDITDIALOG_H
