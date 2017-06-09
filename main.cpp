#include <QApplication>
#include <Box2D/Box2D.h>
#include <world.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    World world(400, 400);
    world.show();

    return a.exec();
}
