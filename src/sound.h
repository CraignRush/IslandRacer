#ifndef SOUND_H
#define SOUND_H

#include <QSoundEffect>

class Sound : public QObject
{
    Q_OBJECT

public:
    Sound();
    ~Sound();

public slots:
    void playBackgroundMusic();
    void stopBackgroundMusic();
    void setBackgroundMusicVolume(int volume);
    void playCarSound();
    void stopCarSound();
    void setCarSoundVolume(int volume);

private:
    QSoundEffect* mCarAcceleratingEffect;
};

#endif // SOUND_H
