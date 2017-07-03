#include "game.h"
#include <QTextStream>
#include <QStringList>
#include <QString>

Game::Game()
{
    mWorld = new World(1920,1080);
    mWorld->hide();
	mPlayer = new Player;
	//connect end race signal to player class
	connect(mWorld,SIGNAL(RaceFinished(QString[],QString)),mPlayer,SLOT(endRaceDialog(QString[],QString)));
}

Game::Game(int screenWidth, int screenHeight, bool fullscreen)
{
    mWorld = new World(screenWidth, screenHeight);
    if(fullscreen)
        mWorld->showFullScreen();
    mWorld->hide();
	mPlayer = new Player;
	//connect end race signal to player class
	connect(mWorld,SIGNAL(RaceFinished(QString[],QString)),mPlayer,SLOT(endRaceDialog(QString[],QString)));
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
		mPlayer->SetCircuit(Monza);
        break;
    case Hockenheimring:
        filename = ":/circuits/Hockenheimring.circuit";
		mPlayer->SetCircuit(Hockenheimring);
        break;
    case YasMarina:
        filename = ":/circuits/YasMarina.circuit";
		mPlayer->SetCircuit(YasMarina);
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
        WorldPosition* checkpointPositions;
        WorldPosition carPosition;

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
                checkpointPositions = (WorldPosition*) malloc(checkpointCount * 2 * sizeof(WorldPosition));

                list2 = list.value(1).split(QRegExp("(\\;)"));
                for(int a = 0; a < list2.length(); a++)
                {
                    list3 = list2.value(a).split(QRegExp("(\\,)"));
                    checkpointPositions[a] = WorldPosition(list3.value(0).toInt(), list3.value(1).toInt(), list3.value(2).toDouble());
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
                carPosition.setAngle(list.value(1).toDouble());
                continue;
            }
        }
        inputFile.close();

        // load circuit with parameter
        mWorld->loadTrack(width, height, background_path, gray_path, checkpointCount, checkpointPositions, 1, &carPosition, true);

        // show window on top
        mWorld->showFullScreen();
        mWorld->raise();
        mWorld->activateWindow();

        if(checkpointPositions != NULL)
            free(checkpointPositions);
	}
}
