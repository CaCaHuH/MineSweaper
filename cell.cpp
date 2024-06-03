#include "cell.h"

Cell::Cell(int id, QWidget *parent)
    : QLabel(parent), id(id)
{
    this->setMinimumWidth(22);
    this->setMinimumHeight(22);
    this->setMaximumWidth(22);
    this->setMaximumHeight(22);
    this->setPixmap(QPixmap("textures/frame.png"));

    mine = false;
    leftClickable = true;
    open = false;
    endGame = false;
}

bool Cell::SetMine()
{
    if (mine)
        return false;
    mine = true;
    return true;
}

bool Cell::IsMine()
{
    return mine;
}

bool Cell::IsOpen()
{
    return open;
}

void Cell::SetCountMines(int value)
{
    countMines = value;
}

int Cell::GetCountMass()
{
    return countMines;
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    if (endGame)
        return;
    if (event->button() == Qt::LeftButton)
    {
        if (!leftClickable || open)
            return;
        if (mine)
        {
            emit gameOver();
            return;
        }
        emit openArea(id);
        return;
    }
    else if (event->button() == Qt::RightButton && !open)
    {
        if (leftClickable)
        {
            leftClickable = false;
            this->setPixmap(QPixmap("textures/point.png"));
            emit plusPoint();
        }
        else
        {
            leftClickable = true;
            this->setPixmap(QPixmap("textures/frame.png"));
            emit minusPoint();
        }
    }
    else
        return;
}

void Cell::OpenCountMines()
{
    open = true;
    if (countMines == 0)
        this->setPixmap(QPixmap());
    else if (countMines == 1)
        this->setPixmap(QPixmap("textures/1.png"));
    else if (countMines == 2)
        this->setPixmap(QPixmap("textures/2.png"));
    else if (countMines == 3)
        this->setPixmap(QPixmap("textures/3.png"));
    else if (countMines == 4)
        this->setPixmap(QPixmap("textures/4.png"));
    else if (countMines == 5)
        this->setPixmap(QPixmap("textures/5.png"));
    else if (countMines == 6)
        this->setPixmap(QPixmap("textures/6.png"));
    else if (countMines == 7)
        this->setPixmap(QPixmap("textures/7.png"));
    else if (countMines == 8)
        this->setPixmap(QPixmap("textures/8.png"));
    else
        return;
}

void Cell::OpenMine()
{
    this->setPixmap(QPixmap("textures/mine.png"));
}

void Cell::SetEndGame()
{
    endGame = true;
}
