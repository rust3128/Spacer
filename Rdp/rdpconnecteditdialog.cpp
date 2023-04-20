#include "rdpconnecteditdialog.h"
#include "ui_rdpconnecteditdialog.h"

RdpConnectEditDialog::RdpConnectEditDialog(int rdpID, int userID, int serverID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RdpConnectEditDialog),
    m_rdpID(rdpID), m_userID(userID), m_serverID(serverID)
{
    ui->setupUi(this);
    m_screenSizes = {
        {640, 480},
        {800, 600},
        {1024, 768},
        {1280, 720},
        {1280, 768},
        {1280, 800},
        {1280, 960},
        {1280, 1024},
        {1366, 768},
        {1440, 900},
        {1600, 900},
        {1680, 1050},
        {1920, 1080},
        {1920, 1200}
    };
    createUI();
}

RdpConnectEditDialog::~RdpConnectEditDialog()
{
    delete ui;
}

void RdpConnectEditDialog::createUI()
{
    // Установка максимального и минимального значений слайдера
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(m_screenSizes.size()-1);

    // Установка шага изменения значений слайдера
    ui->horizontalSlider->setSingleStep(1);


    ui->horizontalSlider->setValue(m_screenSizes.size()-2);

}

void RdpConnectEditDialog::on_horizontalSlider_valueChanged(int value)
{
    // Ищем пару значений ширины и высоты, соответствующую выбранному значению слайдера
    QPair<int, int> size = m_screenSizes.at(value);

    // Обновляем текст метки
    ui->labelSlider->setText(QString("%1 на %2 пикселей").arg(size.first).arg(size.second));
}


