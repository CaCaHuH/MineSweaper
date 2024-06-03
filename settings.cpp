#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->error->hide();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_accept_clicked()
{
    if (CheckMaxMines())
        emit sendSettings(ui->hight->value(),ui->width->value(),ui->amountMines->value());
    close();
}

void Settings::on_exit_clicked()
{
    close();
}

bool Settings::CheckMaxMines()
{
    int maxMines = 0.5*ui->hight->value()*ui->width->value();
    if (ui->amountMines->value() > maxMines)
    {
        ui->error->setText("Превышено максимальное количество допустимых мин!\n(допустимое количество для этого поля " + QVariant(maxMines).toString() + " мин)");
        ui->error->show();
        return false;
    }
    ui->error->hide();
    return true;
}
