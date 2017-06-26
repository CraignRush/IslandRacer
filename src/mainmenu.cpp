#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainMenu)
{    
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    // Set Backgrounds
    QString backgroundImage( "background-image: url(:/images/images/palmtree1_1920_1080.jpg);" );
    QString garageImage( "background-image: url(:/images/images/Garagehell.jpg);" );

    ui->centralWidget->setStyleSheet(backgroundImage);
    ui->garage->setStyleSheet(garageImage);

    QPixmap logo(":/images/images/Logo.png");
    ui->mainLogo->setPixmap(logo);
    ui->mainLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->mainLogo->setStyleSheet("QLabel{background: transparent;}");
    ui->level1Logo->setPixmap(logo);
    ui->level1Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level1Logo->setStyleSheet("QLabel{background: transparent;}");
    ui->level2Logo->setPixmap(logo);
    ui->level2Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level2Logo->setStyleSheet("QLabel{background: transparent;}");
    ui->level3Logo->setPixmap(logo);
    ui->level3Logo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->level3Logo->setStyleSheet("QLabel{background: transparent;}");
    ui->garageLogo->setPixmap(logo);
    ui->garageLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->garageLogo->setStyleSheet("QLabel{background: transparent;}");
    ui->highscoreLogo->setPixmap(logo);
    ui->highscoreLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->highscoreLogo->setStyleSheet("QLabel{background: transparent;}");
    ui->settingsLogo->setPixmap(logo);
    ui->settingsLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->settingsLogo->setStyleSheet("QLabel{background: transparent;}");
    ui->manualLogo->setPixmap(logo);
    ui->manualLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->manualLogo->setStyleSheet("QLabel{background: transparent;}");
    ui->creditsLogo->setPixmap(logo);
    ui->creditsLogo->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->creditsLogo->setStyleSheet("QLabel{background: transparent;}");

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

    // Items in Menu
    ui->main2Level1->setIcon(play);
    ui->main2Level1->setIconSize(QSize(0.9 * ui->main2Level1->width(),0.45 * ui->main2Level1->width()));
    ui->main2Level1->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2Garage->setIcon(garage);
    ui->main2Garage->setIconSize(QSize(0.9 * ui->main2Garage->width(),0.45 * ui->main2Garage->width()));
    ui->main2Garage->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2Highscore->setIcon(highscore);
    ui->main2Highscore->setIconSize(QSize(0.9 * ui->main2Highscore->width(),0.45 * ui->main2Highscore->width()));
    ui->main2Highscore->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2Settings->setIcon(settings);
    ui->main2Settings->setIconSize(QSize(0.9 * ui->main2Settings->width(),0.45 * ui->main2Settings->width()));
    ui->main2Settings->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2Manual->setIcon(manual);
    ui->main2Manual->setIconSize(QSize(0.9 * ui->main2Manual->width(),0.45 * ui->main2Manual->width()));
    ui->main2Manual->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2Credits->setIcon(credits);
    ui->main2Credits->setIconSize(QSize(0.9 * ui->main2Credits->width(),0.45 * ui->main2Credits->width()));
    ui->main2Credits->setStyleSheet("QPushButton{background: transparent;}");
    ui->main2QuitGame->setIcon(quit);
    ui->main2QuitGame->setIconSize(QSize(0.9 * ui->main2QuitGame->width(),0.45 * ui->main2QuitGame->width()));
    ui->main2QuitGame->setStyleSheet("QPushButton{background: transparent;}");


    // Items in Level 1
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

    // Items in Level 2
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

    // Items in Level 3
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

    // Items in garage
    ui->garage2Main->setIcon(menu);
    ui->garage2Main->setIconSize(QSize(100,50));
    ui->garage2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->garageTopspeedSlider->setStyleSheet("QSlider{background: transparent;}");
    ui->garageAccelerationSlider->setStyleSheet("QSlider{background: transparent;}");
    ui->garageHandlingSlider->setStyleSheet("QSlider{background: transparent;}");
    ui->garageTopspeedLabel->setStyleSheet("QLabel{background: transparent;}");
    ui->garageAccelerationLabel->setStyleSheet("QLabel{background: transparent;}");
    ui->garageHandlingLabel->setStyleSheet("QLabel{background: transparent;}");

    // Items in highscore
    ui->highscore2Main->setIcon(menu);
    ui->highscore2Main->setIconSize(QSize(100,50));
    ui->highscore2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->highscoreLevel1->setStyleSheet("QLabel{background: transparent;}");
    ui->highscoreLevel2->setStyleSheet("QLabel{background: transparent;}");
    ui->highscoreLevel3->setStyleSheet("QLabel{background: transparent;}");
    ui->highscoretablelevel1->setStyleSheet("QTableWidget{background: transparent;}");
    ui->highscoretablelevel2->setStyleSheet("QTableWidget{background: transparent;}");
    ui->highscoretablelevel3->setStyleSheet("QTableWidget{background: transparent;}");

    // Items in settings
    ui->settings2Main->setIcon(menu);
    ui->settings2Main->setIconSize(QSize(100,50));
    ui->settings2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->settingsSoundLabel->setStyleSheet("QLabel{background: transparent;}");
    ui->settingsSoundOff->setStyleSheet("QPushButton{background: transparent;}");
    ui->settingsSoundOn->setStyleSheet("QPushButton{background: transparent;}");

    // Items in manual
    ui->manual2Main->setIcon(menu);
    ui->manual2Main->setIconSize(QSize(100,50));
    ui->manual2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->manualLabel->setStyleSheet("QLabel{background: transparent;}");

    // Items in credits
    ui->credits2Main->setIcon(menu);
    ui->credits2Main->setIconSize(QSize(100,50));
    ui->credits2Main->setStyleSheet("QPushButton{background: transparent;}");
    ui->creditsLabel->setStyleSheet("QLabel{background: transparent;}");

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
    world = new World(800,800,1);
    world->show();
    //hide();
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
    world = new World(800,800,2);
    world->show();
    //hide();
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
    world = new World(800,800,3);
    world->show();
    //hide();
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

int maximumValue = 10;
int accelerationValue = 0;
int topspeedValue = 0;
int handlingValue = 0;

void mainMenu::on_garageAccelerationSlider_valueChanged(int value)
{
    accelerationValue = value;
    ui->garageAccelerationLabel->setText(QString::number(accelerationValue));

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
    ui->garageTopspeedLabel->setText(QString::number(topspeedValue));
}

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
    ui->garageHandlingLabel->setText(QString::number(handlingValue));
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
