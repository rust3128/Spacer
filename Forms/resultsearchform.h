#ifndef RESULTSEARCHFORM_H
#define RESULTSEARCHFORM_H

#include "Forms/searchobjectmodel.h"
#include "NetworkAzs/logodelegate.h"

#include <QDialog>

namespace Ui {
class ResultSearchForm;
}

class ResultSearchForm : public QDialog
{
    Q_OBJECT

public:
    explicit ResultSearchForm(int ID, QWidget *parent = nullptr);
    ~ResultSearchForm();
private slots:
    void on_tableViewObjects_doubleClicked(const QModelIndex &idx);

private:
    void createModels();
    void createUI();
private:
    Ui::ResultSearchForm *ui;
    int terminalID;
    SearchObjectModel *modelObjects;
    LogoDelegate *logoDelegate;
};

#endif // RESULTSEARCHFORM_H
