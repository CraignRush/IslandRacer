#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "world.h"

namespace Ui {
class mainMenu;
}

class mainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = 0);
    ~mainMenu();

    QString level1highscorematrix[11][3] = { {0} };
    QString level2highscorematrix[11][3] = { {0} };
    QString level3highscorematrix[11][3] = { {0} };

private slots:

    void on_Main2Level1_clicked();

    void on_Main2Garage_clicked();

    void on_Main2Highscore_clicked();

    void on_Main2Settings_clicked();

    void on_Main2Manual_clicked();

    void on_Main2Credits_clicked();

    void on_Main2QuitGame_clicked();

    void on_Level1_2Main_clicked();

    void on_Level2_2Main_clicked();

    void on_Level3_2Main_clicked();

    void on_Garage2Main_clicked();

    void on_Highscore2Main_clicked();

    void on_Settings2Main_clicked();

    void on_Manual2Main_clicked();

    void on_Credits2Main_clicked();

    void on_Level1_2Level2_clicked();

    void on_Level1_2Level3_clicked();

    void on_Level2_2Level1_clicked();

    void on_Level2_2Level3_clicked();

    void on_Level3_2Level1_clicked();

    void on_Level3_2Level2_clicked();

    void on_playLevel3_clicked();

    void on_playLevel2_clicked();

    void on_playLevel1_clicked();

    void on_sliderAcceleration_valueChanged(int value);

    void on_sliderTopspeed_valueChanged(int value);

    void on_sliderHandling_valueChanged(int value);

private:
    Ui::mainMenu *ui;
    World* world;
};

#endif // MAINMENU_H
