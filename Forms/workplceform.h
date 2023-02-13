#ifndef WORKPLCEFORM_H
#define WORKPLCEFORM_H

#include "ObjectWorkplace/workpalce.h"

#include <QWidget>


namespace Ui {
class WorkplceForm;
}

class WorkplceForm : public QWidget
{
    Q_OBJECT

public:
    explicit WorkplceForm(Workpalce wk, QWidget *parent = nullptr);
    ~WorkplceForm();
private slots:
    void on_toolButtonPing_clicked();
    void slotStartConStatus();
    void slotGetStatus(bool st);
    void slotFinishConStatus();
private:
    void createUI();
    void getConnStatus();
private:
    Ui::WorkplceForm *ui;
    Workpalce curWorplace;
    bool isReadyVNC;
};

#endif // WORKPLCEFORM_H
