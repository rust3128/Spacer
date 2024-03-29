#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int id, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void slotGetNetID(int netID,QString netName);
    void slotGetSearchTermID(int termID);
private slots:
    void on_actionSettings_triggered();
    void on_actionNetworkAzs_triggered();
    void on_tabWidget_currentChanged(int index);

    void on_tabWidget_tabCloseRequested(int index);

    void on_toolButtonGoHome_clicked();

    void on_actionUsers_triggered();

private:
    void createUI();
    void createConnections();
    void getUserStatus();
private:
    Ui::MainWindow *ui;
    QList<int> tabList;
    int searchTermID;
    int userID;
    bool isAdmin;
};
#endif // MAINWINDOW_H
