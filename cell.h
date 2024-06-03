#ifndef CELL_H
#define CELL_H

#include <QLabel>
#include <QMouseEvent>

class Cell : public QLabel
{
    Q_OBJECT

public:
    Cell(int id, QWidget *parent = nullptr);
    bool SetMine();
    bool IsMine();
    bool IsOpen();
    void SetCountMines(int value);
    int GetCountMass();
    void OpenCountMines();
    void OpenMine();
    void SetEndGame();

signals:
    void gameOver();
    void plusPoint();
    void minusPoint();
    void openArea(int);

private:
    void mousePressEvent(QMouseEvent *event) override;

    bool mine;
    bool leftClickable;
    bool open;
    bool endGame;
    int countMines;
    int id;
};

#endif // CELL_H
