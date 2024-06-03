#ifndef ENDGAME_H
#define ENDGAME_H

#include <QDialog>

namespace Ui {
class EndGame;
}

class EndGame : public QDialog
{
    Q_OBJECT

public:
    explicit EndGame(QWidget *parent = nullptr);
    void SetLabel(QString text);
    ~EndGame();

signals:
    void newGame();
    void exitGame();

private slots:
    void on_accept_clicked();
    void on_exit_clicked();

private:
    Ui::EndGame *ui;
};

#endif // ENDGAME_H
