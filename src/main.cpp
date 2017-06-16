#include <QApplication>
#include <Box2D/Box2D.h>
#include <world.h>
#include <mainmenu.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //for debugging purposes this also starts the "game"
    World world(800, 800);
    world.show();
    mainMenu menu;
    menu.show();

    return a.exec();
}
