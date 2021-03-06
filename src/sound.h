#ifndef SOUND_H
#define SOUND_H

#include <QSoundEffect>
#include <QMediaPlayer>
#include <QThread>

//! Handles all sound interaction
/*!
 *  This class is implemented with the singelton design pattern
 *  to ensure that only one instance is running.
 *  The sound is played in a seperate background thread.
 */
class Sound : public QObject
{
    Q_OBJECT

private:
    static Sound* mSoundInstance;

    Sound(QObject* parent);
    QThread* mSoundThread;
    QSoundEffect* mCarAcceleratingSound;
    QSoundEffect* mButtonClickSound;
    QSoundEffect* mWaterSound;
    QSoundEffect* mRaceStartSound1;
    QSoundEffect* mRaceStartSound2;
    QSoundEffect* mFinishTheme;

    QMediaPlayer* mBackgroundMusic;
    QMediaPlaylist* mPlaylist;

public:
    //! Static method for singelton access
    static Sound* getSoundInstance(QObject* parent);
    ~Sound();

signals:
    //! Signal when thread is finished
    void finished();

public slots:
    //! Start background music
    void playBackgroundMusic();

    //! Stop background music
    void stopBackgroundMusic();

    //! Adjust background music volume
    void setBackgroundMusicVolume(int volume);

    //! Start car sound
    void playCarSound();

    //! Stop car sound
    void stopCarSound();

    //! Adjust car sound volume
    void setCarSoundVolume(int volume);

    //! Start button sound
    void playButtonSound();

    //! Start water sound
    void playWaterSound();

    //! Stop button sound
    void setButtonSoundVolume(int volume);

    //! Start race sound 1
    void playRaceStart1Sound();

    //! Start race sound 2
    void playRaceStart2Sound();

    //! Start finish sound
    void playFinishSound();
};

#endif // SOUND_H
