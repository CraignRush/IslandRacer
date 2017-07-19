#ifndef GAME_H
#define GAME_H

#include "QObject"
#include "world.h"
#include "player.h"

//enum Circuit
//{
//    Monza = 1,
//    Hockenheimring,
//    YasMarina
//};

//! Loads the game and connect player with world class
class Game: public QObject
{
	Q_OBJECT
private:
    World* mWorld;
	Player* mPlayer;
    bool mMultiplayer;

public:
    //! Generates world with standard screen size
    Game();

    //! Generates world with selected screen size
    Game(int screenWidth, int screenHeight, bool fullscreen);
    ~Game();

    //! Opens selected .circuit file and reads all necessary values
    /*! The read values are passed to world class
     * \param circuit Circuit enum values which are defined in player.h
     * \param speedValue Garage value for topspeed
     * \param accelerationValue Garage value for acceleration
     * \param handlingValue Garage value for handling
     */
    void loadCircuit(enum Circuit circuit, int speedValue, int accelerationValue, int handlingValue, int carValue);

public slots:
    //! Slot to select multi- or singleplayer
    void setGameMode(bool mp);
};

#endif // GAME_H
