#ifndef LISTNETWORKFORM_H
#define LISTNETWORKFORM_H

#include "Forms/modelnetworklist.h"

#include <QWidget>
#include <QSqlQueryModel>
#include <QObject>

namespace Ui {
class ListNetworkForm;
}

class ListNetworkForm : public QWidget
{
    Q_OBJECT

public:
    explicit ListNetworkForm(QWidget *parent = nullptr);
    ~ListNetworkForm();

signals:
    void signalSendNetID(int netID, QString netName);
private slots:
    void on_listViewNetwork_doubleClicked(const QModelIndex &idx);

private:
    void createUI();
    void createModel();
private:
    Ui::ListNetworkForm *ui;
    ModelNetworkList *modelNetwork;
};

#endif // LISTNETWORKFORM_H
