#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "qscreen.h"

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

    // Get Screensize
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    screenHeight = screenGeometry.height();
    screenWidth = screenGeometry.width();

    // Init game object with screen width/height and fullscreen mode
    game = new Game(screenWidth, screenHeight, true);

    // Set Backgrounds
    QString backgroundImage( "background-image: url(:/images/images/palmtree1_1920_1080.jpg);" );
    QString garageImage( "background-image: url(:/images/images/Garagehell.jpg);" );

    // Set Pixmaps
    QPixmap logo(":/images/images/Logo.png");
    QPixmap hockenheimbig(":/images/images/Hockenheimtextur.png");
    QPixmap monzabig(":/images/images/Monzatextur.png") ;
    QPixmap yasmarinabig(":/images/images/YasMarinatextur.png");
    QPixmap hockenheim, monza, yasmarina;

    hockenheim = hockenheimbig.scaledToHeight(0.5 * screenHeight);
    monza = monzabig.scaledToHeight(0.5 * screenHeight);
    yasmarina = yasmarinabig.scaledToHeight(0.5 * screenHeight);

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

    // Set Fonts
	GillSansMT.setFamily("GillSansMT");
	GillSansMT.setPointSize(20);
    GillSansMT.setBold(1);

    QFont GillSansMTTitle;
    GillSansMTTitle = GillSansMT;
    GillSansMTTitle.setPointSize(30);

    // Items for all
    ui->centralWidget->setStyleSheet(backgroundImage);

    // Items in Menu
    ui->mainLogo->setPixmap(logo);
    ui->mainLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->mainLogo->setStyleSheet("QLabel{background: transparent;}");
    ui->main2Level1->setIcon(play);
    ui->main2Level1->setIconSize(QSize(0.9 * ui->main2Level1->width(),0.4 * ui->main2Level1->width()));
    ui->main2Level1->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2Garage->setIcon(garage);
    ui->main2Garage->setIconSize(QSize(0.9 * ui->main2Garage->width(),0.4 * ui->main2Garage->width()));
    ui->main2Garage->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2Highscore->setIcon(highscore);
    ui->main2Highscore->setIconSize(QSize(0.9 * ui->main2Highscore->width(),0.4 * ui->main2Highscore->width()));
    ui->main2Highscore->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2Settings->setIcon(settings);
    ui->main2Settings->setIconSize(QSize(0.9 * ui->main2Settings->width(),0.4 * ui->main2Settings->width()));
    ui->main2Settings->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2Manual->setIcon(manual);
    ui->main2Manual->setIconSize(QSize(0.9 * ui->main2Manual->width(),0.4 * ui->main2Manual->width()));
    ui->main2Manual->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2Credits->setIcon(credits);
    ui->main2Credits->setIconSize(QSize(0.9 * ui->main2Credits->width(),0.4 * ui->main2Credits->width()));
    ui->main2Credits->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2QuitGame->setIcon(quit);
    ui->main2QuitGame->setIconSize(QSize(0.9 * ui->main2QuitGame->width(),0.4 * ui->main2QuitGame->width()));
    ui->main2QuitGame->setStyleSheet("QPushButton{background: transparent;}");


    // Items in Level 1
    ui->level1Logo->setPixmap(logo);
    ui->level1Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level1Logo->setStyleSheet("QLabel{background: transparent;}");
    ui->level1_2Level2->setIcon(rightArrow);
    ui->level1_2Level2->setIconSize(QSize(100,80));
    ui->level1_2Level2->setStyleSheet("QPushButton{background: transparent;}");
    ui->level1_2Level3->setIcon(leftArrow);
    ui->level1_2Level3->setIconSize(QSize(100,80));
    ui->level1_2Level3->setStyleSheet("QPushButton{background: transparent;}");
    ui->level1_2Main->setIcon(menu);
    ui->level1_2Main->setIconSize(QSize(100,50));
    ui->level1_2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->level1_2Play->setIcon(play);
    ui->level1_2Play->setIconSize(QSize(200,100));
    ui->level1_2Play->setStyleSheet("QPushButton{background: transparent;}");
    ui->level1Trackname->setStyleSheet("QLabel{background: transparent;}");
    ui->level1Trackname->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level1Trackname->setFont(GillSansMT);
    ui->level1Trackname->setText("Sunny Speedway");
    ui->level1Trackpic->setStyleSheet("QLabel{background: transparent; border: 5px solid black}");
    ui->level1Trackpic->setPixmap(monza);

    // Items in Level 2
    ui->level2Logo->setPixmap(logo);
    ui->level2Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level2Logo->setStyleSheet("QLabel{background: transparent;}");
    ui->level2_2Level3->setIcon(rightArrow);
    ui->level2_2Level3->setIconSize(QSize(100,80));
    ui->level2_2Level1->setStyleSheet("QPushButton{background: transparent;}");
    ui->level2_2Level1->setIcon(leftArrow);
    ui->level2_2Level1->setIconSize(QSize(100,80));
    ui->level2_2Level3->setStyleSheet("QPushButton{background: transparent;}");
    ui->level2_2Main->setIcon(menu);
    ui->level2_2Main->setIconSize(QSize(100,50));
    ui->level2_2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->level2_2Play->setIcon(play);
    ui->level2_2Play->setIconSize(QSize(200,100));
    ui->level2_2Play->setStyleSheet("QPushButton{background: transparent;}");
    ui->level2Trackname->setStyleSheet("QLabel{background: transparent;}");
    ui->level2Trackname->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level2Trackname->setFont(GillSansMT);
    ui->level2Trackname->setText("Chancy Circuit");
    ui->level2Trackpic->setStyleSheet("QLabel{background: transparent; border: 5px solid black}");
    ui->level2Trackpic->setPixmap(hockenheim);

    // Items in Level 3
    ui->level3Logo->setPixmap(logo);
    ui->level3Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level3Logo->setStyleSheet("QLabel{background: transparent;}");
    ui->level3_2Level1->setIcon(rightArrow);
    ui->level3_2Level1->setIconSize(QSize(100,80));
    ui->level3_2Level2->setStyleSheet("QPushButton{background: transparent;}");
    ui->level3_2Level2->setIcon(leftArrow);
    ui->level3_2Level2->setIconSize(QSize(100,80));
    ui->level3_2Level1->setStyleSheet("QPushButton{background: transparent;}");
    ui->level3_2Main->setIcon(menu);
    ui->level3_2Main->setIconSize(QSize(100,50));
    ui->level3_2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->level3_2Play->setIcon(play);
    ui->level3_2Play->setIconSize(QSize(200,100));
    ui->level3_2Play->setStyleSheet("QPushButton{background: transparent;}");
    ui->level3Trackname->setStyleSheet("QLabel{background: transparent;}");
    ui->level3Trackname->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level3Trackname->setFont(GillSansMT);
    ui->level3Trackname->setText("Deadly Desert");
    ui->level3Trackpic->setStyleSheet("QLabel{background: transparent; border: 5px solid black}");
    ui->level3Trackpic->setPixmap(yasmarina);

    // Items in garage
    ui->garage->setStyleSheet(garageImage);
    ui->garageLogo->setPixmap(logo);
    ui->garageLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->garageLogo->setStyleSheet("QLabel{background: transparent;}");
    ui->garage2Main->setIcon(menu);
    ui->garage2Main->setIconSize(QSize(100,50));
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
    ui->garageLabel->setText("You have 10 points left to distribute");
    ui->garageLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->garageLabel->setFont(GillSansMT);

    // Items in highscore
    ui->highscoreLogo->setPixmap(logo);
    ui->highscoreLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->highscoreLogo->setStyleSheet("QLabel{background: transparent;}");
    ui->highscore2Main->setIcon(menu);
    ui->highscore2Main->setIconSize(QSize(100,50));
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
    ui->settings2Main->setIconSize(QSize(100,50));
    ui->settings2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->settingsSoundLabel->setStyleSheet("QLabel{background: transparent;}");
    ui->settingsSoundOff->setStyleSheet("QPushButton{background: transparent;}");
    ui->settingsSoundOn->setStyleSheet("QPushButton{background: transparent;}");

    // Items in manual
    ui->manualLogo->setPixmap(logo);
    ui->manualLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->manualLogo->setStyleSheet("QLabel{background: transparent;}");
    ui->manual2Main->setIcon(menu);
    ui->manual2Main->setIconSize(QSize(100,50));
    ui->manual2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->manualTitle->setStyleSheet("QLabel{background: transparent;}");
    ui->manualTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->manualTitle->setFont(GillSansMTTitle);
    ui->manualTitle->setText("Manual:");
    ui->manualLabel->setStyleSheet("QLabel{background: transparent; color: white}");
    ui->manualLabel->setFont(GillSansMT);
    ui->manualLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->manualLabel->setText("You can steer the car with the arrow keys.\n\nYou can adjust your car in the garage.\nThe better your times on the tracks are, the more points you can distribute.");

    // Items in credits
    ui->creditsLogo->setPixmap(logo);
    ui->creditsLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->creditsLogo->setStyleSheet("QLabel{background: transparent;}");
    ui->credits2Main->setIcon(menu);
    ui->credits2Main->setIconSize(QSize(100,50));
    ui->credits2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->creditsTitle->setStyleSheet("QLabel{background: transparent;}");
    ui->creditsTitle->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->creditsTitle->setFont(GillSansMTTitle);
    ui->creditsTitle->setText("Credits:");
    ui->creditsLabel->setStyleSheet("QLabel{background: transparent; color: white}");
    ui->creditsLabel->setFont(GillSansMT);
    ui->creditsLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);


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

// Buttons from the main menu

void mainMenu::on_main2Level1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mainMenu::on_main2Garage_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void mainMenu::on_main2Highscore_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    // define header of highscoretables
    QStringList header;
    header << "#";
    header << "Name";
    header << "Zeit";

    // set layout of highscoretable for level 1
    ui->highscoretablelevel1->setRowCount(10);
    ui->highscoretablelevel1->setColumnCount(3);
    ui->highscoretablelevel1->verticalHeader()->setVisible(false);
    ui->highscoretablelevel1->horizontalHeader()->setVisible(true);

    ui->highscoretablelevel1->setHorizontalHeaderLabels(header);
    ui->highscoretablelevel1->setColumnWidth(0,30);
    ui->highscoretablelevel1->setColumnWidth(1,0.5 * (ui->highscoreLevel1->width() - 30));
    ui->highscoretablelevel1->setColumnWidth(2,0.5 * (ui->highscoreLevel1->width() - 30));

   // level1highscorematrix[9][2]="1.324";
   // level1highscorematrix[9][1]="hallo";
   // level1highscorematrix[9][0]="1";


    // fill the highscore for level 1 with data from highscorematrix for level 1
    for (int i=0;i<10;i++)
       {
        //if(level1highscorematrix[i][2]!=0)
        {
            QString Platz = level1highscorematrix[i][0];
            QString Name = level1highscorematrix[i][1];
            QString Zeit = level1highscorematrix[i][2];
            ui->highscoretablelevel1->setItem(i, 0, new QTableWidgetItem());
            //ui->highscoretablelevel1->item(i,0)->setText(Platz);
            ui->highscoretablelevel1->item(i,0)->setBackground(Qt::white);
            ui->highscoretablelevel1->setItem(i, 1, new QTableWidgetItem());
            //ui->highscoretablelevel1->item(i,1)->setText(Name);
            ui->highscoretablelevel1->item(i,1)->setBackground(Qt::white);
            ui->highscoretablelevel1->setItem(i, 2, new QTableWidgetItem());
            //ui->highscoretablelevel1->item(i,2)->setText(Zeit);
            ui->highscoretablelevel1->item(i,2)->setBackground(Qt::white);
        }
       }

    // set layout of highscoretable for level 2
    ui->highscoretablelevel2->setRowCount(10);
    ui->highscoretablelevel2->setColumnCount(3);
    ui->highscoretablelevel2->verticalHeader()->setVisible(false);
    ui->highscoretablelevel2->horizontalHeader()->setVisible(true);

    ui->highscoretablelevel2->setHorizontalHeaderLabels(header);
    ui->highscoretablelevel2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->highscoretablelevel2->setColumnWidth(0,30);
    ui->highscoretablelevel2->setColumnWidth(1,0.5 * (ui->highscoreLevel2->width() - 30));
    ui->highscoretablelevel2->setColumnWidth(2,0.5 * (ui->highscoreLevel2->width() - 30));

    // fill the highscore for level 2 with data from highscorematrix for level 2
    for (int i=0;i<10;i++)
       {
        //if(level2highscorematrix[i][2]!=0)
        {
            QString Platz = level2highscorematrix[i][0];
            QString Name = level2highscorematrix[i][1];
            QString Zeit = level2highscorematrix[i][2];
            ui->highscoretablelevel2->setItem(i, 0, new QTableWidgetItem());
            //ui->highscoretablelevel2->item(i,0)->setText(Platz);
            ui->highscoretablelevel2->item(i,0)->setBackground(Qt::white);
            ui->highscoretablelevel2->setItem(i, 1, new QTableWidgetItem());
            //ui->highscoretablelevel2->item(i,1)->setText(Name);
            ui->highscoretablelevel2->item(i,1)->setBackground(Qt::white);
            ui->highscoretablelevel2->setItem(i, 2, new QTableWidgetItem());
            //ui->highscoretablelevel2->item(i,2)->setText(Zeit);
            ui->highscoretablelevel2->item(i,2)->setBackground(Qt::white);
        }
       }


    // set layout of highscoretable for level 3
    ui->highscoretablelevel3->setRowCount(10);
    ui->highscoretablelevel3->setColumnCount(3);
    ui->highscoretablelevel3->verticalHeader()->setVisible(false);
    ui->highscoretablelevel3->horizontalHeader()->setVisible(true);

    ui->highscoretablelevel3->setHorizontalHeaderLabels(header);
    ui->highscoretablelevel3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->highscoretablelevel3->setColumnWidth(0,30);
    ui->highscoretablelevel3->setColumnWidth(1,0.5 * (ui->highscoreLevel3->width() - 30));
    ui->highscoretablelevel3->setColumnWidth(2,0.5 * (ui->highscoreLevel3->width() - 30));


    // fill the highscore for level 3 with data from highscorematrix for level 3
    for (int i=0;i<10;i++)
       {
        //if(level3highscorematrix[i][2]!=0)
        {
            QString Platz = level3highscorematrix[i][0];
            QString Name = level3highscorematrix[i][1];
            QString Zeit = level3highscorematrix[i][2];
            ui->highscoretablelevel3->setItem(i, 0, new QTableWidgetItem());
            //ui->highscoretablelevel3->item(i,0)->setText(Platz);
            ui->highscoretablelevel3->item(i,0)->setBackground(Qt::white);
            ui->highscoretablelevel3->setItem(i, 1, new QTableWidgetItem());
            //ui->highscoretablelevel3->item(i,1)->setText(Name);
            ui->highscoretablelevel3->item(i,1)->setBackground(Qt::white);
            ui->highscoretablelevel3->setItem(i, 2, new QTableWidgetItem());
            //ui->highscoretablelevel3->item(i,2)->setText(Zeit);
            ui->highscoretablelevel3->item(i,2)->setBackground(Qt::white);
        }
       }



}

void mainMenu::on_main2Settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void mainMenu::on_main2Manual_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void mainMenu::on_main2Credits_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void mainMenu::on_main2QuitGame_clicked()
{
    QCoreApplication::quit();
}

// Buttons from Level 1

void mainMenu::on_level1_2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level1_2Level3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void mainMenu::on_level1_2Level2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void mainMenu::on_level1_2Play_clicked()
{
    //start Level 1
    //world = new World(screenWidth,screenHeight,1);
    //world->showFullScreen();
    //hide();
    game->loadCircuit(Monza);
}

// Buttons from Level 2

void mainMenu::on_level2_2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level2_2Level1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mainMenu::on_level2_2Level3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void mainMenu::on_level2_2Play_clicked()
{
    //start Level 2
    //world = new World(screenWidth,screenHeight,2);
    //world->showFullScreen();
    //hide();
    game->loadCircuit(Hockenheimring);
}

// Buttons from Level 3

void mainMenu::on_level3_2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_level3_2Level2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void mainMenu::on_level3_2Level1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mainMenu::on_level3_2Play_clicked()
{
    //start Level 3
    //world = new World(screenWidth,screenHeight,3);
    //world->showFullScreen();
    //hide();
    game->loadCircuit(YasMarina);
}

// Buttons from Garage

void mainMenu::on_garage2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Highscore

void mainMenu::on_highscore2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Settings

void mainMenu::on_settings2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Manual

void mainMenu::on_manual2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Credits

void mainMenu::on_credits2Main_clicked()
{
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

// Highscore Configeration
