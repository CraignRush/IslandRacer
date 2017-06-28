#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QObject>
#include <QInputDialog>

class Player: public QObject
{
	Q_OBJECT
private:
	QString mPlayerName;
	QString mPlayerTimes[3];
public:
    Player();
public slots:
	void endRaceDialog(QString lapTimeArray[]);

};

#endif // PLAYER_H
