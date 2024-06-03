#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    height = 20;
    width = 20;
    amountMines = 50;
    NewGame();
}

void GameWindow::timerEvent(QTimerEvent *)
{
    timeGame++;
    int hours = timeGame/3600;
    int minutes = (timeGame - hours*3600)/60;
    int seconds = timeGame - hours*3600 - minutes*60;
    QString time;
    if (hours > 0)
        time = time + QVariant(hours).toString() + ":";
    if (minutes == 0)
        time = time + "00:";
    else if (minutes > 0 && minutes < 10)
        time = time + "0" + QVariant(minutes).toString() + ":";
    else
        time = time + QVariant(minutes).toString() + ":";
    if (seconds < 10)
        time = time + "0" + QVariant(seconds).toString();
    else
        time = time + QVariant(seconds).toString();
    ui->lcdTimer->display(time);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::PlusPoint()
{
    countPoints++;
    ui->findedMines->setNum(countPoints);
}

void GameWindow::MinusPoint()
{
    countPoints--;
    ui->findedMines->setNum(countPoints);
}

void GameWindow::OpenArea(int id)
{
    if (idTimer == -1)
        idTimer = startTimer(1000);

    listCell[id]->OpenCountMines();
    countOpenCells++;
    if (CheckWinGame())
    {
        WinGame();
        return;
    }
    int row = id/width;
    int column = id%width;

    if (listCell[id]->GetCountMass() != 0)
        return;

    for (int k : {row - 1, row, row + 1})
        for (int m : {column - 1, column, column + 1})
            if (k > -1 && k < height && m > -1 && m < width && !listCell[k*width + m]->IsOpen())
                OpenArea(k*width + m);
}

void GameWindow::GameOver()
{
    killTimer(idTimer);
    for (auto iter = listCell.begin(); iter != listCell.end(); iter++)
        if (iter.value()->IsMine())
            iter.value()->OpenMine();
    auto dialog = new EndGame();
    dialog->SetLabel("Конец игры!\nЖелаете сыграть еще одну партию?");
    connect(dialog,SIGNAL(newGame()),this,SLOT(NewGame()));
    connect(dialog,SIGNAL(exitGame()),this,SLOT(ExitGame()));
    dialog->show();
}

void GameWindow::ExitGame()
{
    close();
}

void GameWindow::NewGame()
{
    for (auto iter = listCell.begin(); iter != listCell.end(); iter++)
        delete iter.value();
    listCell.clear();
    countPoints = 0;
    countOpenCells = 0;
    timeGame = 0;
    idTimer = -1;
    ui->lcdTimer->display("00:00");
    ui->allMines->setNum(amountMines);
    ui->findedMines->setNum(countPoints);

    FillGameArea();
    GenerateMines();
    SetCountMines();
}

void GameWindow::SetSettings(int _height, int _width, int _amountMines)
{
    height = _height;
    width = _width;
    amountMines = _amountMines;
    NewGame();
}

void GameWindow::FillGameArea()
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            auto cell = new Cell(row*width + column);
            connect(cell,SIGNAL(openArea(int)),this,SLOT(OpenArea(int)));
            connect(cell,SIGNAL(gameOver()),this,SLOT(GameOver()));
            connect(cell,SIGNAL(plusPoint()),this,SLOT(PlusPoint()));
            connect(cell,SIGNAL(minusPoint()),this,SLOT(MinusPoint()));
            ui->gameArea->addWidget(cell,row,column);
            listCell.insert(row*width + column,cell);
        }
    }
}

void GameWindow::GenerateMines()
{
    QRandomGenerator randomizer = QRandomGenerator(QTime::currentTime().msec());
    int counter = 0;
    while (counter < amountMines)
    {
        int random = randomizer.generate()%(height*width);
        if (listCell[random]->SetMine())
            counter++;
    }
}

void GameWindow::SetCountMines()
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            if (listCell[row*width + column]->IsMine())
            {
                listCell[row*width + column]->SetCountMines(9);
                continue;
            }
            int counter = 0;
            for (int k : {row - 1, row, row + 1})
                for (int m : {column - 1, column, column + 1})
                    if (k > -1 && k < height && m > -1 && m < width && listCell[k*width + m]->IsMine())
                        counter++;
            listCell[row*width + column]->SetCountMines(counter);
        }
    }
}

bool GameWindow::CheckWinGame()
{
    if (countOpenCells == listCell.size() - amountMines)
        return true;
    return false;
}

void GameWindow::WinGame()
{
    killTimer(idTimer);
    auto dialog = new EndGame();
    dialog->SetLabel("Вы выйграли!\nЖелаете сыграть еще одну партию?");
    connect(dialog,SIGNAL(newGame()),this,SLOT(NewGame()));
    connect(dialog,SIGNAL(exitGame()),this,SLOT(ExitGame()));
    dialog->show();
}

void GameWindow::on_settingsArea_clicked()
{
    auto dialog = new Settings();
    connect(dialog,SIGNAL(sendSettings(int,int,int)),this,SLOT(SetSettings(int,int,int)));
    dialog->show();
}
