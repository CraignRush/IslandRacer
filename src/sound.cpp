#include "sound.h"
#include <QMediaPlaylist>
#include <QMediaPlayer>

// Define static member variable
Sound* Sound::mSoundInstance;

Sound::Sound(QObject* parent)
{       
    mBackgroundMusic = new QMediaPlayer();
    mPlaylist = new QMediaPlaylist();
    mPlaylist->addMedia(QUrl("qrc:/sounds/sounds/background_andi.wav"));
    mPlaylist->addMedia(QUrl("qrc:/sounds/sounds/intense-bg-music.wav"));
    // mPlaylist->addMedia(QUrl("qrc:/sounds/sounds/GT_Start.wav"));
    //mPlaylist->addMedia(QUrl("qrc:/sounds/sounds/GT_Stop.wav"));
    //mPlaylist->addMedia(QUrl("qrc:/sounds/sounds/WinTheme.wav"));
    mBackgroundMusic->setPlaylist(mPlaylist);
    mPlaylist->setPlaybackMode(QMediaPlaylist::Random);
    mBackgroundMusic->play();

    // Init enginge sond during car acceleration
    mCarAcceleratingSound = new QSoundEffect();
    mCarAcceleratingSound->setSource(QUrl("qrc:/sounds/sounds/car_accelerating_loop.wav"));
    mCarAcceleratingSound->setLoopCount(QSoundEffect::Infinite);
    mCarAcceleratingSound->setParent(parent);

    // Init click sound when button clicked
    mButtonClickSound = new QSoundEffect();
    mButtonClickSound->setSource(QUrl("qrc:/sounds/sounds/buttonsound.wav"));
    mButtonClickSound->setParent(parent);

    //    // Init background music
    //    mBackgroundMusic = new QSoundEffect();
    //    mBackgroundMusic->setSource(QUrl("qrc:/sounds/sounds/background_andi.wav"));
    //    mBackgroundMusic->setLoopCount(QSoundEffect::Infinite);
    //    mBackgroundMusic->setParent(parent);

    // Init race start sound(1)
    mRaceStartSound1 = new QSoundEffect();
    mRaceStartSound1->setSource(QUrl("qrc:/sounds/sounds/GT_Start.wav"));
    mRaceStartSound1->setParent(parent);

    // Init race start sound(2)
    mRaceStartSound2 = new QSoundEffect();
    mRaceStartSound2->setSource(QUrl("qrc:/sounds/sounds/GT_End.wav"));
    mRaceStartSound2->setParent(parent);

    // Init finish sound effect
    mFinishTheme = new QSoundEffect();
    mFinishTheme->setSource(QUrl("qrc:/sounds/sounds/WinTheme.wav"));
    mFinishTheme->setParent(parent);

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

void Sound::setBackgroundMusicVolume(int volume)    // volume range: 0..100
{
    mBackgroundMusic->setVolume(volume);        // volume range 0.0f ... 1.0f
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
    mCarAcceleratingSound->setVolume(volume/100.0f);
    mRaceStartSound1->setVolume(volume/100.0f);
    mRaceStartSound2->setVolume(volume/100.0f);
}

void Sound::playButtonSound()
{
    mButtonClickSound->play();
}

void Sound::setButtonSoundVolume(int volume)
{
    mButtonClickSound->setVolume(volume/100.0f);
}

void Sound::playRaceStart1Sound()
{
    mRaceStartSound1->play();
}

void Sound::playRaceStart2Sound()
{
    mRaceStartSound2->play();
}

void Sound::playFinishSound()
{
    mFinishTheme->play();
}
