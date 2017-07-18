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
#include "sound.h"

namespace Ui {
class mainMenu;
}

//! Creates the main menu
class mainMenu : public QMainWindow
{
	Q_OBJECT
private:
    Ui::mainMenu *ui;
    Game* game;

    // Screen size
    int mScreenWidth;
    int mScreenHeight;

    // Garage values
    int mAccelerationValue;
    int mHandlingValue;
    int mTopspeedValue;
    int mMaximumValue;
    int mMinimumValue = 10;
    int mMonzaValue;
    int mHockenheimringValue;
    int mYasmarinaValue;
    int mBahrainValue;
    int mSilverstoneValue;

    // Sound values
    int mBackgroundSoundActive;
    int mBackgroundSoundValue;
    int mButtonSoundActive;
    int mButtonSoundValue;
    int mRaceSoundActive;
    int mRaceSoundValue;

    // Highscore selector
    int mHighscoreTrackNumber = 0;

    // Game Mode
    bool mIsMultiplayer;

public:
	explicit mainMenu(QWidget *parent = 0);
	~mainMenu();

	QFont GillSansMT;

    //! The highscore gets written in the table
    void insertHighscoreToTable();

    //! The maximum value for the garage gets computed from the highscores
    void computeMaximumValue();

    //! The number of stars above the levels get set according to the highscores
    void setStars();

    //! The values set in the garage get saved
    void saveGarage();

signals:
    //! Signal to start background music
    void playBackgroundMusic();

    //! Signal to stop background music
    void stopBackgroundMusic();

    //! Signal to set volume of background music
    /*!
     * \param volume Volume of the background music
     */
    void setBackgroundMusicVolume(int volume);

    //! Signal to start car sound
    void playCarSound();

    //! Signal to stop car sound
    void stopCarSound();

    //! Signal to set volume of car sound
    /*!
     * \param volume Volume of the car sound
     */
    void setCarSoundVolume(int volume);

    //! Signal to play button sound
    void playButtonSound();

    //! Signal to set volume of button sound
    /*!
     * \param volume Volume of the button sound
     */
    void setButtonSoundVolume(int volume);

    //! Signal to select multi- or singleplayer
    /*!
     * \param mp Value to select game mode (false -> singleplayer, true -> multiplayer)
     */
    void setGameMode(bool mp);

private slots:

	void on_main2Credits_clicked();

	void on_main2Garage_clicked();

	void on_main2Highscore_clicked();

	void on_main2Level1_clicked();

	void on_main2Manual_clicked();

	void on_main2QuitGame_clicked();

	void on_main2Settings_clicked();

    void on_garage2Main_clicked();

    void on_garageAccelerationSlider_valueChanged(int value);

    void on_garageAccelerationSlider_sliderReleased();

    void on_garageTopspeedSlider_valueChanged(int value);

    void on_garageTopspeedSlider_sliderReleased();

    void on_garageHandlingSlider_valueChanged(int value);

    void on_garageHandlingSlider_sliderReleased();

    void on_highscore2Main_clicked();

    void on_highscore2Right_clicked();

    void on_highscore2Left_clicked();

    void on_settings2Main_clicked();

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

    void setbackgroundsound();

    void playbuttonsound();

    void on_manual2Main_clicked();

    void on_credits2Main_clicked();

    void on_playTypeSelect2SinglePlayer_clicked();

    void on_playTypeSelect2Multiplayer_clicked();

    void on_playTypeSelect2Main_clicked();

    void on_level1_2Left_clicked();

    void on_level1_2Right_clicked();

	void on_level1_2Main_clicked();

	void on_level1_2Play_clicked();

    void on_level2_2Left_clicked();

    void on_level2_2Right_clicked();

	void on_level2_2Main_clicked();

	void on_level2_2Play_clicked();

    void on_level3_2Left_clicked();

    void on_level3_2Right_clicked();

	void on_level3_2Main_clicked();

	void on_level3_2Play_clicked();

    void on_level4_2Main_clicked();

    void on_level4_2Left_clicked();

    void on_level4_2Right_clicked();

    void on_level4_2Play_clicked();

    void on_level5_2Right_clicked();

    void on_level5_2Left_clicked();

    void on_level5_2Main_clicked();

    void on_level5_2Play_clicked();
};

#endif // MAINMENU_H
