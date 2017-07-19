#include <QApplication>
#include <Box2D/Box2D.h>
#include <QSplashScreen>
#include <mainmenu.h>
#include "game.h"
#include "pausemenu.h"
#include "speedometer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/images/images/Logo_Splash.png");
    QSplashScreen splash(pixmap);
    splash.setWindowFlag(Qt::WindowStaysOnTopHint);
    splash.setStyleSheet("background: tranparent;");
    splash.show();
    splash.showMessage("Loading modules",Qt::AlignHCenter | Qt::AlignTop);
   // splash.showMessage("Established connections");

    mainMenu menu;
    menu.showFullScreen();
    splash.finish(&menu);

    return a.exec();
}
