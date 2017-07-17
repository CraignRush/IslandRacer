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
#include <QVector>


enum Circuit
{
	Monza = 1,
	Hockenheimring,
    YasMarina,
    Bahrain,
    Silverstone
};

class Player: public QObject
{
	Q_OBJECT
private:
	QString mPlayerName;
    QString mLapTimes[3];
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
    void endRaceDialog(QString* mLapTimeEnd,QString mTotalTimeEnd);
	void savePlayerName(QString name);
};

#endif // PLAYER_H
