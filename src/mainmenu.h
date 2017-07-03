#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
//#include "world.h"
#include "game.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTextStream>
#include <QFile>
#include <QStringList>
#include "ui_mainmenu.h"
#include <qscreen.h>
#include <QString>

namespace Ui {
class mainMenu;
}

class mainMenu : public QMainWindow
{
	Q_OBJECT
private:
	QString mName;
	QString mZeit;
	QString mLevel1HighscoreMatrix[2][10];
	QString mLevel2HighscoreMatrix[2][10];
	QString mLevel3HighscoreMatrix[2][10];

public:
	explicit mainMenu(QWidget *parent = 0);
	~mainMenu();

	QFont GillSansMT;


private slots:

	void on_main2Credits_clicked();

	void on_main2Garage_clicked();

	void on_main2Highscore_clicked();

	void on_main2Level1_clicked();

	void on_main2Manual_clicked();

	void on_main2QuitGame_clicked();

	void on_main2Settings_clicked();

	void on_level1_2Level2_clicked();

	void on_level1_2Level3_clicked();

	void on_level1_2Main_clicked();

	void on_level1_2Play_clicked();

	void on_level2_2Level1_clicked();

	void on_level2_2Level3_clicked();

	void on_level2_2Main_clicked();

	void on_level2_2Play_clicked();

	void on_level3_2Level1_clicked();

	void on_level3_2Level2_clicked();

	void on_level3_2Main_clicked();

	void on_level3_2Play_clicked();

	void on_garage2Main_clicked();

	void on_highscore2Main_clicked();

	void on_settings2Main_clicked();

	void on_manual2Main_clicked();

	void on_credits2Main_clicked();

	void on_garageAccelerationSlider_valueChanged(int value);

	void on_garageAccelerationSlider_sliderReleased();

	void on_garageTopspeedSlider_valueChanged(int value);

	void on_garageTopspeedSlider_sliderReleased();

	void on_garageHandlingSlider_valueChanged(int value);

	void on_garageHandlingSlider_sliderReleased();

    void setbackgroundsound();

    void playbuttonsound();

    void on_settingsBackgroundSoundOn_clicked();

    void on_settingsBackgroundSoundOff_clicked();

    void on_settingsBackgroundSoundSlider_valueChanged(int value);

    void on_settingsButtonSoundOn_clicked();

    void on_settingsButtonSoundOff_clicked();

    void on_settingsButtonSoundSlider_valueChanged(int value);

    void on_settingsRaceSoundOn_clicked();

    void on_settingsRaceSoundOff_clicked();

    void on_settingsRaceSoundSlider_valueChanged(int value);

    void on_settingsHighscoreResetButton_clicked();


private:
	Ui::mainMenu *ui;
	//World* world;
	Game* game;

	int screenWidth;
	int screenHeight;
	int accelerationValue;
	int handlingValue;
	int topspeedValue;
	int maximumValue;
    int active;
    int backgroundSoundValue;
    int buttonSoundValue;
    int raceSoundValue;

    //QMediaPlaylist *playlist;
    //QMediaPlayer *buttonsound;
    //QMediaPlayer *backgroundmusic;

};

#endif // MAINMENU_H
