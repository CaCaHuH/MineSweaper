#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QRandomGenerator>
#include <QTime>
#include <QMap>
#include "cell.h"
#include "endgame.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    void timerEvent(QTimerEvent*) override;
    ~GameWindow();

public slots:
    void PlusPoint();
    void MinusPoint();
    void OpenArea(int id);
    void GameOver();
    void ExitGame();
    void NewGame();
    void SetSettings(int _height, int _width, int _amountMines);

private slots:
    void on_settingsArea_clicked();

private:
    void FillGameArea();
    void GenerateMines();
    void SetCountMines();
    bool CheckWinGame();
    void WinGame();

    Ui::GameWindow *ui;
    int height;
    int width;
    int amountMines;
    int countPoints;
    int countOpenCells;
    int timeGame;
    int idTimer;
    QMap<int,Cell*> listCell;
};
#endif // GAMEWINDOW_H
