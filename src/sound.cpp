#include "sound.h"

Sound::Sound()
{
    mCarAcceleratingEffect = new QSoundEffect();
    mCarAcceleratingEffect->setSource(QUrl("qrc:/sounds/sounds/car_accelerating_loop.wav"));
    mCarAcceleratingEffect->setVolume(40);
    mCarAcceleratingEffect->setLoopCount(QSoundEffect::Infinite);
}

Sound::~Sound()
{
    delete mCarAcceleratingEffect;
    mCarAcceleratingEffect = NULL;
}

void Sound::playBackgroundMusic()
{

}

void Sound::stopBackgroundMusic()
{

}

void Sound::setBackgroundMusicVolume(int volume)
{

}

void Sound::playCarSound()
{
    mCarAcceleratingEffect->play();
}

void Sound::stopCarSound()
{
    mCarAcceleratingEffect->stop();
}

void Sound::setCarSoundVolume(int volume)
{

}
