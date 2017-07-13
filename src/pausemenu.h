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
    void playButtonSoundIfOn();

signals:
    void resumeGame();
    void restartGame();
    void quitGame();

    void playBackgroundMusic();
    void stopBackgroundMusic();
    void setBackgroundMusicVolume(int volume);
    void playCarSound();
    void stopCarSound();
    void setCarSoundVolume(int volume);
    void playButtonSound();
    void setButtonSoundVolume(int volume);

public slots:
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
