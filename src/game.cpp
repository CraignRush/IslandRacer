#include "game.h"
#include <QTextStream>
#include <QStringList>
#include <QString>

Game::Game()
{
    mWorld = new World(1920,1080);
    mWorld->hide();
}

Game::Game(int screenWidth, int screenHeight, bool fullscreen)
{
    mWorld = new World(screenWidth, screenHeight);
    if(fullscreen)
        mWorld->showFullScreen();
    mWorld->hide();
}

Game::~Game()
{
    delete mWorld;
    mWorld = NULL;
}

void Game::loadCircuit(Circuit circuit)
{
    QString filename;

    switch(circuit)
    {
    case Monza:
        filename = ":/circuits/Monza.circuit";
        break;
    case Hockenheimring:
        filename = ":/circuits/Hockenheimring.circuit";
        break;
    case YasMarina:
        filename = ":/circuits/YasMarina.circuit";
        break;
    }

    QFile inputFile(filename);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        QString line;
        QStringList list, list2, list3;

        int width = -1;
        int height = -1;
        QString background_path;
        QString gray_path;
        int checkpointCount = 0;
        QPoint* position_list;
        double* angle_list;
        QPoint carPosition(0.0, 0.0);
        double carAngle;

        while (!in.atEnd())
        {
            line = in.readLine();
            list = line.split(QRegExp("(\\=)"));

            if(list.value(0) == "WIDTH")
            {
                width = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "HEIGHT")
            {
                height = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "BACKGROUND")
            {
                background_path = list.value(1);
                continue;
            }
            if(list.value(0) == "GRAY")
            {
                gray_path = list.value(1);
                continue;
            }
            if(list.value(0) == "CHECKPOINT_COUNT")
            {
                checkpointCount = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "CHECKPOINTS")
            {
                position_list = (QPoint*) malloc(checkpointCount * 2 * sizeof(QPoint));
                angle_list = (double*) malloc(checkpointCount * 2 * sizeof(double));

                list2 = list.value(1).split(QRegExp("(\\;)"));
                for(int a = 0; a < list2.length(); a++)
                {
                    list3 = list2.value(a).split(QRegExp("(\\,)"));
                    position_list[a] = QPoint(list3.value(0).toInt(), list3.value(1).toInt());
                    angle_list[a] = list3.value(2).toDouble();
                }
                continue;
            }
            if(list.value(0) == "CAR_X")
            {
                carPosition.setX(list.value(1).toInt());
                continue;
            }
            if(list.value(0) == "CAR_Y")
            {
                carPosition.setY(list.value(1).toInt());
                continue;
            }
            if(list.value(0) == "CAR_ANGLE")
            {
                carAngle = list.value(1).toDouble();
                continue;
            }
        }
        inputFile.close();

        // load circuit with parameter
        mWorld->loadTrack(width, height, background_path, gray_path, checkpointCount, position_list, angle_list, carPosition, carAngle);

        // show window on top
        mWorld->showFullScreen();
        mWorld->raise();
        mWorld->activateWindow();

        if(position_list != NULL)
            free(position_list);

        if(angle_list != NULL)
            free(angle_list);
    }
}
