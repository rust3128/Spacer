#ifndef RDPCONNECTEDITDIALOG_H
#define RDPCONNECTEDITDIALOG_H

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

private:
    void createUI();
private:
    Ui::RdpConnectEditDialog *ui;
    int m_rdpID;
    int m_userID;
    int m_serverID;
    QList<QPair<int, int>> m_screenSizes;
};

#endif // RDPCONNECTEDITDIALOG_H
