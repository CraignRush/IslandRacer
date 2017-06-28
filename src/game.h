#ifndef GAME_H
#define GAME_H

#include "QObject"
#include "world.h"
#include "player.h"

enum Circuit
{
    Monza = 1,
    Hockenheimring,
    YasMarina
};

class Game: public QObject
{
	Q_OBJECT
private:
    World* mWorld;
	Player* mPlayer;

public:
    Game();
    Game(int screenWidth, int screenHeight, bool fullscreen);
    ~Game();
    void loadCircuit(enum Circuit circuit);

};

#endif // GAME_H
