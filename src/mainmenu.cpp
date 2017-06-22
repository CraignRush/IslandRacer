#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainMenu)
{    
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    // Set Backgrounds
    QPixmap mainBackgroundPic(":/images/images/palmtree1_1920_1080.jpg");
    ui->mainBackground->setPixmap(mainBackgroundPic);
    ui->level1Background->setPixmap(mainBackgroundPic);
    ui->level2Background->setPixmap(mainBackgroundPic);
    ui->level3Background->setPixmap(mainBackgroundPic);
    ui->highscoreBackground->setPixmap(mainBackgroundPic);
    ui->settingsBackground->setPixmap(mainBackgroundPic);
    ui->manualBackground->setPixmap(mainBackgroundPic);
    ui->creditsBackground->setPixmap(mainBackgroundPic);
    QPixmap garageBackgroundPic(":/images/images/Garagehell.jpg");
    ui->garageBackground->setPixmap(garageBackgroundPic);

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

    // Buttons in Menu
    ui->Main2Level1->setIcon(play);
    ui->Main2Level1->setIconSize(QSize(200,100));
    ui->Main2Garage->setIcon(garage);
    ui->Main2Garage->setIconSize(QSize(200,100));
    ui->Main2Highscore->setIcon(highscore);
    ui->Main2Highscore->setIconSize(QSize(200,100));
    ui->Main2Settings->setIcon(settings);
    ui->Main2Settings->setIconSize(QSize(200,100));
    ui->Main2Manual->setIcon(manual);
    ui->Main2Manual->setIconSize(QSize(200,100));
    ui->Main2Credits->setIcon(credits);
    ui->Main2Credits->setIconSize(QSize(200,100));
    ui->Main2QuitGame->setIcon(quit);
    ui->Main2QuitGame->setIconSize(QSize(200,100));

    // Buttons in Level 1
    ui->Level1_2Level2->setIcon(rightArrow);
    ui->Level1_2Level2->setIconSize(QSize(100,80));
    ui->Level1_2Level3->setIcon(leftArrow);
    ui->Level1_2Level3->setIconSize(QSize(100,80));
    ui->Level1_2Main->setIcon(menu);
    ui->Level1_2Main->setIconSize(QSize(100,50));
    ui->playLevel1->setIcon(play);
    ui->playLevel1->setIconSize(QSize(200,100));

    // Buttons in Level 2
    ui->Level2_2Level3->setIcon(rightArrow);
    ui->Level2_2Level3->setIconSize(QSize(100,80));
    ui->Level2_2Level1->setIcon(leftArrow);
    ui->Level2_2Level1->setIconSize(QSize(100,80));
    ui->Level2_2Main->setIcon(menu);
    ui->Level2_2Main->setIconSize(QSize(100,50));
    ui->playLevel2->setIcon(play);
    ui->playLevel2->setIconSize(QSize(200,100));

    // Buttons in Level 3
    ui->Level3_2Level1->setIcon(rightArrow);
    ui->Level3_2Level1->setIconSize(QSize(100,80));
    ui->Level3_2Level2->setIcon(leftArrow);
    ui->Level3_2Level2->setIconSize(QSize(100,80));
    ui->Level3_2Main->setIcon(menu);
    ui->Level3_2Main->setIconSize(QSize(100,50));
    ui->playLevel3->setIcon(play);
    ui->playLevel3->setIconSize(QSize(200,100));

    // remaining Buttons
    ui->Garage2Main->setIcon(menu);
    ui->Garage2Main->setIconSize(QSize(100,50));
    ui->Highscore2Main->setIcon(menu);
    ui->Highscore2Main->setIconSize(QSize(100,50));
    ui->Settings2Main->setIcon(menu);
    ui->Settings2Main->setIconSize(QSize(100,50));
    ui->Manual2Main->setIcon(menu);
    ui->Manual2Main->setIconSize(QSize(100,50));
    ui->Credits2Main->setIcon(menu);
    ui->Credits2Main->setIconSize(QSize(100,50));

    // Transparent Background
    QPalette p = palette();
    QString transparentBackground( "background-color: rgba( 255, 255, 255, 0%);" );
    ui->Main2Level1->setPalette(p);
    ui->Main2Level1->setStyleSheet(transparentBackground);
    ui->Main2Garage->setPalette(p);
    ui->Main2Garage->setStyleSheet(transparentBackground);
    ui->Main2Highscore->setPalette(p);
    ui->Main2Highscore->setStyleSheet(transparentBackground);
    ui->Main2Settings->setPalette(p);
    ui->Main2Settings->setStyleSheet(transparentBackground);
    ui->Main2Manual->setPalette(p);
    ui->Main2Manual->setStyleSheet(transparentBackground);
    ui->Main2Credits->setPalette(p);
    ui->Main2Credits->setStyleSheet(transparentBackground);
    ui->Main2QuitGame->setPalette(p);
    ui->Main2QuitGame->setStyleSheet(transparentBackground);
    ui->Level1_2Level2->setPalette(p);
    ui->Level1_2Level2->setStyleSheet(transparentBackground);
    ui->Level1_2Level3->setPalette(p);
    ui->Level1_2Level3->setStyleSheet(transparentBackground);
    ui->Level1_2Main->setPalette(p);
    ui->Level1_2Main->setStyleSheet(transparentBackground);
    ui->playLevel1->setPalette(p);
    ui->playLevel1->setStyleSheet(transparentBackground);
    ui->Level2_2Level1->setPalette(p);
    ui->Level2_2Level1->setStyleSheet(transparentBackground);
    ui->Level2_2Level3->setPalette(p);
    ui->Level2_2Level3->setStyleSheet(transparentBackground);
    ui->Level2_2Main->setPalette(p);
    ui->Level2_2Main->setStyleSheet(transparentBackground);
    ui->playLevel2->setPalette(p);
    ui->playLevel2->setStyleSheet(transparentBackground);
    ui->Level3_2Level2->setPalette(p);
    ui->Level3_2Level2->setStyleSheet(transparentBackground);
    ui->Level3_2Level1->setPalette(p);
    ui->Level3_2Level1->setStyleSheet(transparentBackground);
    ui->Level3_2Main->setPalette(p);
    ui->Level3_2Main->setStyleSheet(transparentBackground);
    ui->playLevel3->setPalette(p);
    ui->playLevel3->setStyleSheet(transparentBackground);
    ui->Garage2Main->setPalette(p);
    ui->Garage2Main->setStyleSheet(transparentBackground);
    ui->Highscore2Main->setPalette(p);
    ui->Highscore2Main->setStyleSheet(transparentBackground);
    ui->Settings2Main->setPalette(p);
    ui->Settings2Main->setStyleSheet(transparentBackground);
    ui->Manual2Main->setPalette(p);
    ui->Manual2Main->setStyleSheet(transparentBackground);
    ui->Credits2Main->setPalette(p);
    ui->Credits2Main->setStyleSheet(transparentBackground);
}

mainMenu::~mainMenu()
{
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

void mainMenu::on_Main2Level1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mainMenu::on_Main2Garage_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void mainMenu::on_Main2Highscore_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    // define header of highscoretables
    QStringList header;
    header << "Platz";
    header << "Name";
    header << "Zeit";

    // set layout of highscoretable for level 1
    ui->highscoretablelevel1->setRowCount(10);
    ui->highscoretablelevel1->setColumnCount(3);
    ui->highscoretablelevel1->verticalHeader()->setVisible(false);
    ui->highscoretablelevel1->horizontalHeader()->setVisible(true);

    ui->highscoretablelevel1->setHorizontalHeaderLabels(header);


   // level1highscorematrix[9][2]="1.324";
   // level1highscorematrix[9][1]="hallo";
   // level1highscorematrix[9][0]="1";


    // fill the highscore for level 1 with data from highscorematrix for level 1
    for (int i=0;i<10;i++)
       {
        if(level1highscorematrix[i][2]!=0)
        {
            QString Platz = level1highscorematrix[i][0];
            QString Name = level1highscorematrix[i][1];
            QString Zeit = level1highscorematrix[i][2];
            ui->highscoretablelevel1->setItem(i, 0, new QTableWidgetItem(Platz));
            ui->highscoretablelevel1->setItem(i, 1, new QTableWidgetItem(Name));
            ui->highscoretablelevel1->setItem(i, 2, new QTableWidgetItem(Zeit));
        }
       }


    // set layout of highscoretable for level 2
    ui->highscoretablelevel2->setRowCount(10);
    ui->highscoretablelevel2->setColumnCount(3);
    ui->highscoretablelevel2->verticalHeader()->setVisible(false);
    ui->highscoretablelevel2->horizontalHeader()->setVisible(true);

    ui->highscoretablelevel2->setHorizontalHeaderLabels(header);
    ui->highscoretablelevel2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // fill the highscore for level 2 with data from highscorematrix for level 2
    for (int i=0;i<10;i++)
       {
        if(level2highscorematrix[i][2]!=0)
        {
            QString Platz = level2highscorematrix[i][0];
            QString Name = level2highscorematrix[i][1];
            QString Zeit = level2highscorematrix[i][2];
            ui->highscoretablelevel2->setItem(i, 0, new QTableWidgetItem(Platz));
            ui->highscoretablelevel2->setItem(i, 1, new QTableWidgetItem(Name));
            ui->highscoretablelevel2->setItem(i, 2, new QTableWidgetItem(Zeit));
        }
       }


    // set layout of highscoretable for level 3
    ui->highscoretablelevel3->setRowCount(10);
    ui->highscoretablelevel3->setColumnCount(3);
    ui->highscoretablelevel3->verticalHeader()->setVisible(false);
    ui->highscoretablelevel3->horizontalHeader()->setVisible(true);

    ui->highscoretablelevel3->setHorizontalHeaderLabels(header);
    ui->highscoretablelevel3->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // fill the highscore for level 3 with data from highscorematrix for level 3
    for (int i=0;i<10;i++)
       {
        if(level3highscorematrix[i][2]!=0)
        {
            QString Platz = level3highscorematrix[i][0];
            QString Name = level3highscorematrix[i][1];
            QString Zeit = level3highscorematrix[i][2];
            ui->highscoretablelevel3->setItem(i, 0, new QTableWidgetItem(Platz));
            ui->highscoretablelevel3->setItem(i, 1, new QTableWidgetItem(Name));
            ui->highscoretablelevel3->setItem(i, 2, new QTableWidgetItem(Zeit));
        }
       }



}

void mainMenu::on_Main2Settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}

void mainMenu::on_Main2Manual_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void mainMenu::on_Main2Credits_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void mainMenu::on_Main2QuitGame_clicked()
{
    QCoreApplication::quit();
}

// Buttons from Level 1

void mainMenu::on_Level1_2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_Level1_2Level3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void mainMenu::on_Level1_2Level2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void mainMenu::on_playLevel1_clicked()
{
    //start Level 1
    world = new World(800,800,1);
    world->show();
    //hide();
}

// Buttons from Level 2

void mainMenu::on_Level2_2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_Level2_2Level1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mainMenu::on_Level2_2Level3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void mainMenu::on_playLevel2_clicked()
{
    //start Level 2
    world = new World(800,800,2);
    world->show();
    //hide();
}

// Buttons from Level 3

void mainMenu::on_Level3_2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void mainMenu::on_Level3_2Level2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void mainMenu::on_Level3_2Level1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mainMenu::on_playLevel3_clicked()
{
    //start Level 3
    world = new World(800,800,3);
    world->show();
    //hide();
}

// Buttons from Garage

void mainMenu::on_Garage2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Highscore

void mainMenu::on_Highscore2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Settings

void mainMenu::on_Settings2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Manual

void mainMenu::on_Manual2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons from Credits

void mainMenu::on_Credits2Main_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// Buttons finished

// Garage Configeration

int maximumValue = 10;
int accelerationValue = 0;
int topspeedValue = 0;
int handlingValue = 0;

void mainMenu::on_sliderAcceleration_valueChanged(int value)
{
    accelerationValue = value;
    ui->acceleration->setText(QString::number(accelerationValue));
    ui->sliderHandling->setMaximum(maximumValue - accelerationValue - topspeedValue);
    ui->sliderTopspeed->setMaximum(maximumValue- accelerationValue - handlingValue);
}

void mainMenu::on_sliderTopspeed_valueChanged(int value)
{
    topspeedValue = value;
    ui->topSpeed->setText(QString::number(topspeedValue));
    ui->sliderAcceleration->setMaximum(maximumValue - topspeedValue - handlingValue);
    ui->sliderHandling->setMaximum(maximumValue - topspeedValue - accelerationValue);
}

void mainMenu::on_sliderHandling_valueChanged(int value)
{
    handlingValue = value;
    ui->handling->setText(QString::number(handlingValue));
    ui->sliderAcceleration->setMaximum(maximumValue - handlingValue - topspeedValue);
    ui->sliderTopspeed->setMaximum(maximumValue - handlingValue - accelerationValue);
}


// Highscore Configeration

