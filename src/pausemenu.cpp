#include "pausemenu.h"

PauseMenu::PauseMenu(int screenHeight, QWidget *parent) : QWidget(parent)
{
    // Read sound values from file
    QString filename = "settings/sound.set";
    QFile inputFile(filename);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        QString line;
        QStringList list;

        while(!in.atEnd())
        {
            line = in.readLine();
            list = line.split(QRegExp("\\="));

            if(list.value(0) == "backgroundSoundValue")
            {
                mBackgroundMusicValue = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "backgroundSoundActive")
            {
                mBackgroundMusicActive = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "buttonSoundValue")
            {
                mButtonSoundValue = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "buttonSoundActive")
            {
                mButtonSoundActive = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "raceSoundValue")
            {
                mCarSoundValue = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "raceSoundActive")
            {
                mCarSoundActive = list.value(1).toInt();
                continue;
            }
        }
        inputFile.close();
    }

    // Main Layout
    mGridLayout = new QGridLayout();

    // Define button size
    QSize normalButton(0.2 * screenHeight, 0.1 * screenHeight);
    QSize smallButton(0.15 * screenHeight, 0.075 * screenHeight);
    QSize arrowButton(0.125 * screenHeight, 0.1 * screenHeight);

    //Define Font
    QFont GillSansMT;
    GillSansMT.setFamily("GillSansMT");
    GillSansMT.setPointSize(20);
    GillSansMT.setBold(1);

    // Init menu buttons
    mResumeButton = new QPushButton();
    mResumeButton->setIcon(QIcon(":/images/images/resume.png"));
    mResumeButton->setIconSize(normalButton);
    mResumeButton->setStyleSheet("QPushButton{background: transparent;}");
    connect(mResumeButton, SIGNAL(clicked(bool)), this, SLOT(resumeClicked()));

    mRestartButton = new QPushButton();
    mRestartButton->setIcon(QIcon(":/images/images/restart.png"));
    mRestartButton->setIconSize(normalButton);
    mRestartButton->setStyleSheet("QPushButton{background: transparent;}");
    connect(mRestartButton, SIGNAL(clicked(bool)), this, SLOT(restartClicked()));

    mSettingsButton = new QPushButton();
    mSettingsButton->setIcon(QIcon(":/images/images/settings.png"));
    mSettingsButton->setIconSize(normalButton);
    mSettingsButton->setStyleSheet("QPushButton{background: transparent;}");
    connect(mSettingsButton, SIGNAL(clicked(bool)), this, SLOT(settingsClicked()));

    mQuitButton = new QPushButton();
    mQuitButton->setIcon(QIcon(":/images/images/quit.png"));
    mQuitButton->setIconSize(normalButton);
    mQuitButton->setStyleSheet("QPushButton{background: transparent;}");
    connect(mQuitButton, SIGNAL(clicked(bool)), this, SLOT(quitClicked()));

    // Add Buttons to layout
    mGridLayout->addWidget(mResumeButton, 0, 1, 1, 1);
    mGridLayout->addWidget(mRestartButton, 1, 1, 1, 1);
    mGridLayout->addWidget(mSettingsButton, 2, 1, 1, 1);
    mGridLayout->addWidget(mQuitButton, 3, 1, 1, 1);

    setLayout(mGridLayout);

    // Init widgets for settings tab
    mBackButton = new QPushButton();
    mBackButton->setIcon(QIcon(":/images/images/menu.png"));
    mBackButton->setIconSize(smallButton);
    mBackButton->setStyleSheet("QPushButton{background: transparent; color: white}");
    mBackButton->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(mBackButton, SIGNAL(clicked(bool)), this, SLOT(backClicked()));

    // Background music
    mBackgroundMusicLabel = new QLabel();
    mBackgroundMusicLabel->setStyleSheet("QLabel{background: transparent; color: black}");
    mBackgroundMusicLabel->setFont(GillSansMT);
    mBackgroundMusicLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    mBackgroundMusicLabel->setText("Background Sound:");
    mBackgroundMusicLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    mBackgroundMusicOnButton = new QPushButton();
    mBackgroundMusicOnButton->setStyleSheet("QPushButton{background: transparent; color: white}");
    mBackgroundMusicOnButton->setIcon(QIcon(":/images/images/soundOn.png"));
    mBackgroundMusicOnButton->setIconSize(arrowButton);
    mBackgroundMusicOnButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    connect(mBackgroundMusicOnButton, SIGNAL(clicked(bool)), this, SLOT(backgroundMusicOnClicked()));

    mBackgroundMusicOffButton = new QPushButton();
    mBackgroundMusicOffButton->setStyleSheet("QPushButton{background: transparent; color: white}");
    mBackgroundMusicOffButton->setIcon(QIcon(":/images/images/soundOff.png"));
    mBackgroundMusicOffButton->setIconSize(arrowButton);
    mBackgroundMusicOffButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    connect(mBackgroundMusicOffButton, SIGNAL(clicked(bool)), this, SLOT(backgroundMusicOffClicked()));

    mBackgroundMusicSlider = new QSlider();
    mBackgroundMusicSlider->setOrientation(Qt::Horizontal);
    mBackgroundMusicSlider->setStyleSheet("QSlider{background: transparent;}");
    mBackgroundMusicSlider->setValue(mBackgroundMusicValue);
    mBackgroundMusicSlider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    connect(mBackgroundMusicSlider, SIGNAL(valueChanged(int)), this, SLOT(backgroudnMusicVolumeChangd(int)));

    // Car sound
    mCarSoundLabel = new QLabel();
    mCarSoundLabel->setStyleSheet("QLabel{background: transparent; color: black}");
    mCarSoundLabel->setFont(GillSansMT);
    mCarSoundLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    mCarSoundLabel->setText("Race Sound:");
    mCarSoundLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);


    mCarSoundOnButton = new QPushButton();
    mCarSoundOnButton->setStyleSheet("QPushButton{background: transparent; color: white}");
    mCarSoundOnButton->setIcon(QIcon(":/images/images/soundOn.png"));
    mCarSoundOnButton->setIconSize(arrowButton);
    mCarSoundOnButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    connect(mCarSoundOnButton, SIGNAL(clicked(bool)), this, SLOT(carSoundOnClicked()));

    mCarSoundOffButton = new QPushButton();
    mCarSoundOffButton->setStyleSheet("QPushButton{background: transparent; color: white}");
    mCarSoundOffButton->setIcon(QIcon(":/images/images/soundOff.png"));
    mCarSoundOffButton->setIconSize(arrowButton);
    mCarSoundOffButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    connect(mCarSoundOffButton, SIGNAL(clicked(bool)), this, SLOT(carSoundOffClicked()));

    mCarSoundSlider = new QSlider();
    mCarSoundSlider->setOrientation(Qt::Horizontal);
    mCarSoundSlider->setStyleSheet("QSlider{background: transparent;}");
    mCarSoundSlider->setValue(mCarSoundValue);
    mCarSoundSlider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    connect(mCarSoundSlider, SIGNAL(valueChanged(int)), this, SLOT(carSoundVolumeChangd(int)));

    // Button sound
    mButtonSoundLabel = new QLabel();
    mButtonSoundLabel->setStyleSheet("QLabel{background: transparent; color: black}");
    mButtonSoundLabel->setFont(GillSansMT);
    mButtonSoundLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    mButtonSoundLabel->setText("Button Sound:");
    mButtonSoundLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    mButtonSoundOnButton = new QPushButton();
    mButtonSoundOnButton->setStyleSheet("QPushButton{background: transparent; color: white}");
    mButtonSoundOnButton->setIcon(QIcon(":/images/images/soundOn.png"));
    mButtonSoundOnButton->setIconSize(arrowButton);
    mButtonSoundOnButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    connect(mButtonSoundOnButton, SIGNAL(clicked(bool)), this, SLOT(buttonSoundOnClicked()));

    mButtonSoundOffButton = new QPushButton();
    mButtonSoundOffButton->setStyleSheet("QPushButton{background: transparent; color: white}");
    mButtonSoundOffButton->setIcon(QIcon(":/images/images/soundOff.png"));
    mButtonSoundOffButton->setIconSize(arrowButton);
    mButtonSoundOffButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    connect(mButtonSoundOffButton, SIGNAL(clicked(bool)), this, SLOT(buttonSoundOffClicked()));

    mButtonSoundSlider = new QSlider();
    mButtonSoundSlider->setOrientation(Qt::Horizontal);
    mButtonSoundSlider->setStyleSheet("QSlider{background: transparent;}");
    mButtonSoundSlider->setValue(mButtonSoundValue);
    mButtonSoundSlider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    connect(mButtonSoundSlider, SIGNAL(valueChanged(int)), this, SLOT(buttonSoundVolumeChangd(int)));

    // Horizontal spacer
    mHorizontalSpacer = new QSpacerItem(100, 0, QSizePolicy::Minimum, QSizePolicy::Preferred);

    // Set up Sound
    connect(this, SIGNAL(playBackgroundMusic()), Sound::getSoundInstance(this), SLOT(playBackgroundMusic()));
    connect(this, SIGNAL(stopBackgroundMusic()), Sound::getSoundInstance(this), SLOT(stopBackgroundMusic()));
    connect(this, SIGNAL(playButtonSound()), Sound::getSoundInstance(this), SLOT(playButtonSound()));
    connect(this, SIGNAL(playCarSound()), Sound::getSoundInstance(this), SLOT(playCarSound()));
    connect(this, SIGNAL(stopCarSound()), Sound::getSoundInstance(this), SLOT(stopCarSound()));
    connect(this, SIGNAL(setBackgroundMusicVolume(int)), Sound::getSoundInstance(this), SLOT(setBackgroundMusicVolume(int)));
    connect(this, SIGNAL(setCarSoundVolume(int)), Sound::getSoundInstance(this), SLOT(setCarSoundVolume(int)));
    connect(this, SIGNAL(setButtonSoundVolume(int)), Sound::getSoundInstance(this), SLOT(setButtonSoundVolume(int)));
}

PauseMenu::~PauseMenu()
{
    // Buttons in main layout
    delete mResumeButton;
    mResumeButton = NULL;

    delete mRestartButton;
    mRestartButton = NULL;

    delete mSettingsButton;
    mSettingsButton = NULL;

    delete mQuitButton;
    mQuitButton = NULL;

    // Widgets in settings
    delete mBackButton;
    mBackButton = NULL;

    delete mBackgroundMusicLabel;
    mBackgroundMusicLabel = NULL;

    delete mBackgroundMusicOnButton;
    mBackgroundMusicOnButton = NULL;

    delete mBackgroundMusicOffButton;
    mBackgroundMusicOffButton = NULL;

    delete mBackgroundMusicSlider;
    mBackgroundMusicSlider = NULL;


    delete mCarSoundLabel;
    mCarSoundLabel = NULL;

    delete mCarSoundOnButton;
    mCarSoundOnButton = NULL;

    delete mCarSoundOffButton;
    mCarSoundOffButton = NULL;

    delete mCarSoundSlider;
    mCarSoundSlider = NULL;


    delete mButtonSoundLabel;
    mButtonSoundLabel = NULL;

    delete mButtonSoundOnButton;
    mButtonSoundOnButton = NULL;

    delete mButtonSoundOffButton;
    mButtonSoundOffButton = NULL;

    delete mButtonSoundSlider;
    mButtonSoundSlider = NULL;

    // Main layout
    delete mGridLayout;
    mGridLayout = NULL;
}

void PauseMenu::playButtonSoundIfOn()
{
    if(mButtonSoundActive)
        emit playButtonSound();
}

void PauseMenu::resumeClicked()
{
    playButtonSoundIfOn();

    emit resumeGame();
}

void PauseMenu::restartClicked()
{
    playButtonSoundIfOn();

    emit restartGame();
}

void PauseMenu::settingsClicked()
{
    playButtonSoundIfOn();

    // Remove main widgets
    mGridLayout->removeWidget(mResumeButton);
    mGridLayout->removeWidget(mRestartButton);
    mGridLayout->removeWidget(mSettingsButton);
    mGridLayout->removeWidget(mQuitButton);

    mResumeButton->setParent(NULL);
    mRestartButton->setParent(NULL);
    mSettingsButton->setParent(NULL);
    mQuitButton->setParent(NULL);

    mResumeButton->hide();
    mRestartButton->hide();
    mSettingsButton->hide();
    mQuitButton->hide();

    // Add widgets for settings tab
    mGridLayout->addWidget(mBackButton, 1, 0, 1, 1);

    mGridLayout->addWidget(mBackgroundMusicLabel, 2, 1, 1, 1);
    mGridLayout->addWidget(mBackgroundMusicOnButton, 2, 2, 1, 1);
    mGridLayout->addWidget(mBackgroundMusicOffButton, 2, 3, 1, 1);
    mGridLayout->addWidget(mBackgroundMusicSlider, 2, 4, 1, 2);
    mGridLayout->addItem(mHorizontalSpacer, 2, 6, 1, 1, Qt::AlignCenter);

    mGridLayout->addWidget(mCarSoundLabel, 3, 1, 1, 1);
    mGridLayout->addWidget(mCarSoundOnButton, 3, 2, 1, 1);
    mGridLayout->addWidget(mCarSoundOffButton, 3, 3, 1, 1);
    mGridLayout->addWidget(mCarSoundSlider, 3, 4, 1, 2);
    //mGridLayout->addItem(mHorizontalSpacer, 3, 6, 1, 1, Qt::AlignCenter);

    mGridLayout->addWidget(mButtonSoundLabel, 4, 1, 1, 1);
    mGridLayout->addWidget(mButtonSoundOnButton, 4, 2, 1, 1);
    mGridLayout->addWidget(mButtonSoundOffButton, 4, 3, 1, 1);
    mGridLayout->addWidget(mButtonSoundSlider, 4, 4, 1, 2);
    //mGridLayout->addItem(mHorizontalSpacer, 4, 6, 1, 1, Qt::AlignCenter);

    // Adapt grid layout for settings menu
    //mGridLayout->setColumnMinimumWidth(6, 100);
}

void PauseMenu::quitClicked()
{
    playButtonSoundIfOn();

    emit quitGame();
}

void PauseMenu::backClicked()
{
    playButtonSoundIfOn();

    // Save current sound values
    QString out("backgroundSoundValue=" + QString::number(mBackgroundMusicValue) + "\n"
                "backgroundSoundActive=" + QString::number(mBackgroundMusicActive) + "\n"
                "buttonSoundValue=" + QString::number(mButtonSoundValue) + "\n"
                "buttonSoundActive=" + QString::number(mButtonSoundActive) + "\n"
                "raceSoundValue=" + QString::number(mCarSoundValue) + "\n"
                "raceSoundActive=" + QString::number(mCarSoundActive) + "\n");

    QString filename;
    filename = "settings/sound.set";
    QFile outputFile(filename);
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate| QIODevice::Text))
    {
        QTextStream in(&outputFile);
        in << out;
        outputFile.close();
    }

    // Remove main widgets
    mBackButton->setParent(NULL);

    mBackgroundMusicLabel->setParent(NULL);
    mBackgroundMusicOnButton->setParent(NULL);
    mBackgroundMusicOffButton->setParent(NULL);
    mBackgroundMusicSlider->setParent(NULL);

    mCarSoundLabel->setParent(NULL);
    mCarSoundOnButton->setParent(NULL);
    mCarSoundOffButton->setParent(NULL);
    mCarSoundSlider->setParent(NULL);

    mButtonSoundLabel->setParent(NULL);
    mButtonSoundOnButton->setParent(NULL);
    mButtonSoundOffButton->setParent(NULL);
    mButtonSoundSlider->setParent(NULL);

    mGridLayout->removeItem(mHorizontalSpacer);

    // Add widgets for settings tab
    mGridLayout->addWidget(mResumeButton, 0, 1, 1, 1);
    mGridLayout->addWidget(mRestartButton, 1, 1, 1, 1);
    mGridLayout->addWidget(mSettingsButton, 2, 1, 1, 1);
    mGridLayout->addWidget(mQuitButton, 3, 1, 1, 1);

    mResumeButton->show();
    mRestartButton->show();
    mSettingsButton->show();
    mQuitButton->show();
}

void PauseMenu::backgroundMusicOnClicked()
{
    playButtonSoundIfOn();

    mBackgroundMusicActive = 1;
    emit setBackgroundMusicVolume(mBackgroundMusicValue);
    mBackgroundMusicSlider->setValue(mBackgroundMusicValue);
}

void PauseMenu::backgroundMusicOffClicked()
{
    playButtonSoundIfOn();

    mBackgroundMusicActive = 0;
    emit setBackgroundMusicVolume(0);
    mBackgroundMusicSlider->setValue(0);
}

void PauseMenu::backgroudnMusicVolumeChangd(int value)
{
    if(mBackgroundMusicActive)
        mBackgroundMusicValue = value;
    emit setBackgroundMusicVolume(value);
}

void PauseMenu::carSoundOnClicked()
{
    playButtonSoundIfOn();

    mCarSoundActive = 1;
    emit setCarSoundVolume(mCarSoundValue);
    mCarSoundSlider->setValue(mCarSoundValue);
}

void PauseMenu::carSoundOffClicked()
{
    playButtonSoundIfOn();

    mCarSoundActive = 0;
    emit setCarSoundVolume(0);
    mCarSoundSlider->setValue(0);
}

void PauseMenu::carSoundVolumeChangd(int value)
{
    if(mCarSoundActive)
        mCarSoundValue = value;
    emit setCarSoundVolume(value);
}

void PauseMenu::buttonSoundOnClicked()
{
    playButtonSoundIfOn();
    mButtonSoundActive = 1;
    mButtonSoundSlider->setValue(mButtonSoundValue);
}

void PauseMenu::buttonSoundOffClicked()
{
    playButtonSoundIfOn();
    mButtonSoundActive = 0;
    mButtonSoundSlider->setValue(0);
}

void PauseMenu::buttonSoundVolumeChangd(int value)
{
    if(mButtonSoundActive)
        mButtonSoundValue = value;
    mButtonSoundSlider->setValue(value);
}
