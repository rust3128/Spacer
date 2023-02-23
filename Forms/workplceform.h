#ifndef WORKPLCEFORM_H
#define WORKPLCEFORM_H

#include "ObjectWorkplace/workpalce.h"
#include "ObjectWorkplace/objecttitle.h"

#include <QWidget>
#include <QProcess>


namespace Ui {
class WorkplceForm;
}

class WorkplceForm : public QWidget
{
    Q_OBJECT

public:
    explicit WorkplceForm(Workpalce wk, ObjectTitle *title, QWidget *parent = nullptr);
    ~WorkplceForm();
signals:
    void signalSendUpdateWp(void);
private slots:
    void on_toolButtonPing_clicked();
    void slotStartConStatus();
    void slotGetStatus(bool st);
    void slotFinishConStatus();
    void on_toolButtonVNC_clicked();
    void slotFinishVNC();

    void on_toolButtonRefresh_clicked();

    void on_toolButtonEdit_clicked();

private:
    void createUI();
    void getConnStatus();
private:
    Ui::WorkplceForm *ui;
    Workpalce curWorplace;
    bool isReadyVNC;
    QProcess *connectVNC;
    ObjectTitle *titleObject;
};

#endif // WORKPLCEFORM_H
