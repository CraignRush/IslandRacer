#include "mainmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainMenu w;
    w.showFullScreen();

    return a.exec();
}
