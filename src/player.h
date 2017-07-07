#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QObject>
#include <QFile>
#include <QFont>
#include <QStringList>
#include <QTextStream>
#include <QInputDialog>
#include <QTemporaryFile>
#include <QIODevice>


enum Circuit
{
	Monza = 1,
	Hockenheimring,
    YasMarina,
    Bahrain
};

class Player: public QObject
{
	Q_OBJECT
private:
	QString mPlayerName;
	QString mPlayerTimes[3];
	QString mTotalTime;
	QInputDialog mInputDialog;
	Circuit mCircuit;
public:
    Player();
	void updateFile();
	void SetCircuit(Circuit circuit);
signals:
	void playerInputFinished();
public slots:
	void endRaceDialog(QString lapTimeArray[], QString totalTime);
	void savePlayerName(QString name);
};

#endif // PLAYER_H
