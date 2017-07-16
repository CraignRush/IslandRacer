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

//    PauseMenu menu(1080);
//    menu.show();

//    Game game;
//    game.loadCircuit(Silverstone, 10, 10, 10);

    return a.exec();
}
