#include "gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    a.setStyle("Fusion");
    w.setWindowTitle("MineSweaper");
    w.show();
    return a.exec();
}
