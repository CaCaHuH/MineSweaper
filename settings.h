#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

signals:
    void sendSettings(int,int,int);

private slots:
    void on_accept_clicked();
    void on_exit_clicked();

private:
    bool CheckMaxMines();

    Ui::Settings *ui;
};

#endif // SETTINGS_H
