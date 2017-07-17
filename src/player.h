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

//! @enum all possible racing maps
enum Circuit
{
	Monza = 1,
	Hockenheimring,
    YasMarina,
    Bahrain,
    Silverstone
};

    //! Handles the user input after a finished race and saves the highscores
class Player: public QObject
{
	Q_OBJECT
private:
    //! Contains the player name string
	QString mPlayerName;
    //! Contains the three lap times
    QString mLapTimes[3];
    //! Contains the total race time
	QString mTotalTime;
    //! Dialog for the user name input
	QInputDialog mInputDialog;
    //! Contains the circuit name of the finished race
	Circuit mCircuit;
public:
    //! Creates an instance of Player and sets attributes of \var mInputDialog
    Player();
    //! Searches for the right insertion point of the highscore, truncates and updates the highscore file
	void updateFile();
    //! Get the right circuit from game
	void SetCircuit(Circuit circuit);
signals:
    //!Emitted when user name is saved or user aborted
	void playerInputFinished();
public slots:
    //! Saves the times of the race to member variables for further processing and starts input dialog
    //! @param mLapTimeEnd QString Array with the three lap times
    //! @param mTotalTimeEnd QString with the total race time
    void endRaceDialog(QString* mLapTimeEnd,QString mTotalTimeEnd);
    //! @brief Saves the name to highscore file or restarts the dialog if name is empty
    //! Connected to the event textValueSelected of mInputDialog
    //! @param name Content of the mInputDialog Box. Sometimes the player's name, mostly crap
	void savePlayerName(QString name);
};

#endif // PLAYER_H
