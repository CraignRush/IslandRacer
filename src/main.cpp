#include <QApplication>
#include <Box2D/Box2D.h>
#include <mainmenu.h>
#include "game.h"
#include "pausemenu.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    mainMenu menu;
    menu.showFullScreen();

    return a.exec();
}
