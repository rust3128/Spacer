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
private:
    void createUI();
private:
    Ui::WorkplceForm *ui;
    Workpalce curWorplace;
};

#endif // WORKPLCEFORM_H
