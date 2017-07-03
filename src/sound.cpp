#include "sound.h"
#include <QMediaPlaylist>

// Define static member variable
Sound* Sound::mSoundInstance;

Sound::Sound(QObject* parent)
{       
    // Init enginge sond during car acceleration
    mCarAcceleratingSound = new QSoundEffect();
    mCarAcceleratingSound->setSource(QUrl("qrc:/sounds/sounds/car_accelerating_loop.wav"));
    mCarAcceleratingSound->setLoopCount(QSoundEffect::Infinite);
    mCarAcceleratingSound->setParent(parent);

    // Init click sound when button clicked
    mButtonClickSound = new QSoundEffect();
    mButtonClickSound->setSource(QUrl("qrc:/sounds/sounds/buttonsound.wav"));
    mButtonClickSound->setParent(parent);

    // Init background music
    mBackgroundMusic = new QSoundEffect();
    mBackgroundMusic->setSource(QUrl("qrc:/sounds/sounds/background_andi.wav"));
    mBackgroundMusic->setLoopCount(QSoundEffect::Infinite);
    mBackgroundMusic->setParent(parent);
    //mBackgroundMusic = new QMediaPlayer();
    //QMediaPlaylist* playlist = new QMediaPlaylist();
    //playlist->addMedia(QUrl("qrc:/sounds/sounds/background_andi.mp3"));
    //playlist->setPlaybackMode(QMediaPlaylist::Loop);
    //mBackgroundMusic->setPlaylist(playlist);

    // Start sound engine in extra thread in background
    mSoundThread = new QThread();
    this->moveToThread(mSoundThread);
    connect(this, SIGNAL(finished()), mSoundThread, SLOT(quit()));
    mSoundThread->start();
}

Sound* Sound::getSoundInstance(QObject* parent)
{
    if(mSoundInstance == NULL)
        mSoundInstance = new Sound(parent);

    return mSoundInstance;
}

Sound::~Sound()
{    
    emit finished();

    delete mCarAcceleratingSound;
    mCarAcceleratingSound = NULL;

    delete mButtonClickSound;
    mButtonClickSound = NULL;

    delete mBackgroundMusic;
    mBackgroundMusic = NULL;

    delete mSoundThread;
    mSoundInstance = NULL;
}

void Sound::playBackgroundMusic()
{
    mBackgroundMusic->play();
}

void Sound::stopBackgroundMusic()
{
    mBackgroundMusic->stop();
}

void Sound::setBackgroundMusicVolume(int volume)
{
    mBackgroundMusic->setVolume(volume);
}

void Sound::playCarSound()
{
    mCarAcceleratingSound->play();
}

void Sound::stopCarSound()
{
    mCarAcceleratingSound->stop();
}

void Sound::setCarSoundVolume(int volume)
{
    mCarAcceleratingSound->setVolume(volume);
}

void Sound::playButtonSound()
{
    mButtonClickSound->setVolume(1.0f);
    mButtonClickSound->play();
}

void Sound::setButtonSoundVolume(int volume)
{
    mButtonClickSound->setVolume(volume);
}
