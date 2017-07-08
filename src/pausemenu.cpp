#include "pausemenu.h"

PauseMenu::PauseMenu(int screenHeight, QWidget *parent) : QWidget(parent)
{
    // Main Layout
    mGridLayout = new QGridLayout();

    // Define button size
    QSize bigButton(0.2 * screenHeight, 0.1 * screenHeight);

    mResumeButton = new QPushButton();
    mResumeButton->setIcon(QIcon(":/images/images/resume.png"));
    mResumeButton->setIconSize(bigButton);
    mResumeButton->setStyleSheet("QPushButton{background: transparent;}");
    connect(mResumeButton, SIGNAL(clicked(bool)), this, SLOT(resumeClicked()));

    mRestartButton = new QPushButton();
    mRestartButton->setIcon(QIcon(":/images/images/restart.png"));
    mRestartButton->setIconSize(bigButton);
    mRestartButton->setStyleSheet("QPushButton{background: transparent;}");
    connect(mRestartButton, SIGNAL(clicked(bool)), this, SLOT(restartClicked()));

    mSettingsButton = new QPushButton();
    mSettingsButton->setIcon(QIcon(":/images/images/settings.png"));
    mSettingsButton->setIconSize(bigButton);
    mSettingsButton->setStyleSheet("QPushButton{background: transparent;}");
    connect(mSettingsButton, SIGNAL(clicked(bool)), this, SLOT(settingsClicked()));

    mQuitButton = new QPushButton();
    mQuitButton->setIcon(QIcon(":/images/images/quit.png"));
    mQuitButton->setIconSize(bigButton);
    mQuitButton->setStyleSheet("QPushButton{background: transparent;}");
    connect(mQuitButton, SIGNAL(clicked(bool)), this, SLOT(quitClicked()));

    // Add Buttons to layout
    mGridLayout->addWidget(mResumeButton, 0, 1, 1, 1);
    mGridLayout->addWidget(mRestartButton, 1, 1, 1, 1);
    mGridLayout->addWidget(mSettingsButton, 2, 1, 1, 1);
    mGridLayout->addWidget(mQuitButton, 3, 1, 1, 1);

    setLayout(mGridLayout);
}

void PauseMenu::resumeClicked()
{
    emit resumeGame();
}

void PauseMenu::restartClicked()
{
    emit restartGame();
}

void PauseMenu::settingsClicked()
{

}

void PauseMenu::quitClicked()
{
    emit quitGame();
}
