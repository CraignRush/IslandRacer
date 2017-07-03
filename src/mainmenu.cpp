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
	maximumValue = 10;
	accelerationValue = 0;
	handlingValue = 0;
	topspeedValue = 0;
	active=1;
	backgroundSoundValue = 50;
	buttonSoundValue = 100;
	raceSoundValue = 50;


	// Get Screensize
	QScreen *screen = QGuiApplication::primaryScreen();
	QRect  screenGeometry = screen->geometry();
	screenHeight = screenGeometry.height();
	screenWidth = screenGeometry.width();

	// Init game object with screen width/height and fullscreen mode
	game = new Game(screenWidth, screenHeight, true);

	// Set und start playing Backgroundmusic
//	playlist = new QMediaPlaylist();
	//playlist->addMedia(QUrl("qrc:/sounds/sounds/backgroundmusic.wav"));
//	playlist->addMedia(QUrl("qrc:/sounds/sounds/intense-bg-music.wav")); //source: https://www.royaltyfreemusicforfree.com/free-background-music/intense-background-music
//	playlist->setPlaybackMode(QMediaPlaylist::Loop);

//	backgroundmusic = new QMediaPlayer();
//	backgroundmusic->setPlaylist(playlist);
//	backgroundmusic->setVolume(backgroundSoundValue);
//	backgroundmusic->play();

	// Set Buttonsound
//    buttonsound = new QMediaPlayer();
//    buttonsound->setMedia(QUrl("qrc:/sounds/sounds/buttonsound.wav"));
//    buttonsound->setVolume(buttonSoundValue);

	// Set Pixmaps
	QPixmap logo(":/images/images/Logo.png");
	QPixmap hockenheim(":/images/images/Hockenheimtextur.png");
	QPixmap monza(":/images/images/Monzatextur.png") ;
	QPixmap yasmarina(":/images/images/YasMarinatextur.png");

	logo = logo.scaledToHeight(0.2 * screenHeight);
	hockenheim = hockenheim.scaledToHeight(0.5 * screenHeight);
	monza = monza.scaledToHeight(0.5 * screenHeight);
	yasmarina = yasmarina.scaledToHeight(0.5 * screenHeight);

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

	// Set Icon Sizes
	QSize bigButton(0.2 * screenHeight,0.1 * screenHeight);
	QSize smallButton(0.15 * screenHeight, 0.075 * screenHeight);
	QSize arrowButton(0.125 * screenHeight, 0.1 * screenHeight);

	// Set Spacer Sizes for centering (same size as smallButton)
	ui->level1HorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
	ui->level2HorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
	ui->level3HorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
	ui->garageHorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
	ui->highscoreHorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
	ui->settingsHorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
	ui->manualHorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);
	ui->creditsHorizontalSpacer->changeSize(0.15 * screenHeight,0.075 * screenHeight);

	// Set Fonts
	GillSansMT.setFamily("GillSansMT");
	GillSansMT.setPointSize(20);
	GillSansMT.setBold(1);

	QFont GillSansMTTitle;
	GillSansMTTitle = GillSansMT;
	GillSansMTTitle.setPointSize(30);

	// Items for all

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

	// Items in Menu
	ui->mainLogo->setPixmap(logo);
	ui->mainLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->mainLogo->setStyleSheet("QLabel{background: transparent;}");
	ui->main2Level1->setIcon(play);
	ui->main2Level1->setIconSize(bigButton);
	ui->main2Level1->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2Garage->setIcon(garage);
	ui->main2Garage->setIconSize(bigButton);
	ui->main2Garage->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2Highscore->setIcon(highscore);
	ui->main2Highscore->setIconSize(bigButton);
	ui->main2Highscore->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2Settings->setIcon(settings);
	ui->main2Settings->setIconSize(bigButton);
	ui->main2Settings->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2Manual->setIcon(manual);
	ui->main2Manual->setIconSize(bigButton);
	ui->main2Manual->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2Credits->setIcon(credits);
	ui->main2Credits->setIconSize(bigButton);
	ui->main2Credits->setStyleSheet("QPushButton{background: transparent;}");
	ui->main2QuitGame->setIcon(quit);
	ui->main2QuitGame->setIconSize(bigButton);
	ui->main2QuitGame->setStyleSheet("QPushButton{background: transparent;}");


	// Items in Level 1
	ui->level1Logo->setPixmap(logo);
	ui->level1Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->level1Logo->setStyleSheet("QLabel{background: transparent;}");
	ui->level1_2Level2->setIcon(rightArrow);
	ui->level1_2Level2->setIconSize(arrowButton);
	ui->level1_2Level2->setStyleSheet("QPushButton{background: transparent;}");
	ui->level1_2Level3->setIcon(leftArrow);
	ui->level1_2Level3->setIconSize(arrowButton);
	ui->level1_2Level3->setStyleSheet("QPushButton{background: transparent;}");
	ui->level1_2Main->setIcon(menu);
	ui->level1_2Main->setIconSize(smallButton);
	ui->level1_2Main->setStyleSheet("QPushButton{background: transparent;}");
	ui->level1_2Play->setIcon(play);
	ui->level1_2Play->setIconSize(bigButton);
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
	ui->level2_2Level3->setIcon(rightArrow);
	ui->level2_2Level3->setIconSize(arrowButton);
	ui->level2_2Level1->setStyleSheet("QPushButton{background: transparent;}");
	ui->level2_2Level1->setIcon(leftArrow);
	ui->level2_2Level1->setIconSize(arrowButton);
	ui->level2_2Level3->setStyleSheet("QPushButton{background: transparent;}");
	ui->level2_2Main->setIcon(menu);
	ui->level2_2Main->setIconSize(smallButton);
	ui->level2_2Main->setStyleSheet("QPushButton{background: transparent;}");
	ui->level2_2Play->setIcon(play);
	ui->level2_2Play->setIconSize(bigButton);
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
	ui->level3_2Level1->setIcon(rightArrow);
	ui->level3_2Level1->setIconSize(arrowButton);
	ui->level3_2Level2->setStyleSheet("QPushButton{background: transparent;}");
	ui->level3_2Level2->setIcon(leftArrow);
	ui->level3_2Level2->setIconSize(arrowButton);
	ui->level3_2Level1->setStyleSheet("QPushButton{background: transparent;}");
	ui->level3_2Main->setIcon(menu);
	ui->level3_2Main->setIconSize(smallButton);
	ui->level3_2Main->setStyleSheet("QPushButton{background: transparent;}");
	ui->level3_2Play->setIcon(play);
	ui->level3_2Play->setIconSize(bigButton);
	ui->level3_2Play->setStyleSheet("QPushButton{background: transparent;}");
	ui->level3Trackname->setStyleSheet("QLabel{background: transparent;}");
	ui->level3Trackname->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->level3Trackname->setFont(GillSansMTTitle);
	ui->level3Trackname->setText("Deadly Desert");
	ui->level3Trackpic->setStyleSheet("QLabel{background: transparent; border: 5px solid black}");
	ui->level3Trackpic->setPixmap(yasmarina);

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
	ui->garageAccelerationSlider->setStyleSheet("QSlider{background: transparent;}");
	ui->garageHandlingSlider->setStyleSheet("QSlider{background: transparent;}");
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
	ui->garageLabel->setText("You have " + QString::number(maximumValue) + " points left to distribute");
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
	ui->highscoreLevel1->setStyleSheet("QLabel{background: transparent; color: white}");
	ui->highscoreLevel1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->highscoreLevel1->setFont(GillSansMT);
	ui->highscoreLevel1->setText("Sunny Speedway");
	ui->highscoreLevel2->setStyleSheet("QLabel{background: transparent; color: white}");
	ui->highscoreLevel2->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->highscoreLevel2->setFont(GillSansMT);
	ui->highscoreLevel2->setText("Chancy Circuit");
	ui->highscoreLevel3->setStyleSheet("QLabel{background: transparent; color: white}");
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
	ui->settings2Main->setStyleSheet("QPushButton{background: transparent; color: white}");
	ui->settingsBackgroundSoundLabel->setStyleSheet("QLabel{background: transparent; color: white}");
	ui->settingsBackgroundSoundLabel->setFont(GillSansMT);
	ui->settingsBackgroundSoundLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->settingsBackgroundSoundLabel->setText("Background Sound:");
	ui->settingsBackgroundSoundOn->setStyleSheet("QPushButton{background: transparent; color: white}");
	ui->settingsBackgroundSoundOn->setIcon(soundOn);
	ui->settingsBackgroundSoundOn->setIconSize(arrowButton);
	ui->settingsBackgroundSoundOff->setStyleSheet("QPushButton{background: transparent; color: white}");
	ui->settingsBackgroundSoundOff->setIcon(soundOff);
	ui->settingsBackgroundSoundOff->setIconSize(arrowButton);
	ui->settingsBackgroundSoundSlider->setStyleSheet("QSlider{background: transparent;}");
	ui->settingsBackgroundSoundSlider->setValue(backgroundSoundValue);
	ui->settingsButtonSoundLabel->setStyleSheet("QLabel{background: transparent; color: white}");
	ui->settingsButtonSoundLabel->setFont(GillSansMT);
	ui->settingsButtonSoundLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->settingsButtonSoundLabel->setText("Button Sound:");
	ui->settingsButtonSoundOn->setStyleSheet("QPushButton{background: transparent; color: white}");
	ui->settingsButtonSoundOn->setIcon(soundOn);
	ui->settingsButtonSoundOn->setIconSize(arrowButton);
	ui->settingsButtonSoundOff->setStyleSheet("QPushButton{background: transparent; color: white}");
	ui->settingsButtonSoundOff->setIcon(soundOff);
	ui->settingsButtonSoundOff->setIconSize(arrowButton);
	ui->settingsButtonSoundSlider->setStyleSheet("QSlider{background: transparent;}");
	ui->settingsButtonSoundSlider->setValue(buttonSoundValue);
	ui->settingsRaceSoundLabel->setStyleSheet("QLabel{background: transparent; color: white}");
	ui->settingsRaceSoundLabel->setFont(GillSansMT);
	ui->settingsRaceSoundLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->settingsRaceSoundLabel->setText("Race Sound:");
	ui->settingsRaceSoundOn->setStyleSheet("QPushButton{background: transparent; color: white}");
	ui->settingsRaceSoundOn->setIcon(soundOn);
	ui->settingsRaceSoundOn->setIconSize(arrowButton);
	ui->settingsRaceSoundOff->setStyleSheet("QPushButton{background: transparent; color: white}");
	ui->settingsRaceSoundOff->setIcon(soundOff);
	ui->settingsRaceSoundOff->setIconSize(arrowButton);
	ui->settingsRaceSoundSlider->setStyleSheet("QSlider{background: transparent;}");
	ui->settingsRaceSoundSlider->setValue(raceSoundValue);
	ui->settingsHighscoreResetLabel->setStyleSheet("QLabel{background: transparent; color: white}");
	ui->settingsHighscoreResetLabel->setFont(GillSansMT);
	ui->settingsHighscoreResetLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	ui->settingsHighscoreResetLabel->setText("Highscore Reset:");
	ui->settingsHighscoreResetButton->setStyleSheet("QPushButton{background: transparent; color: white}");
	ui->settingsHighscoreResetButton->setIcon(reset);
	ui->settingsHighscoreResetButton->setIconSize(bigButton);

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
	ui->manualLabel->setStyleSheet("QLabel{background: transparent; color: white}");
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
	ui->creditsLabel->setStyleSheet("QLabel{background: transparent; color: white}");
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
}

mainMenu::~mainMenu()
{
	delete game;
	delete ui;
}

//  Buttons from the Main Menu UI

/*  pages:  0 - Main Menu
 *          1 - Level 1
 *          2 - Level 2
 *          3 - Level 3
 *          4 - Garage
 *          5 - Highscore
 *          6 - Settings
 *          7 - Manual
 *          8 - Credits
*/

// Setbackgroundsound
void mainMenu::setbackgroundsound()
{
	if(active==1)
	{
//		backgroundmusic->play();
	}
	else
		if(active==0)
		{
//			backgroundmusic->stop();
		}
}


//  Sound for buttons
void mainMenu::playbuttonsound()
{
	//if(active==1)
//	buttonsound->play();
}

// Buttons from the main menu
void mainMenu::on_main2Level1_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(1);
}

void mainMenu::on_main2Garage_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(4);
}

void mainMenu::on_main2Highscore_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(5);

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
		line;
		list;
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
			ui->highscoretablelevel1->item(i,0)->setBackgroundColor(QColor(255,255,255,90));
			ui->highscoretablelevel1->item(i,1)->setBackgroundColor(QColor(255,255,255,90));
		}
		inputFile.close();
	}


	filename = "highscores/Hockenheimring.score";
	QFile inputFile2(filename);
	if (inputFile2.open(QIODevice::ReadOnly))
	{
		QTextStream in2(&inputFile2);
		line;
		list;
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
			ui->highscoretablelevel2->item(i,0)->setBackgroundColor(QColor(255,255,255,90));
			ui->highscoretablelevel2->item(i,1)->setBackgroundColor(QColor(255,255,255,90));
		}
		inputFile2.close();
	}

	filename = "highscores/YasMarina.score";
	QFile inputFile3(filename);
	if (inputFile3.open(QIODevice::ReadOnly))
	{
		QTextStream in3(&inputFile3);
		line;
		list;
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
			ui->highscoretablelevel3->item(i,0)->setBackgroundColor(QColor(255,255,255,90));
			ui->highscoretablelevel3->item(i,1)->setBackgroundColor(QColor(255,255,255,90));
		}
		inputFile3.close();
	}
}

void mainMenu::on_main2Settings_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(6);

}

void mainMenu::on_main2Manual_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(7);
}

void mainMenu::on_main2Credits_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(8);
}

void mainMenu::on_main2QuitGame_clicked()
{
	playbuttonsound();
	QCoreApplication::quit();
}

// Buttons from Level 1

void mainMenu::on_level1_2Main_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level1_2Level3_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(3);
}

void mainMenu::on_level1_2Level2_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(2);
}

void mainMenu::on_level1_2Play_clicked()
{
	playbuttonsound();
	//start Level 1
	//world = new World(screenWidth,screenHeight,1);
	//world->showFullScreen();
	//hide();
	game->loadCircuit(Monza);
}

// Buttons from Level 2

void mainMenu::on_level2_2Main_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level2_2Level1_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(1);
}

void mainMenu::on_level2_2Level3_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(3);
}

void mainMenu::on_level2_2Play_clicked()
{
	playbuttonsound();
	//start Level 2
	//world = new World(screenWidth,screenHeight,2);
	//world->showFullScreen();
	//hide();
	game->loadCircuit(Hockenheimring);
}

// Buttons from Level 3

void mainMenu::on_level3_2Main_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level3_2Level2_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(2);
}

void mainMenu::on_level3_2Level1_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(1);
}

void mainMenu::on_level3_2Play_clicked()
{
	playbuttonsound();
	//start Level 3
	//world = new World(screenWidth,screenHeight,3);
	//world->showFullScreen();
	//hide();
	game->loadCircuit(YasMarina);
}

// Buttons from Garage

void mainMenu::on_garage2Main_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Highscore

void mainMenu::on_highscore2Main_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Settings

void mainMenu::on_settings2Main_clicked()
{
	playbuttonsound();
	ui->stackedWidget->setCurrentIndex(0);
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

// Buttons finished


// Garage Configeration


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

// Sound Configeration
void mainMenu::on_settingsBackgroundSoundOn_clicked()
{
	playbuttonsound();
	active = 1;
	setbackgroundsound();
//	backgroundmusic->setVolume(backgroundSoundValue);
	ui->settingsBackgroundSoundSlider->setValue(backgroundSoundValue);
}

void mainMenu::on_settingsBackgroundSoundOff_clicked()
{
	playbuttonsound();
	active=0;
	setbackgroundsound();
	backgroundSoundValue = ui->settingsBackgroundSoundSlider->value();
	ui->settingsBackgroundSoundSlider->setValue(0);
}

void mainMenu::on_settingsBackgroundSoundSlider_valueChanged(int value)
{
	if(active == 0){
		active = 1;
		setbackgroundsound();
	}
//	backgroundmusic->setVolume(value);
}
void mainMenu::on_settingsButtonSoundOn_clicked()
{
	playbuttonsound();
//	buttonsound->setVolume(buttonSoundValue);
	ui->settingsButtonSoundSlider->setValue(buttonSoundValue);
}

void mainMenu::on_settingsButtonSoundOff_clicked()
{
	playbuttonsound();
//	buttonsound->setVolume(0);
	buttonSoundValue = ui->settingsButtonSoundSlider->value();
	ui->settingsButtonSoundSlider->setValue(0);
}

void mainMenu::on_settingsButtonSoundSlider_valueChanged(int value)
{
//	buttonsound->setVolume(value);
}

void mainMenu::on_settingsRaceSoundOn_clicked()
{
	playbuttonsound();
	ui->settingsRaceSoundSlider->setValue(raceSoundValue);
}

void mainMenu::on_settingsRaceSoundOff_clicked()
{
	playbuttonsound();
	//raceSound aus
	raceSoundValue = ui->settingsRaceSoundSlider->value();
	ui->settingsRaceSoundSlider->setValue(0);
}

void mainMenu::on_settingsRaceSoundSlider_valueChanged(int value)
{
	//racesound lauter/leiser
}

// Highscore Configuration

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
