#include "pausemenu.h"

PauseMenu::PauseMenu(int screenHeight, QWidget *parent) : QWidget(parent)
{
    // Main Layout
    mGridLayout = new QGridLayout();

    // Define button size
    QSize bigButton(0.2 * screenHeight, 0.1 * screenHeight);

    mResumeButton = new QPushButton();
    mResumeButton->setIcon(QIcon(":/images/images/play.png"));
    mResumeButton->setIconSize(bigButton);
    mResumeButton->setStyleSheet("QPushButton{background: transparent;}");

    mRestartButton = new QPushButton();
    mRestartButton->setIcon(QIcon(":/images/images/garage.png"));
    mRestartButton->setIconSize(bigButton);
    mRestartButton->setStyleSheet("QPushButton{background: transparent;}");

    mSettingsButton = new QPushButton();
    mSettingsButton->setIcon(QIcon(":/images/images/manual.png"));
    mSettingsButton->setIconSize(bigButton);
    mSettingsButton->setStyleSheet("QPushButton{background: transparent;}");

    mQuitButton = new QPushButton();
    mQuitButton->setIcon(QIcon(":/images/images/quit.png"));
    mQuitButton->setIconSize(bigButton);
    mQuitButton->setStyleSheet("QPushButton{background: transparent;}");

    // Create spacer
    //QHorizontalSpacer*


    // Add Buttons to layout
    mGridLayout->addWidget(mResumeButton, 0, 1, 1, 1);
    mGridLayout->addWidget(mRestartButton, 1, 1, 1, 1);
    mGridLayout->addWidget(mSettingsButton, 2, 1, 1, 1);
    mGridLayout->addWidget(mQuitButton, 3, 1, 1, 1);

    setLayout(mGridLayout);
}
