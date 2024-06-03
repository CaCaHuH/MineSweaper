#include "endgame.h"
#include "ui_endgame.h"

EndGame::EndGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EndGame)
{
    ui->setupUi(this);
    this->setModal(true);
}

void EndGame::SetLabel(QString text)
{
    ui->label->setText(text);
}

EndGame::~EndGame()
{
    delete ui;
}

void EndGame::on_accept_clicked()
{
    emit newGame();
    close();
}

void EndGame::on_exit_clicked()
{
    emit exitGame();
    close();
}
