#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QSpacerItem>
#include "sound.h"
#include <QFile>

class PauseMenu : public QWidget
{
    Q_OBJECT

private:
    int mBackgroundMusicValue;
    int mBackgroundMusicActive;
    int mCarSoundValue;
    int mCarSoundActive;
    int mButtonSoundValue;
    int mButtonSoundActive;

    // Main Layout
    QGridLayout* mGridLayout;

    // Buttons for main layout
    QPushButton* mResumeButton;
    QPushButton* mRestartButton;
    QPushButton* mSettingsButton;
    QPushButton* mQuitButton;

    // Widgets for settings
    QPushButton* mBackButton;

    QLabel* mBackgroundMusicLabel;
    QPushButton* mBackgroundMusicOnButton;
    QPushButton* mBackgroundMusicOffButton;
    QSlider* mBackgroundMusicSlider;

    QLabel* mCarSoundLabel;
    QPushButton* mCarSoundOnButton;
    QPushButton* mCarSoundOffButton;
    QSlider* mCarSoundSlider;

    QLabel* mButtonSoundLabel;
    QPushButton* mButtonSoundOnButton;
    QPushButton* mButtonSoundOffButton;
    QSlider* mButtonSoundSlider;

    QSpacerItem* mHorizontalSpacer;

public:
    explicit PauseMenu(int screenHeight, QWidget *parent = 0);
    ~PauseMenu();

    //! Plays button Sound if active
    void playButtonSoundIfOn();

signals:
    //! Signal to resume game
    void resumeGame();

    //! Signal to restart game
    void restartGame();

    //! Signal to quit game
    void quitGame();

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

private slots:
    void resumeClicked();
    void restartClicked();
    void settingsClicked();
    void quitClicked();

    void backClicked();
    void backgroundMusicOnClicked();
    void backgroundMusicOffClicked();
    void backgroudnMusicVolumeChangd(int value);
    void carSoundOnClicked();
    void carSoundOffClicked();
    void carSoundVolumeChangd(int value);
    void buttonSoundOnClicked();
    void buttonSoundOffClicked();
    void buttonSoundVolumeChangd(int value);
};

#endif // PAUSEMENU_H
