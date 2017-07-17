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
    QFile inputFile1(filename);
    if (inputFile1.open(QIODevice::ReadOnly))
    {
        QTextStream in1(&inputFile1);
        QString line;
        QStringList list;

        while(!in1.atEnd())
        {
            line = in1.readLine();
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
        inputFile1.close();
    }

    filename = "settings/sound.set";
    QFile inputFile2(filename);
    if (inputFile2.open(QIODevice::ReadOnly))
    {
        QTextStream in2(&inputFile2);
        QString line;
        QStringList list;

        while(!in2.atEnd())
        {
            line = in2.readLine();
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
        inputFile2.close();
    }

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
    QPixmap silverstone(":/images/images/Silverstonetextur.png");
    QPixmap starYellow(":/images/images/star-yellow.png");
    QPixmap starDark(":/images/images/star-dark.png");

	logo = logo.scaledToHeight(0.2 * screenHeight);
    hockenheim = hockenheim.scaled(QSize(0.5 * screenWidth, 0.5 * screenHeight),Qt::IgnoreAspectRatio);
    monza = monza.scaled(QSize(0.5 * screenWidth, 0.5 * screenHeight),Qt::IgnoreAspectRatio);
    yasmarina = yasmarina.scaled(QSize(0.5 * screenWidth, 0.5 * screenHeight),Qt::IgnoreAspectRatio);
    bahrain = bahrain.scaled(QSize(0.5 * screenWidth, 0.5 * screenHeight),Qt::IgnoreAspectRatio);
    silverstone = silverstone.scaled(QSize(0.5 * screenWidth, 0.5 * screenHeight),Qt::IgnoreAspectRatio);
    starYellow = starYellow.scaled(QSize(screenHeight * 0.1, screenHeight * 0.1),Qt::IgnoreAspectRatio);
    starDark = starDark.scaled(QSize(screenHeight * 0.1, screenHeight * 0.1),Qt::IgnoreAspectRatio);

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
    ui->level5HorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);

    // Set Fonts
	GillSansMT.setFamily("GillSansMT");
    GillSansMT.setPointSize(screenHeight * 0.02);
	GillSansMT.setBold(1);

	QFont GillSansMTTitle;
	GillSansMTTitle = GillSansMT;
    GillSansMTTitle.setPointSize(screenHeight * 0.03);

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
    ui->highscore2Left->setIcon(leftArrow);
    ui->highscore2Left->setIconSize(arrowButton);
    ui->highscore2Left->setStyleSheet("QPushButton{background: transparent;}");
    ui->highscore2Right->setIcon(rightArrow);
    ui->highscore2Right->setIconSize(arrowButton);
    ui->highscore2Right->setStyleSheet("QPushButton{background: transparent;}");
	ui->highscoreTitle->setStyleSheet("QLabel{background: transparent;}");
	ui->highscoreTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->highscoreTitle->setFont(GillSansMTTitle);
	ui->highscoreTitle->setText("Highscore:");
    ui->highscoreLevelTitle->setStyleSheet("QLabel{background: transparent; color: black}");
    ui->highscoreLevelTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->highscoreLevelTitle->setFont(GillSansMT);
    ui->highscoreTable->setStyleSheet("QTableWidget{background: transparent;}");

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
    ui->level1Star1->setStyleSheet("QLabel{background: transparent;}");
    ui->level1Star1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level1Star1->setPixmap(starDark);
    ui->level1Star2->setStyleSheet("QLabel{background: transparent;}");
    ui->level1Star2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level1Star2->setPixmap(starDark);
    ui->level1Star3->setStyleSheet("QLabel{background: transparent;}");
    ui->level1Star3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level1Star3->setPixmap(starDark);

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
    ui->level2Star1->setStyleSheet("QLabel{background: transparent;}");
    ui->level2Star1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level2Star1->setPixmap(starDark);
    ui->level2Star2->setStyleSheet("QLabel{background: transparent;}");
    ui->level2Star2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level2Star2->setPixmap(starDark);
    ui->level2Star3->setStyleSheet("QLabel{background: transparent;}");
    ui->level2Star3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level2Star3->setPixmap(starDark);

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
    ui->level3Star1->setStyleSheet("QLabel{background: transparent;}");
    ui->level3Star1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level3Star1->setPixmap(starDark);
    ui->level3Star2->setStyleSheet("QLabel{background: transparent;}");
    ui->level3Star2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level3Star2->setPixmap(starDark);
    ui->level3Star3->setStyleSheet("QLabel{background: transparent;}");
    ui->level3Star3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level3Star3->setPixmap(starDark);

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
    ui->level4Star1->setStyleSheet("QLabel{background: transparent;}");
    ui->level4Star1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level4Star1->setPixmap(starDark);
    ui->level4Star2->setStyleSheet("QLabel{background: transparent;}");
    ui->level4Star2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level4Star2->setPixmap(starDark);
    ui->level4Star3->setStyleSheet("QLabel{background: transparent;}");
    ui->level4Star3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level4Star3->setPixmap(starDark);

    // Items in Level 5
    ui->level5Logo->setPixmap(logo);
    ui->level5Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level5Logo->setStyleSheet("QLabel{background: transparent;}");
    ui->level5_2Right->setIcon(rightArrow);
    ui->level5_2Right->setIconSize(arrowButton);
    ui->level5_2Right->setStyleSheet("QPushButton{background: transparent;}");
    ui->level5_2Left->setIcon(leftArrow);
    ui->level5_2Left->setIconSize(arrowButton);
    ui->level5_2Left->setStyleSheet("QPushButton{background: transparent;}");
    ui->level5_2Main->setIcon(menu);
    ui->level5_2Main->setIconSize(smallButton);
    ui->level5_2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->level5_2Play->setIcon(play);
    ui->level5_2Play->setIconSize(normalButton);
    ui->level5_2Play->setStyleSheet("QPushButton{background: transparent;}");
    ui->level5Trackname->setStyleSheet("QLabel{background: transparent;}");
    ui->level5Trackname->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level5Trackname->setFont(GillSansMTTitle);
    ui->level5Trackname->setText("Rapid Randomness");
    ui->level5Trackpic->setStyleSheet("QLabel{background: transparent; border: 5px solid black}");
    ui->level5Trackpic->setPixmap(silverstone);
    ui->level5Star1->setStyleSheet("QLabel{background: transparent;}");
    ui->level5Star1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level5Star1->setPixmap(starDark);
    ui->level5Star2->setStyleSheet("QLabel{background: transparent;}");
    ui->level5Star2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level5Star2->setPixmap(starDark);
    ui->level5Star3->setStyleSheet("QLabel{background: transparent;}");
    ui->level5Star3->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level5Star3->setPixmap(starDark);
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
 *         10 - Level 4
 *         11 - Level 5
*/

// Buttons from the main menu
void mainMenu::on_main2Level1_clicked()
{
	playbuttonsound();
    ui->stackedWidget->setCurrentIndex(6);
    computeMaximumValue();
    setStars();
}

void mainMenu::on_main2Garage_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(1);
    computeMaximumValue();
    int decider = maximumValue - accelerationValue - topspeedValue - handlingValue;
    ui->garageLabel->setText("You have " + QString::number(decider) + " points left to distribute");
}

void mainMenu::on_main2Highscore_clicked()
{
	playbuttonsound();
    ui->stackedWidget->setCurrentIndex(2);
    insertHighscoreToTable();
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

// Get the number of points which can be distributed from the Highscores
void mainMenu::computeMaximumValue()
{
    QString filename;
    QString lineAll;
    QString lineTime;
    QStringList list;
    int min = 0;
    double sec = 0;

    monzaValue = 0;
    hockenheimringValue = 0;
    yasmarinaValue = 0;
    bahrainValue = 0;
    silverstoneValue=0;

    // get the MonzaValue
    filename = "highscores/Monza.score";
    QFile inputFile1(filename);
    if (inputFile1.open(QIODevice::ReadOnly))
    {
        QTextStream in1(&inputFile1);
        lineAll = in1.readLine();
        list = lineAll.split(QRegExp("\\,"));
        lineTime = list.at(1);
        list = lineTime.split(QRegExp("\\:"));
        min = list.value(0).toInt();
        sec = list.value(1).toDouble();
        inputFile1.close();
    }
    if(min < 3)
    {
        monzaValue = 1;
    }
    if(min < 3 && sec < 30)
    {
        monzaValue = 2;
    }
    if(min < 2)
    {
        monzaValue = 3;
    }
    if(min == 0 && sec == 0)
    {
        monzaValue = 0;
    }

    // get the HockenheimringValue
    filename = "highscores/Hockenheimring.score";
    QFile inputFile2(filename);
    if (inputFile2.open(QIODevice::ReadOnly))
    {
        QTextStream in2(&inputFile2);
        lineAll = in2.readLine();
        list = lineAll.split(QRegExp("\\,"));
        lineTime = list.at(1);
        list = lineTime.split(QRegExp("\\:"));
        min = list.value(0).toInt();
        sec = list.value(1).toDouble();
        inputFile2.close();
    }
    if(min < 3 && sec < 30)
    {
        hockenheimringValue = 1;
    }
    if(min < 2)
    {
        hockenheimringValue = 2;
    }
    if((min < 2 && sec < 30) || min < 1)
    {
        hockenheimringValue = 3;
    }
    if(min == 0 && sec == 0)
    {
        hockenheimringValue = 0;
    }

    // get the YasMarinaValue
    filename = "highscores/YasMarina.score";
    QFile inputFile3(filename);
    if (inputFile3.open(QIODevice::ReadOnly))
    {
        QTextStream in3(&inputFile3);
        lineAll = in3.readLine();
        list = lineAll.split(QRegExp("\\,"));
        lineTime = list.at(1);
        list = lineTime.split(QRegExp("\\:"));
        min = list.value(0).toInt();
        sec = list.value(1).toDouble();
        inputFile3.close();
    }
    if(min < 4)
    {
        yasmarinaValue = 1;
    }
    if(min < 3 && sec < 30)
    {
        yasmarinaValue = 2;
    }
    if(min < 3)
    {
        yasmarinaValue = 3;
    }
    if(min == 0 && sec == 0)
    {
        yasmarinaValue = 0;
    }

    // get the BahrainValue
    filename = "highscores/Bahrain.score";
    QFile inputFile4(filename);
    if (inputFile4.open(QIODevice::ReadOnly))
    {
        QTextStream in4(&inputFile4);
        lineAll = in4.readLine();
        list = lineAll.split(QRegExp("\\,"));
        lineTime = list.at(1);
        list = lineTime.split(QRegExp("\\:"));
        min = list.value(0).toInt();
        sec = list.value(1).toDouble();
        inputFile4.close();
    }
    if(min < 4)
    {
        bahrainValue = 1;
    }
    if(min < 4 && sec < 30)
    {
        bahrainValue = 2;
    }
    if(min < 3)
    {
        bahrainValue = 3;
    }
    if(min == 0 && sec == 0)
    {
        bahrainValue = 0;
    }

    // get the SilverstoneValue
    filename = "highscores/Silverstone.score";
    QFile inputFile5(filename);
    if (inputFile5.open(QIODevice::ReadOnly))
    {
        QTextStream in5(&inputFile5);
        lineAll = in5.readLine();
        list = lineAll.split(QRegExp("\\,"));
        lineTime = list.at(1);
        list = lineTime.split(QRegExp("\\:"));
        min = list.value(0).toInt();
        sec = list.value(1).toDouble();
        inputFile5.close();
    }
    if(min < 4)
    {
        silverstoneValue = 1;
    }
    if(min < 4 && sec < 30)
    {
        silverstoneValue = 2;
    }
    if(min < 3)
    {
        silverstoneValue = 3;
    }
    if(min == 0 && sec == 0)
    {
        silverstoneValue = 0;
    }

    maximumValue = minimumValue + monzaValue + hockenheimringValue + yasmarinaValue + bahrainValue + silverstoneValue;
}

// Set the correct amount of Stars in the Level Selector according to the values of the Highscores
void mainMenu::setStars()
{
    QPixmap starYellow(":/images/images/star-yellow.png");
    QPixmap starDark(":/images/images/star-dark.png");
    starYellow = starYellow.scaled(QSize(screenHeight * 0.1, screenHeight * 0.1),Qt::IgnoreAspectRatio);
    starDark = starDark.scaled(QSize(screenHeight * 0.1, screenHeight * 0.1),Qt::IgnoreAspectRatio);

    switch (monzaValue) {
    case 0:
        ui->level1Star1->setPixmap(starDark);
        ui->level1Star2->setPixmap(starDark);
        ui->level1Star3->setPixmap(starDark);
        break;
    case 1:
        ui->level1Star1->setPixmap(starYellow);
        ui->level1Star2->setPixmap(starDark);
        ui->level1Star3->setPixmap(starDark);
        break;
    case 2:
        ui->level1Star1->setPixmap(starYellow);
        ui->level1Star2->setPixmap(starYellow);
        ui->level1Star3->setPixmap(starDark);
        break;
    default:
        ui->level1Star1->setPixmap(starYellow);
        ui->level1Star2->setPixmap(starYellow);
        ui->level1Star3->setPixmap(starYellow);
        break;
    }
    switch (hockenheimringValue) {
    case 0:
        ui->level2Star1->setPixmap(starDark);
        ui->level2Star2->setPixmap(starDark);
        ui->level2Star3->setPixmap(starDark);
        break;
    case 1:
        ui->level2Star1->setPixmap(starYellow);
        ui->level2Star2->setPixmap(starDark);
        ui->level2Star3->setPixmap(starDark);
        break;
    case 2:
        ui->level2Star1->setPixmap(starYellow);
        ui->level2Star2->setPixmap(starYellow);
        ui->level2Star3->setPixmap(starDark);
        break;
    default:
        ui->level2Star1->setPixmap(starYellow);
        ui->level2Star2->setPixmap(starYellow);
        ui->level2Star3->setPixmap(starYellow);
        break;
    }
    switch (yasmarinaValue) {
    case 0:
        ui->level3Star1->setPixmap(starDark);
        ui->level3Star2->setPixmap(starDark);
        ui->level3Star3->setPixmap(starDark);
        break;
    case 1:
        ui->level3Star1->setPixmap(starYellow);
        ui->level3Star2->setPixmap(starDark);
        ui->level3Star3->setPixmap(starDark);
        break;
    case 2:
        ui->level3Star1->setPixmap(starYellow);
        ui->level3Star2->setPixmap(starYellow);
        ui->level3Star3->setPixmap(starDark);
        break;
    default:
        ui->level3Star1->setPixmap(starYellow);
        ui->level3Star2->setPixmap(starYellow);
        ui->level3Star3->setPixmap(starYellow);
        break;
    }
    switch (bahrainValue) {
    case 0:
        ui->level4Star1->setPixmap(starDark);
        ui->level4Star2->setPixmap(starDark);
        ui->level4Star3->setPixmap(starDark);
        break;
    case 1:
        ui->level4Star1->setPixmap(starYellow);
        ui->level4Star2->setPixmap(starDark);
        ui->level4Star3->setPixmap(starDark);
        break;
    case 2:
        ui->level4Star1->setPixmap(starYellow);
        ui->level4Star2->setPixmap(starYellow);
        ui->level4Star3->setPixmap(starDark);
        break;
    default:
        ui->level4Star1->setPixmap(starYellow);
        ui->level4Star2->setPixmap(starYellow);
        ui->level4Star3->setPixmap(starYellow);
        break;
    }
    switch (silverstoneValue) {
    case 0:
        ui->level5Star1->setPixmap(starDark);
        ui->level5Star2->setPixmap(starDark);
        ui->level5Star3->setPixmap(starDark);
        break;
    case 1:
        ui->level5Star1->setPixmap(starYellow);
        ui->level5Star2->setPixmap(starDark);
        ui->level5Star3->setPixmap(starDark);
        break;
    case 2:
        ui->level5Star1->setPixmap(starYellow);
        ui->level5Star2->setPixmap(starYellow);
        ui->level5Star3->setPixmap(starDark);
        break;
    default:
        ui->level5Star1->setPixmap(starYellow);
        ui->level5Star2->setPixmap(starYellow);
        ui->level5Star3->setPixmap(starYellow);
        break;
    }
}

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

// Buttons from Highscore

void mainMenu::on_highscore2Main_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_highscore2Right_clicked()
{
    playbuttonsound();
    if(highscoreTrackNumber < 4)
    {
        highscoreTrackNumber++;
    }
    else
    {
        highscoreTrackNumber = 0;
    }
    insertHighscoreToTable();
}

void mainMenu::on_highscore2Left_clicked()
{
    playbuttonsound();
    if(highscoreTrackNumber > 0)
    {
        highscoreTrackNumber++;
    }
    else
    {
        highscoreTrackNumber = 4;
    }
    insertHighscoreToTable();
}

void mainMenu::insertHighscoreToTable()
{
    ui->highscoreTable->setFont(QFont("GillSansMT",15,17));

    QString filename;
    QString line;
    QStringList list;

    switch (highscoreTrackNumber) {
    case 0:
        filename = "highscores/Monza.score";
        ui->highscoreLevelTitle->setText("Sunny Speedway");
        break;
    case 1:
        filename = "highscores/Hockenheimring.score";
        ui->highscoreLevelTitle->setText("Chancy Circuit");
        break;
    case 2:
        filename = "highscores/YasMarina.score";
        ui->highscoreLevelTitle->setText("Deadly Desert");
        break;
    case 3:
        filename = "highscores/Bahrain.score";
        ui->highscoreLevelTitle->setText("Breezy Bridges");
        break;
    case 4:
        filename = "highscores/Silverstone.score";
        ui->highscoreLevelTitle->setText("Rapid Randomness");
        break;
    default:
        break;
    }

    QFile inputFile(filename);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        int i = 0;
        while(!in.atEnd()){
            line = in.readLine();
            list = line.split(QRegExp("\\,"));
            mHighscoreMatrix[0][i] = list.at(0);
            mHighscoreMatrix[1][i] = list.at(1);
            mHighscoreMatrix[2][i] = list.at(2);
            mHighscoreMatrix[3][i] = list.at(3);
            mHighscoreMatrix[4][i] = list.at(4);
            i++;
        }
        for(int i = 0; i < 10;i++){
            mName = mHighscoreMatrix[0][i];
            mZeit = mHighscoreMatrix[1][i];
            mLap1 = mHighscoreMatrix[2][i];
            mLap2 = mHighscoreMatrix[3][i];
            mLap3 = mHighscoreMatrix[4][i];
            ui->highscoreTable->item(i,0)->setText(mName);
            ui->highscoreTable->item(i,1)->setText(mZeit);
            ui->highscoreTable->item(i,2)->setText(mLap1);
            ui->highscoreTable->item(i,3)->setText(mLap2);
            ui->highscoreTable->item(i,4)->setText(mLap3);
            ui->highscoreTable->item(i,0)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            ui->highscoreTable->item(i,1)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            ui->highscoreTable->item(i,2)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            ui->highscoreTable->item(i,3)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            ui->highscoreTable->item(i,4)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
            ui->highscoreTable->item(i,0)->setBackgroundColor(QColor(255,255,255,90));
            ui->highscoreTable->item(i,1)->setBackgroundColor(QColor(255,255,255,90));
            ui->highscoreTable->item(i,2)->setBackgroundColor(QColor(255,255,255,90));
            ui->highscoreTable->item(i,3)->setBackgroundColor(QColor(255,255,255,90));
            ui->highscoreTable->item(i,4)->setBackgroundColor(QColor(255,255,255,90));
        }
        inputFile.close();
    }
    ui->highscoreTable->setMaximumHeight(ui->highscoreTable->height());
    ui->highscoreTable->setMaximumWidth(ui->highscoreTable->width());
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
        for(int i = 0; i < 10; i++)	in << "-,-,-,-,-\n";
        outputFile.close();
    }

    filename = "highscores/Hockenheimring.score";
    QFile outputFile2(filename);
    if (outputFile2.open(QIODevice::WriteOnly | QIODevice::Truncate| QIODevice::Text)){
        QTextStream in2(&outputFile2);
        for(int i = 0; i < 10; i++)	in2 << "-,-,-,-,-\n";
        outputFile2.close();
    }

    filename = "highscores/YasMarina.score";
    QFile outputFile3(filename);
    if (outputFile3.open(QIODevice::WriteOnly | QIODevice::Truncate| QIODevice::Text)){
        QTextStream in3(&outputFile3);
        for(int i = 0; i < 10; i++)	in3 << "-,-,-,-,-\n";
        outputFile3.close();
    }

    filename = "highscores/Bahrain.score";
    QFile outputFile4(filename);
    if (outputFile4.open(QIODevice::WriteOnly | QIODevice::Truncate| QIODevice::Text)){
        QTextStream in4(&outputFile4);
        for(int i = 0; i < 10; i++)	in4 << "-,-,-,-,-\n";
        outputFile4.close();
    }

    filename = "highscores/Silverstone.score";
    QFile outputFile5(filename);
    if (outputFile5.open(QIODevice::WriteOnly | QIODevice::Truncate| QIODevice::Text)){
        QTextStream in5(&outputFile5);
        for(int i = 0; i < 10; i++)	in5 << "-,-,-,-,-\n";
        outputFile5.close();
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
    if((monzaValue + hockenheimringValue + yasmarinaValue + bahrainValue) < 8)
    {
        ui->level5_2Play->setEnabled(false);
    }
    else
    {
        ui->level5_2Play->setEnabled(true);
    }
}

void mainMenu::on_level1_2Right_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
    if((monzaValue) < 1)
    {
        ui->level2_2Play->setEnabled(false);
    }
    else
    {
        ui->level2_2Play->setEnabled(true);
    }
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
    if((monzaValue + hockenheimringValue) < 3)
    {
        ui->level3_2Play->setEnabled(false);
    }
    else
    {
        ui->level3_2Play->setEnabled(true);
    }
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
    if((monzaValue) < 1)
    {
        ui->level2_2Play->setEnabled(false);
    }
    else
    {
        ui->level2_2Play->setEnabled(true);
    }
}

void mainMenu::on_level3_2Right_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
    if((monzaValue + hockenheimringValue + yasmarinaValue) < 6)
    {
        ui->level4_2Play->setEnabled(false);
    }
    else
    {
        ui->level4_2Play->setEnabled(true);
    }
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

// Buttons from Level 4

void mainMenu::on_level4_2Main_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level4_2Left_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
    if((monzaValue + hockenheimringValue) < 3)
    {
        ui->level3_2Play->setEnabled(false);
    }
    else
    {
        ui->level3_2Play->setEnabled(true);
    }
}

void mainMenu::on_level4_2Right_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
    if((monzaValue + hockenheimringValue + yasmarinaValue + bahrainValue) < 8)
    {
        ui->level5_2Play->setEnabled(false);
    }
    else
    {
        ui->level5_2Play->setEnabled(true);
    }
}

void mainMenu::on_level4_2Play_clicked()
{
    playbuttonsound();
    // start level 4
    game->loadCircuit(Bahrain, topspeedValue, accelerationValue, handlingValue);
}

// Buttons from Level 5

void mainMenu::on_level5_2Main_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level5_2Left_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
    if((monzaValue + hockenheimringValue + yasmarinaValue) < 6)
    {
        ui->level4_2Play->setEnabled(false);
    }
    else
    {
        ui->level4_2Play->setEnabled(true);
    }
}

void mainMenu::on_level5_2Right_clicked()
{
    playbuttonsound();
    ui->stackedWidget->setCurrentIndex(7);    // Page 7 is Level 1
}

void mainMenu::on_level5_2Play_clicked()
{
    playbuttonsound();
    // start level 5
    game->loadCircuit(Silverstone, topspeedValue, accelerationValue, handlingValue);
}

