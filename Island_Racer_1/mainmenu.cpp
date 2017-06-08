#include "mainmenu.h"
#include "ui_mainmenu.h"

mainMenu::mainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    ui->mainBackground->setPixmap(QPixmap(":/resources/resources/palmtree1_1920_1080.jpg"));
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
