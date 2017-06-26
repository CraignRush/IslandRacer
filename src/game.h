#ifndef GAME_H
#define GAME_H

#include "world.h"

enum Circuit
{
    Monza = 1,
    Hockenheimring,
    YasMarina
};

class Game
{
private:
    World* mWorld;

public:
    Game();
    ~Game();
    void loadCircuit(enum Circuit circuit);

};

#endif // GAME_H
