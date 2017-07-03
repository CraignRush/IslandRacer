#ifndef SOUND_H
#define SOUND_H

#include <QSoundEffect>
#include <QMediaPlayer>
#include <QThread>


class Sound : public QObject
{
    Q_OBJECT

private:
    static Sound* mSoundInstance;

    Sound(QObject* parent);
    QThread* mSoundThread;
    QSoundEffect* mCarAcceleratingSound;
    QSoundEffect* mButtonClickSound;
    QSoundEffect* mBackgroundMusic;
    //QMediaPlayer* mBackgroundMusic;

public:
    static Sound* getSoundInstance(QObject* parent);
    ~Sound();

signals:
    void finished();

public slots:
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void setBackgroundMusicVolume(int volume);
    void playCarSound();
    void stopCarSound();
    void setCarSoundVolume(int volume);
    void playButtonSound();
    void setButtonSoundVolume(int volume);
};

#endif // SOUND_H
