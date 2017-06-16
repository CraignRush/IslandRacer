#include <QApplication>
#include <Box2D/Box2D.h>
#include <world.h>
#include <mainmenu.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    World world(800, 800);
    world.show();
/*
    mainMenu menu;
    menu.showFullScreen();
*/
    return a.exec();
}
