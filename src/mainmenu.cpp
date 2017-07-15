#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "qscreen.h"
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QPixmap>
#include <QPalette>


mainMenu::mainMenu(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::mainMenu)
{

	ui->setupUi(this);

	// Initial Values
	ui->stackedWidget->setCurrentIndex(0);

    QString filename;

    filename = "settings/garage.set";
    QFile inputFile4(filename);
    if (inputFile4.open(QIODevice::ReadOnly))
    {
        QTextStream in4(&inputFile4);
        QString line;
        QStringList list;

        while(!in4.atEnd())
        {
            line = in4.readLine();
            list = line.split(QRegExp("\\="));

            if(list.value(0) == "topspeedValue")
            {
                topspeedValue = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "accelerationValue")
            {
                accelerationValue = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "handlingValue")
            {
                handlingValue = list.value(1).toInt();
                continue;
            }
        }
        inputFile4.close();
    }

    filename = "settings/sound.set";
    QFile inputFile5(filename);
    if (inputFile5.open(QIODevice::ReadOnly))
    {
        QTextStream in5(&inputFile5);
        QString line;
        QStringList list;

        while(!in5.atEnd())
        {
            line = in5.readLine();
            list = line.split(QRegExp("\\="));

            if(list.value(0) == "backgroundSoundValue")
            {
                backgroundSoundValue = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "backgroundSoundActive")
            {
                backgroundSoundActive = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "buttonSoundValue")
            {
                buttonSoundValue = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "buttonSoundActive")
            {
                buttonSoundActive = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "raceSoundValue")
            {
                raceSoundValue = list.value(1).toInt();
                continue;
            }
            if(list.value(0) == "raceSoundActive")
            {
                raceSoundActive = list.value(1).toInt();
                continue;
            }
        }
        inputFile5.close();
    }

	maximumValue = 10;


	// Get Screensize
	QScreen *screen = QGuiApplication::primaryScreen();
	QRect  screenGeometry = screen->geometry();
	screenHeight = screenGeometry.height();
	screenWidth = screenGeometry.width();

	// Init game object with screen width/height and fullscreen mode
	game = new Game(screenWidth, screenHeight, true);

    // connect the multiplayer option
    connect(this, SIGNAL(setMultiplayer(bool)), game, SLOT(setMultiplayer(bool)));

    // --- Set up sound ---
    // connect all signals to their corresponding slots
    connect(this, SIGNAL(playBackgroundMusic()), Sound::getSoundInstance(this), SLOT(playBackgroundMusic()));
    connect(this, SIGNAL(stopBackgroundMusic()), Sound::getSoundInstance(this), SLOT(stopBackgroundMusic()));
    connect(this, SIGNAL(playButtonSound()), Sound::getSoundInstance(this), SLOT(playButtonSound()));
    connect(this, SIGNAL(playCarSound()), Sound::getSoundInstance(this), SLOT(playCarSound()));
    connect(this, SIGNAL(stopCarSound()), Sound::getSoundInstance(this), SLOT(stopCarSound()));

    connect(this, SIGNAL(setBackgroundMusicVolume(int)), Sound::getSoundInstance(this), SLOT(setBackgroundMusicVolume(int)));
    connect(this, SIGNAL(setCarSoundVolume(int)), Sound::getSoundInstance(this), SLOT(setCarSoundVolume(int)));
    connect(this, SIGNAL(setButtonSoundVolume(int)), Sound::getSoundInstance(this), SLOT(setButtonSoundVolume(int)));

    // set up sound volume from stored values and start background music
    on_settingsButtonSoundSlider_valueChanged(buttonSoundValue);
    on_settingsRaceSoundSlider_valueChanged(raceSoundValue);
    on_settingsBackgroundSoundSlider_valueChanged(backgroundSoundValue);

    emit playBackgroundMusic();

// Set und start playing Backgroundmusic
//	playlist = new QMediaPlaylist();
	//playlist->addMedia(QUrl("qrc:/sounds/sounds/backgroundmusic.wav"));
//	playlist->addMedia(QUrl("qrc:/sounds/sounds/intense-bg-music.wav")); //source: https://www.royaltyfreemusicforfree.com/free-background-music/intense-background-music
//	playlist->setPlaybackMode(QMediaPlaylist::Loop);

//	backgroundmusic = new QMediaPlayer();
//	backgroundmusic->setPlaylist(playlist);
//	backgroundmusic->setVolume(backgroundSoundValue);
//	backgroundmusic->play();
//    setbackgroundsound();

	// Set Buttonsound
//    buttonsound = new QMediaPlayer();
//    buttonsound->setMedia(QUrl("qrc:/sounds/sounds/buttonsound.wav"));
//    buttonsound->setVolume(buttonSoundValue);

	// Set Pixmaps
	QPixmap logo(":/images/images/Logo.png");
	QPixmap hockenheim(":/images/images/Hockenheimtextur.png");
	QPixmap monza(":/images/images/Monzatextur.png") ;
	QPixmap yasmarina(":/images/images/YasMarinatextur.png");
    QPixmap bahrain(":/images/images/Bahraintextur.png");

	logo = logo.scaledToHeight(0.2 * screenHeight);
    hockenheim = hockenheim.scaled(QSize(0.5 * screenWidth, 0.5 * screenHeight),Qt::IgnoreAspectRatio);
    monza = monza.scaled(QSize(0.5 * screenWidth, 0.5 * screenHeight),Qt::IgnoreAspectRatio);
    yasmarina = yasmarina.scaled(QSize(0.5 * screenWidth, 0.5 * screenHeight),Qt::IgnoreAspectRatio);
    bahrain = bahrain.scaled(QSize(0.5 * screenWidth, 0.5 * screenHeight),Qt::IgnoreAspectRatio);

	// Set Icons
	QIcon leftArrow(":/images/images/l-arrow-576725_1280.png");
	QIcon rightArrow(":/images/images/r-arrow-576725_1280.png");
	QIcon menu(":/images/images/menu.png");
	QIcon play(":/images/images/play.png");
	QIcon garage(":/images/images/garage.png");
	QIcon highscore(":/images/images/highscore.png");
	QIcon settings(":/images/images/settings.png");
	QIcon manual(":/images/images/manual.png");
	QIcon credits(":/images/images/credits.png");
	QIcon quit(":/images/images/quit.png");
	QIcon reset(":/images/images/reset.png");
	QIcon soundOn(":/images/images/soundOn.png");
	QIcon soundOff(":/images/images/soundOff.png");
    QIcon singlePlayer(":/images/images/singleplayer.png");
    QIcon multiPlayer(":/images/images/multiplayer.png");

	// Set Icon Sizes
    QSize bigButton(0.4 * screenHeight, 0.2 * screenHeight);
    QSize normalButton(0.2 * screenHeight,0.1 * screenHeight);
	QSize smallButton(0.15 * screenHeight, 0.075 * screenHeight);
	QSize arrowButton(0.125 * screenHeight, 0.1 * screenHeight);

	// Set Spacer Sizes for centering (same size as smallButton)
	ui->garageHorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
	ui->highscoreHorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
	ui->settingsHorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
	ui->manualHorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
	ui->creditsHorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
    ui->playTypeSelectHorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
    ui->level1HorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
    ui->level2HorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
    ui->level3HorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
    ui->level4HorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);

	// Set Fonts
	GillSansMT.setFamily("GillSansMT");
	GillSansMT.setPointSize(20);
	GillSansMT.setBold(1);

	QFont GillSansMTTitle;
	GillSansMTTitle = GillSansMT;
	GillSansMTTitle.setPointSize(30);

    // Backgrounds for all

	QPixmap bkgnd(":/images/images/palmtree1_3840_2160.jpg");
	bkgnd = bkgnd.scaled(QSize(screenWidth,screenHeight), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);
	this->setAutoFillBackground(true);

	QPixmap bkgnd2(":/images/images/GaragehellGross.jpg");
	bkgnd2 = bkgnd2.scaled(QSize(screenWidth,screenHeight), Qt::IgnoreAspectRatio);
	QPalette palette2;
	palette2.setBrush(QPalette::Background, bkgnd2);
	ui->garage->setPalette(palette2);
	ui->garage->setAutoFillBackground(true);

    QPixmap bkgnd3(":/images/images/highscorebackground.png");
    bkgnd3 = bkgnd3.scaled(QSize(screenWidth,screenHeight), Qt::IgnoreAspectRatio);
    QPalette palette3;
    palette3.setBrush(QPalette::Background, bkgnd3);
    ui->highscore->setPalette(palette3);
    ui->highscore->setAutoFillBackground(true);

    QPixmap bkgnd4(":/images/images/settingsbackground.png");
    bkgnd4 = bkgnd4.scaled(QSize(screenWidth,screenHeight), Qt::IgnoreAspectRatio);
    QPalette palette4;
    palette4.setBrush(QPalette::Background, bkgnd4);
    ui->settings->setPalette(palette4);
    ui->settings->setAutoFillBackground(true);

    QPixmap bkgnd5(":/images/images/creditsbackground.png");
    bkgnd5 = bkgnd5.scaled(QSize(screenWidth,screenHeight), Qt::IgnoreAspectRatio);
    QPalette palette5;
    palette5.setBrush(QPalette::Background, bkgnd5);
    ui->credits->setPalette(palette5);
    ui->credits->setAutoFillBackground(true);

    QPixmap bkgnd6(":/images/images/manualbackground.png");
    bkgnd6 = bkgnd6.scaled(QSize(screenWidth,screenHeight), Qt::IgnoreAspectRatio);
    QPalette palette6;
    palette6.setBrush(QPalette::Background, bkgnd6);
    ui->manual->setPalette(palette6);
    ui->manual->setAutoFillBackground(true);

	// Items in Menu
	ui->mainLogo->setPixmap(logo);
	ui->mainLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->mainLogo->setStyleSheet("QLabel{background: transparent;}");
	ui->main2Level1->setIcon(play);
    ui->main2Level1->setIconSize(normalButton);
	ui->main2Level1->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2Garage->setIcon(garage);
    ui->main2Garage->setIconSize(normalButton);
	ui->main2Garage->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2Highscore->setIcon(highscore);
    ui->main2Highscore->setIconSize(normalButton);
	ui->main2Highscore->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2Settings->setIcon(settings);
    ui->main2Settings->setIconSize(normalButton);
	ui->main2Settings->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2Manual->setIcon(manual);
    ui->main2Manual->setIconSize(normalButton);
	ui->main2Manual->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2Credits->setIcon(credits);
    ui->main2Credits->setIconSize(normalButton);
	ui->main2Credits->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2QuitGame->setIcon(quit);
    ui->main2QuitGame->setIconSize(normalButton);
	ui->main2QuitGame->setStyleSheet("QPushButton{background: transparent;}");

	// Items in garage
	ui->garageLogo->setPixmap(logo);
	ui->garageLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->garageLogo->setStyleSheet("QLabel{background: transparent;}");
	ui->garage2Main->setIcon(menu);
	ui->garage2Main->setIconSize(smallButton);
	ui->garage2Main->setStyleSheet("QPushButton{background: transparent;}");
	ui->garageTitle->setStyleSheet("QLabel{background: transparent;}");
	ui->garageTitle->setText("Garage");
	ui->garageTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->garageTitle->setFont(GillSansMTTitle);
	ui->garageTopspeedSlider->setStyleSheet("QSlider{background: transparent;}");
    ui->garageTopspeedSlider->setValue(topspeedValue);
	ui->garageAccelerationSlider->setStyleSheet("QSlider{background: transparent;}");
    ui->garageAccelerationSlider->setValue(accelerationValue);
    ui->garageHandlingSlider->setStyleSheet("QSlider{background: transparent;}");
    ui->garageHandlingSlider->setValue(handlingValue);
    ui->garageTopspeedLabel->setStyleSheet("QLabel{background: transparent;}");
	ui->garageTopspeedLabel->setText("Your topspeed value: " + QString::number(topspeedValue));
	ui->garageTopspeedLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->garageTopspeedLabel->setFont(GillSansMT);
	ui->garageAccelerationLabel->setStyleSheet("QLabel{background: transparent;}");
	ui->garageAccelerationLabel->setText("Your acceleration value: " + QString::number(accelerationValue));
	ui->garageAccelerationLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->garageAccelerationLabel->setFont(GillSansMT);
	ui->garageHandlingLabel->setStyleSheet("QLabel{background: transparent;}");
	ui->garageHandlingLabel->setText("Your handling value: " + QString::number(handlingValue));
	ui->garageHandlingLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->garageHandlingLabel->setFont(GillSansMT);
	ui->garageLabel->setStyleSheet("QLabel{background: transparent;}");
	ui->garageLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->garageLabel->setFont(GillSansMT);

	// Items in highscore
	ui->highscoreLogo->setPixmap(logo);
	ui->highscoreLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->highscoreLogo->setStyleSheet("QLabel{background: transparent;}");
	ui->highscore2Main->setIcon(menu);
	ui->highscore2Main->setIconSize(smallButton);
	ui->highscore2Main->setStyleSheet("QPushButton{background: transparent;}");
	ui->highscoreTitle->setStyleSheet("QLabel{background: transparent;}");
	ui->highscoreTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->highscoreTitle->setFont(GillSansMTTitle);
	ui->highscoreTitle->setText("Highscore:");
    ui->highscoreLevel1->setStyleSheet("QLabel{background: transparent; color: black}");
	ui->highscoreLevel1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->highscoreLevel1->setFont(GillSansMT);
	ui->highscoreLevel1->setText("Sunny Speedway");
    ui->highscoreLevel2->setStyleSheet("QLabel{background: transparent; color: black}");
	ui->highscoreLevel2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->highscoreLevel2->setFont(GillSansMT);
	ui->highscoreLevel2->setText("Chancy Circuit");
    ui->highscoreLevel3->setStyleSheet("QLabel{background: transparent; color: black}");
	ui->highscoreLevel3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->highscoreLevel3->setFont(GillSansMT);
	ui->highscoreLevel3->setText("Deadly Desert");
	ui->highscoretablelevel1->setStyleSheet("QTableWidget{background: transparent;}");
	ui->highscoretablelevel2->setStyleSheet("QTableWidget{background: transparent;}");
	ui->highscoretablelevel3->setStyleSheet("QTableWidget{background: transparent;}");

	// Items in settings
	ui->settingsLogo->setPixmap(logo);
	ui->settingsLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->settingsLogo->setStyleSheet("QLabel{background: transparent;}");
	ui->settings2Main->setIcon(menu);
	ui->settings2Main->setIconSize(smallButton);
    ui->settings2Main->setStyleSheet("QPushButton{background: transparent; color: black}");
    ui->settingsBackgroundSoundLabel->setStyleSheet("QLabel{background: transparent; color: black}");
	ui->settingsBackgroundSoundLabel->setFont(GillSansMT);
	ui->settingsBackgroundSoundLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->settingsBackgroundSoundLabel->setText("Background Sound:");
    ui->settingsBackgroundSoundOn->setStyleSheet("QPushButton{background: transparent; color: black}");
	ui->settingsBackgroundSoundOn->setIcon(soundOn);
	ui->settingsBackgroundSoundOn->setIconSize(arrowButton);
    ui->settingsBackgroundSoundOff->setStyleSheet("QPushButton{background: transparent; color: black}");
	ui->settingsBackgroundSoundOff->setIcon(soundOff);
	ui->settingsBackgroundSoundOff->setIconSize(arrowButton);
	ui->settingsBackgroundSoundSlider->setStyleSheet("QSlider{background: transparent;}");
    ui->settingsButtonSoundLabel->setStyleSheet("QLabel{background: transparent; color: black}");
	ui->settingsButtonSoundLabel->setFont(GillSansMT);
	ui->settingsButtonSoundLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->settingsButtonSoundLabel->setText("Button Sound:");
    ui->settingsButtonSoundOn->setStyleSheet("QPushButton{background: transparent; color: black}");
	ui->settingsButtonSoundOn->setIcon(soundOn);
	ui->settingsButtonSoundOn->setIconSize(arrowButton);
    ui->settingsButtonSoundOff->setStyleSheet("QPushButton{background: transparent; color: black}");
	ui->settingsButtonSoundOff->setIcon(soundOff);
	ui->settingsButtonSoundOff->setIconSize(arrowButton);
	ui->settingsButtonSoundSlider->setStyleSheet("QSlider{background: transparent;}");
    ui->settingsRaceSoundLabel->setStyleSheet("QLabel{background: transparent; color: black}");
	ui->settingsRaceSoundLabel->setFont(GillSansMT);
	ui->settingsRaceSoundLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->settingsRaceSoundLabel->setText("Race Sound:");
    ui->settingsRaceSoundOn->setStyleSheet("QPushButton{background: transparent; color: black}");
	ui->settingsRaceSoundOn->setIcon(soundOn);
	ui->settingsRaceSoundOn->setIconSize(arrowButton);
    ui->settingsRaceSoundOff->setStyleSheet("QPushButton{background: transparent; color: black}");
	ui->settingsRaceSoundOff->setIcon(soundOff);
	ui->settingsRaceSoundOff->setIconSize(arrowButton);
	ui->settingsRaceSoundSlider->setStyleSheet("QSlider{background: transparent;}");
    ui->settingsHighscoreResetLabel->setStyleSheet("QLabel{background: transparent; color: black}");
	ui->settingsHighscoreResetLabel->setFont(GillSansMT);
	ui->settingsHighscoreResetLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->settingsHighscoreResetLabel->setText("Highscore Reset:");
    ui->settingsHighscoreResetButton->setStyleSheet("QPushButton{background: transparent; color: black}");
	ui->settingsHighscoreResetButton->setIcon(reset);
    ui->settingsHighscoreResetButton->setIconSize(normalButton);

	// Items in manual
	ui->manualLogo->setPixmap(logo);
	ui->manualLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->manualLogo->setStyleSheet("QLabel{background: transparent;}");
	ui->manual2Main->setIcon(menu);
	ui->manual2Main->setIconSize(smallButton);
	ui->manual2Main->setStyleSheet("QPushButton{background: transparent;}");
	ui->manualTitle->setStyleSheet("QLabel{background: transparent;}");
	ui->manualTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->manualTitle->setFont(GillSansMTTitle);
	ui->manualTitle->setText("Manual:");
    ui->manualLabel->setStyleSheet("QLabel{background: transparent; color: black}");
	ui->manualLabel->setFont(GillSansMT);
	ui->manualLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->manualLabel->setText("MOVING THE CAR:\n\n"
							 "UP = Accelerate\n"
							 "DOWN = Brake\n"
							 "LEFT/RIGHT = Steer\n"
							 "ESC = Back to main menu\n\n"
							 "You can adjust the attributes of the car in the garage.\n"
							 "The better your times on the tracks are, the more points you can distribute.\n"
							 "There is no possibility to take a shortcut - we know where you drive!\n");

	// Items in credits
	ui->creditsLogo->setPixmap(logo);
	ui->creditsLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->creditsLogo->setStyleSheet("QLabel{background: transparent;}");
	ui->credits2Main->setIcon(menu);
	ui->credits2Main->setIconSize(smallButton);
	ui->credits2Main->setStyleSheet("QPushButton{background: transparent;}");
	ui->creditsTitle->setStyleSheet("QLabel{background: transparent;}");
	ui->creditsTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->creditsTitle->setFont(GillSansMTTitle);
	ui->creditsTitle->setText("Credits:");
    ui->creditsLabel->setStyleSheet("QLabel{background: transparent; color: black}");
	ui->creditsLabel->setFont(GillSansMT);
	ui->creditsLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->creditsLabel->setText("DESIGNED AND PROGRAMMED BY:\n"
							  "Adrian Schiechel\n"
							  "Andreas Finkenzeller\n"
							  "Carina Vogl\n"
							  "Michael Maas\n"
							  "Johann Brenner\n\n"
							  "FOR:\n"
							  "Grundkurs C++, TUM\n\n"
							  "IN:\n"
							  "Summer Semester 2017\n\n");

    // Items in playTypeSelect
    ui->playTypeSelectLogo->setPixmap(logo);
    ui->playTypeSelectLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->playTypeSelectLogo->setStyleSheet("QLabel{background: transparent;}");
    ui->playTypeSelect2Main->setIcon(menu);
    ui->playTypeSelect2Main->setIconSize(smallButton);
    ui->playTypeSelect2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->playTypeSelect2SinglePlayer->setIcon(singlePlayer);
    ui->playTypeSelect2SinglePlayer->setIconSize(bigButton);
    ui->playTypeSelect2SinglePlayer->setStyleSheet("QPushButton{background: transparent;}");
    ui->playTypeSelect2Multiplayer->setIcon(multiPlayer);
    ui->playTypeSelect2Multiplayer->setIconSize(bigButton);
    ui->playTypeSelect2Multiplayer->setStyleSheet("QPushButton{background: transparent;}");
    ui->playTypeSelectTitle->setStyleSheet("QLabel{background: transparent;}");
    ui->playTypeSelectTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->playTypeSelectTitle->setFont(GillSansMTTitle);
    ui->playTypeSelectTitle->setText("Choose your playtype:");


    // Items in Level 1
    ui->level1Logo->setPixmap(logo);
    ui->level1Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level1Logo->setStyleSheet("QLabel{background: transparent;}");
    ui->level1_2Right->setIcon(rightArrow);
    ui->level1_2Right->setIconSize(arrowButton);
    ui->level1_2Right->setStyleSheet("QPushButton{background: transparent;}");
    ui->level1_2Left->setIcon(leftArrow);
    ui->level1_2Left->setIconSize(arrowButton);
    ui->level1_2Left->setStyleSheet("QPushButton{background: transparent;}");
    ui->level1_2Main->setIcon(menu);
    ui->level1_2Main->setIconSize(smallButton);
    ui->level1_2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->level1_2Play->setIcon(play);
    ui->level1_2Play->setIconSize(normalButton);
    ui->level1_2Play->setStyleSheet("QPushButton{background: transparent;}");
    ui->level1Trackname->setStyleSheet("QLabel{background: transparent;}");
    ui->level1Trackname->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level1Trackname->setFont(GillSansMTTitle);
    ui->level1Trackname->setText("Sunny Speedway");
    ui->level1Trackpic->setStyleSheet("QLabel{background: transparent; border: 5px solid black}");
    ui->level1Trackpic->setPixmap(monza);

    // Items in Level 2
    ui->level2Logo->setPixmap(logo);
    ui->level2Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level2Logo->setStyleSheet("QLabel{background: transparent;}");
    ui->level2_2Right->setIcon(rightArrow);
    ui->level2_2Right->setIconSize(arrowButton);
    ui->level2_2Right->setStyleSheet("QPushButton{background: transparent;}");
    ui->level2_2Left->setIcon(leftArrow);
    ui->level2_2Left->setIconSize(arrowButton);
    ui->level2_2Left->setStyleSheet("QPushButton{background: transparent;}");
    ui->level2_2Main->setIcon(menu);
    ui->level2_2Main->setIconSize(smallButton);
    ui->level2_2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->level2_2Play->setIcon(play);
    ui->level2_2Play->setIconSize(normalButton);
    ui->level2_2Play->setStyleSheet("QPushButton{background: transparent;}");
    ui->level2Trackname->setStyleSheet("QLabel{background: transparent;}");
    ui->level2Trackname->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level2Trackname->setFont(GillSansMTTitle);
    ui->level2Trackname->setText("Chancy Circuit");
    ui->level2Trackpic->setStyleSheet("QLabel{background: transparent; border: 5px solid black}");
    ui->level2Trackpic->setPixmap(hockenheim);

    // Items in Level 3
    ui->level3Logo->setPixmap(logo);
    ui->level3Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level3Logo->setStyleSheet("QLabel{background: transparent;}");
    ui->level3_2Right->setIcon(rightArrow);
    ui->level3_2Right->setIconSize(arrowButton);
    ui->level3_2Right->setStyleSheet("QPushButton{background: transparent;}");
    ui->level3_2Left->setIcon(leftArrow);
    ui->level3_2Left->setIconSize(arrowButton);
    ui->level3_2Left->setStyleSheet("QPushButton{background: transparent;}");
    ui->level3_2Main->setIcon(menu);
    ui->level3_2Main->setIconSize(smallButton);
    ui->level3_2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->level3_2Play->setIcon(play);
    ui->level3_2Play->setIconSize(normalButton);
    ui->level3_2Play->setStyleSheet("QPushButton{background: transparent;}");
    ui->level3Trackname->setStyleSheet("QLabel{background: transparent;}");
    ui->level3Trackname->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level3Trackname->setFont(GillSansMTTitle);
    ui->level3Trackname->setText("Deadly Desert");
    ui->level3Trackpic->setStyleSheet("QLabel{background: transparent; border: 5px solid black}");
    ui->level3Trackpic->setPixmap(yasmarina);

    // Items in Level 4
    ui->level4Logo->setPixmap(logo);
    ui->level4Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level4Logo->setStyleSheet("QLabel{background: transparent;}");
    ui->level4_2Right->setIcon(rightArrow);
    ui->level4_2Right->setIconSize(arrowButton);
    ui->level4_2Right->setStyleSheet("QPushButton{background: transparent;}");
    ui->level4_2Left->setIcon(leftArrow);
    ui->level4_2Left->setIconSize(arrowButton);
    ui->level4_2Left->setStyleSheet("QPushButton{background: transparent;}");
    ui->level4_2Main->setIcon(menu);
    ui->level4_2Main->setIconSize(smallButton);
    ui->level4_2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->level4_2Play->setIcon(play);
    ui->level4_2Play->setIconSize(normalButton);
    ui->level4_2Play->setStyleSheet("QPushButton{background: transparent;}");
    ui->level4Trackname->setStyleSheet("QLabel{background: transparent;}");
    ui->level4Trackname->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level4Trackname->setFont(GillSansMTTitle);
    ui->level4Trackname->setText("Breezy Bridges");
    ui->level4Trackpic->setStyleSheet("QLabel{background: transparent; border: 5px solid black}");
    ui->level4Trackpic->setPixmap(bahrain);
}

mainMenu::~mainMenu()
{
    delete game;
	delete ui;
}

// Setbackgroundsound
void mainMenu::setbackgroundsound()
{
    if(backgroundSoundActive==1)
	{
//		backgroundmusic->play();
        emit playBackgroundMusic();
	}
    else
    {
//        backgroundmusic->stop();
        emit stopBackgroundMusic();
    }
}


//  Sound for buttons
void mainMenu::playbuttonsound()
{
    if(buttonSoundActive==1)
    {
        //buttonsound->play();
        emit playButtonSound();
    }
    else
    {
        //buttonsound->stop();
    }
}

//  Buttons from the Main Menu UI

/*  pages:  0 - Main Menu
 *          1 - Garage
 *          2 - Highscore
 *          3 - Settings
 *          4 - Manual
 *          5 - Credits
 *          6 - PlayType Select
 *          7 - Level 1
 *          8 - Level 2
 *          9 - Level 3
 *
*/

// Buttons from the main menu
void mainMenu::on_main2Level1_clicked()
{
	playbuttonsound();
    ui->stackedWidget->setCurrentIndex(6);
}

void mainMenu::on_main2Garage_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(1);
    int decider = maximumValue - accelerationValue - topspeedValue - handlingValue;
    ui->garageLabel->setText("You have " + QString::number(decider) + " points left to distribute");
}

void mainMenu::on_main2Highscore_clicked()
{
	playbuttonsound();
    ui->stackedWidget->setCurrentIndex(2);

	ui->highscoretablelevel1->setFont(QFont("GillSansMT",15,17));
	ui->highscoretablelevel2->setFont(QFont("GillSansMT",15,17));
	ui->highscoretablelevel3->setFont(QFont("GillSansMT",15,17));

	QString filename;
	QString line;
	QStringList list;

	filename = "highscores/Monza.score";
	QFile inputFile(filename);
	if (inputFile.open(QIODevice::ReadOnly))
	{
		QTextStream in(&inputFile);
        int i = 0;
		while(!in.atEnd()){
			line = in.readLine();
			list = line.split(QRegExp("\\,"));
			mLevel1HighscoreMatrix[0][i] = list.at(0);
			mLevel1HighscoreMatrix[1][i] = list.at(1);
			i++;
		}
		for(int i = 0; i < 10;i++){
			mName = mLevel1HighscoreMatrix[0][i];
			mZeit = mLevel1HighscoreMatrix[1][i];
			ui->highscoretablelevel1->item(i,0)->setText(mName);
			ui->highscoretablelevel1->item(i,1)->setText(mZeit);
			ui->highscoretablelevel1->item(i,0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ui->highscoretablelevel1->item(i,1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ui->highscoretablelevel1->item(i,0)->setBackgroundColor(QColor(255,255,255,90));
			ui->highscoretablelevel1->item(i,1)->setBackgroundColor(QColor(255,255,255,90));
		}
		inputFile.close();
	}
	ui->highscoretablelevel1->setMaximumHeight(ui->highscoretablelevel1->height());
	ui->highscoretablelevel1->setMaximumWidth(ui->highscoretablelevel1->width());

	filename = "highscores/Hockenheimring.score";
	QFile inputFile2(filename);
	if (inputFile2.open(QIODevice::ReadOnly))
	{
		QTextStream in2(&inputFile2);
        int i = 0;
		while(!in2.atEnd()){
			line = in2.readLine();
			list = line.split(QRegExp("\\,"));
			mLevel2HighscoreMatrix[0][i] = list.at(0);
			mLevel2HighscoreMatrix[1][i] = list.at(1);
			i++;
		}
		for(int i = 0; i < 10;i++){
			mName = mLevel2HighscoreMatrix[0][i];
			mZeit = mLevel2HighscoreMatrix[1][i];
			ui->highscoretablelevel2->item(i,0)->setText(mName);
			ui->highscoretablelevel2->item(i,1)->setText(mZeit);
			ui->highscoretablelevel2->item(i,0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ui->highscoretablelevel2->item(i,1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ui->highscoretablelevel2->item(i,0)->setBackgroundColor(QColor(255,255,255,90));
			ui->highscoretablelevel2->item(i,1)->setBackgroundColor(QColor(255,255,255,90));
		}
		inputFile2.close();
	}
	ui->highscoretablelevel2->setMaximumHeight(ui->highscoretablelevel2->height());
	ui->highscoretablelevel2->setMaximumWidth(ui->highscoretablelevel2->width());

	filename = "highscores/YasMarina.score";
	QFile inputFile3(filename);
	if (inputFile3.open(QIODevice::ReadOnly))
	{
		QTextStream in3(&inputFile3);
        int i = 0;
		while(!in3.atEnd()){
			line = in3.readLine();
			list = line.split(QRegExp("\\,"));
			mLevel3HighscoreMatrix[0][i] = list.at(0);
			mLevel3HighscoreMatrix[1][i] = list.at(1);
			i++;
		}
		for(int i = 0; i < 10;i++){
			mName = mLevel3HighscoreMatrix[0][i];
			mZeit = mLevel3HighscoreMatrix[1][i];
			ui->highscoretablelevel3->item(i,0)->setText(mName);
			ui->highscoretablelevel3->item(i,1)->setText(mZeit);
			ui->highscoretablelevel3->item(i,0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ui->highscoretablelevel3->item(i,1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			ui->highscoretablelevel3->item(i,0)->setBackgroundColor(QColor(255,255,255,90));
			ui->highscoretablelevel3->item(i,1)->setBackgroundColor(QColor(255,255,255,90));
		}
		inputFile3.close();
	}
	ui->highscoretablelevel3->setMaximumHeight(ui->highscoretablelevel3->height());
	ui->highscoretablelevel3->setMaximumWidth(ui->highscoretablelevel3->width());
}

void mainMenu::on_main2Settings_clicked()
{
	playbuttonsound();
    ui->stackedWidget->setCurrentIndex(3);
    if(backgroundSoundActive == 1)
    {
        ui->settingsBackgroundSoundSlider->setValue(backgroundSoundValue);
    }
    if(buttonSoundActive == 1)
    {
        ui->settingsButtonSoundSlider->setValue(buttonSoundValue);
    }
    if(raceSoundActive == 1)
    {
        ui->settingsRaceSoundSlider->setValue(raceSoundValue);
    }

}

void mainMenu::on_main2Manual_clicked()
{
	playbuttonsound();
    ui->stackedWidget->setCurrentIndex(4);
}

void mainMenu::on_main2Credits_clicked()
{
	playbuttonsound();
    ui->stackedWidget->setCurrentIndex(5);
}

void mainMenu::on_main2QuitGame_clicked()
{
	playbuttonsound();
	QCoreApplication::quit();
}

// Buttons and Sliders from Garage

void mainMenu::on_garage2Main_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(0);

    QString out("topspeedValue=" + QString::number(topspeedValue) + "\n"
                "accelerationValue=" + QString::number(accelerationValue) + "\n"
                "handlingValue=" + QString::number(handlingValue) + "\n");
    QString filename;
    filename = "settings/garage.set";
    QFile outputFile(filename);
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate| QIODevice::Text)){
        QTextStream in(&outputFile);
        in << out;
        outputFile.close();
    }
}

void mainMenu::on_garageAccelerationSlider_valueChanged(int value)
{
    accelerationValue = value;

    int decider = maximumValue - accelerationValue - topspeedValue - handlingValue;

    ui->garageAccelerationLabel->setText("Your acceleration value: " + QString::number(accelerationValue));

    if(decider < 0){
        ui->garageLabel->setText("You have 0 points left to distribute");
    }
    else{
        ui->garageLabel->setText("You have " + QString::number(decider) + " points left to distribute");
    }
}

void mainMenu::on_garageAccelerationSlider_sliderReleased()
{
    int decider =  0;
    int setvalue = 0;
    decider = maximumValue - topspeedValue - accelerationValue - handlingValue;
    setvalue = maximumValue - topspeedValue - handlingValue;

    if(decider < 0){
        ui->garageAccelerationSlider->setValue(setvalue);
    }
}

void mainMenu::on_garageTopspeedSlider_valueChanged(int value)
{
    topspeedValue = value;

    int decider = maximumValue - accelerationValue - topspeedValue - handlingValue;

    ui->garageTopspeedLabel->setText("Your topspeed value: " + QString::number(topspeedValue));

    if(decider < 0){
        ui->garageLabel->setText("You have 0 points left to distribute");
    }
    else{
        ui->garageLabel->setText("You have " + QString::number(decider) + " points left to distribute");
    }}

void mainMenu::on_garageTopspeedSlider_sliderReleased()
{
    int decider =  0;
    int setvalue = 0;
    decider = maximumValue - topspeedValue - accelerationValue - handlingValue;
    setvalue = maximumValue - accelerationValue - handlingValue;

    if(decider < 0){
        ui->garageTopspeedSlider->setValue(setvalue);
    }
}

void mainMenu::on_garageHandlingSlider_valueChanged(int value)
{
    handlingValue = value;

    int decider = maximumValue - accelerationValue - topspeedValue - handlingValue;

    ui->garageHandlingLabel->setText("Your handling value: " + QString::number(handlingValue));

    if(decider < 0){
        ui->garageLabel->setText("You have 0 points left to distribute");
    }
    else{
        ui->garageLabel->setText("You have " + QString::number(decider) + " points left to distribute");
    }
}

void mainMenu::on_garageHandlingSlider_sliderReleased()
{
    int decider =  0;
    int setvalue = 0;
    decider = maximumValue - topspeedValue - accelerationValue - handlingValue;
    setvalue = maximumValue - accelerationValue - topspeedValue;

    if(decider < 0){
        ui->garageHandlingSlider->setValue(setvalue);
    }
}

// Garage end

// Buttons from Highscore

void mainMenu::on_highscore2Main_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(0);
}

/* Settings Configeration
 *
 * Buttons from Settings
 *
 * Sound Configeration and Highscore Reset directly behind
 *
*/

void mainMenu::on_settings2Main_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(0);

    QString out("backgroundSoundValue=" + QString::number(backgroundSoundValue) + "\n"
                "backgroundSoundActive=" + QString::number(backgroundSoundActive) + "\n"
                "buttonSoundValue=" + QString::number(buttonSoundValue) + "\n"
                "buttonSoundActive=" + QString::number(buttonSoundActive) + "\n"
                "raceSoundValue=" + QString::number(raceSoundValue) + "\n"
                "raceSoundActive=" + QString::number(raceSoundActive) + "\n");

    QString filename;
    filename = "settings/sound.set";
    QFile outputFile2(filename);
    if (outputFile2.open(QIODevice::WriteOnly | QIODevice::Truncate| QIODevice::Text)){
        QTextStream in2(&outputFile2);
        in2 << out;
        outputFile2.close();
    }
}

// Sound Configeration

void mainMenu::on_settingsBackgroundSoundOn_clicked()
{
    playbuttonsound();
    backgroundSoundActive = 1;
    //setbackgroundsound();
    emit setBackgroundMusicVolume(backgroundSoundValue);
    //emit playBackgroundMusic();
//	backgroundmusic->setVolume(backgroundSoundValue);
    ui->settingsBackgroundSoundSlider->setValue(backgroundSoundValue);
}

void mainMenu::on_settingsBackgroundSoundOff_clicked()
{
    int saver;
    playbuttonsound();
    //setbackgroundsound();
    saver = ui->settingsBackgroundSoundSlider->value();
    ui->settingsBackgroundSoundSlider->setValue(0);
    backgroundSoundValue = saver;
    backgroundSoundActive = 0;
    emit setBackgroundMusicVolume(0);
    //emit stopBackgroundMusic();
}

void mainMenu::on_settingsBackgroundSoundSlider_valueChanged(int value)
{
    if(backgroundSoundActive == 0){
        backgroundSoundActive = 1;
        //setbackgroundsound();
    }
    backgroundSoundValue = value;
    emit setBackgroundMusicVolume(backgroundSoundValue);
    //backgroundmusic->setVolume(backgroundSoundValue);
}
void mainMenu::on_settingsButtonSoundOn_clicked()
{
    playbuttonsound();
    buttonSoundActive = 1;
    emit setButtonSoundVolume(buttonSoundValue);
    //buttonsound->setVolume(buttonSoundValue);
    ui->settingsButtonSoundSlider->setValue(buttonSoundValue);
}

void mainMenu::on_settingsButtonSoundOff_clicked()
{
    int saver;
    playbuttonsound();
    saver = ui->settingsButtonSoundSlider->value();
    ui->settingsButtonSoundSlider->setValue(0);
    emit setButtonSoundVolume(0);
    buttonSoundValue = saver;
    buttonSoundActive = 0;
}

void mainMenu::on_settingsButtonSoundSlider_valueChanged(int value)
{
    if(buttonSoundActive == 0){
        buttonSoundActive = 1;
    }
    buttonSoundValue = value;
    emit setButtonSoundVolume(buttonSoundValue);
    //buttonsound->setVolume(buttonSoundValue);
}

void mainMenu::on_settingsRaceSoundOn_clicked()
{
    playbuttonsound();
    raceSoundActive = 1;
    ui->settingsRaceSoundSlider->setValue(raceSoundValue);
    emit setCarSoundVolume(raceSoundValue);
}

void mainMenu::on_settingsRaceSoundOff_clicked()
{
    int saver;
    playbuttonsound();
    saver = ui->settingsRaceSoundSlider->value();
    ui->settingsRaceSoundSlider->setValue(0);
    emit setCarSoundVolume(0);
    raceSoundValue = saver;
    raceSoundActive = 0;
}

void mainMenu::on_settingsRaceSoundSlider_valueChanged(int value)
{
    //racesound lauter/leiser
    if(raceSoundActive == 0){
        raceSoundActive = 1;
    }
    raceSoundValue = value;
    emit setCarSoundVolume(raceSoundValue);
}

// Highscore Reset

void mainMenu::on_settingsHighscoreResetButton_clicked()
{
    playbuttonsound();
    //resetHighscore

    QString filename;
    filename = "highscores/Monza.score";
    QFile outputFile(filename);
    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate| QIODevice::Text)){
        QTextStream in(&outputFile);
        for(int i = 0; i < 10; i++)	in << "-,-\n";
        outputFile.close();
    }

    filename = "highscores/Hockenheimring.score";
    QFile outputFile2(filename);
    if (outputFile2.open(QIODevice::WriteOnly | QIODevice::Truncate| QIODevice::Text)){
        QTextStream in2(&outputFile2);
        for(int i = 0; i < 10; i++)	in2 << "-,-\n";
        outputFile2.close();
    }

    filename = "highscores/YasMarina.score";
    QFile outputFile3(filename);
    if (outputFile3.open(QIODevice::WriteOnly | QIODevice::Truncate| QIODevice::Text)){
        QTextStream in3(&outputFile3);
        for(int i = 0; i < 10; i++)	in3 << "-,-\n";
        outputFile3.close();
    }
}

// Buttons from Manual

void mainMenu::on_manual2Main_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Credits

void mainMenu::on_credits2Main_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from playTypeSelect

void mainMenu::on_playTypeSelect2SinglePlayer_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(7);
    emit setMultiplayer(false);
}

void mainMenu::on_playTypeSelect2Multiplayer_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(7);
    emit setMultiplayer(true);
}

void mainMenu::on_playTypeSelect2Main_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Level 1

void mainMenu::on_level1_2Left_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->count() - 1); // Left is last Level
}

void mainMenu::on_level1_2Right_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void mainMenu::on_level1_2Main_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level1_2Play_clicked()
{
	playbuttonsound();
	//start Level 1
	//world = new World(screenWidth,screenHeight,1);
	//world->showFullScreen();
	//hide();
    game->loadCircuit(Monza, topspeedValue, accelerationValue, handlingValue);
}

// Buttons from Level 2

void mainMenu::on_level2_2Main_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level2_2Left_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void mainMenu::on_level2_2Right_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void mainMenu::on_level2_2Play_clicked()
{
	playbuttonsound();
	//start Level 2
	//world = new World(screenWidth,screenHeight,2);
	//world->showFullScreen();
	//hide();
    game->loadCircuit(Hockenheimring, topspeedValue, accelerationValue, handlingValue);
}

// Buttons from Level 3

void mainMenu::on_level3_2Main_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level3_2Left_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void mainMenu::on_level3_2Right_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
}

void mainMenu::on_level3_2Play_clicked()
{
	playbuttonsound();
	//start Level 3
	//world = new World(screenWidth,screenHeight,3);
	//world->showFullScreen();
	//hide();
    game->loadCircuit(YasMarina, topspeedValue, accelerationValue, handlingValue);
}

void mainMenu::on_level4_2Main_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level4_2Left_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
}

void mainMenu::on_level4_2Right_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(7);    // Page 7 is Level 1
}

void mainMenu::on_level4_2Play_clicked()
{
    playbuttonsound();
    // start level 4
    game->loadCircuit(Bahrain, topspeedValue, accelerationValue, handlingValue);
}
