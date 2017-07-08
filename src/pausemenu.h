#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class PauseMenu : public QWidget
{
    Q_OBJECT

private:
    QGridLayout* mGridLayout;
    QPushButton* mResumeButton;
    QPushButton* mRestartButton;
    QPushButton* mSettingsButton;
    QPushButton* mQuitButton;

public:
    explicit PauseMenu(int screenHeight, QWidget *parent = 0);

signals:
    void resumeGame();
    void restartGame();
    void quitGame();

public slots:
    void resumeClicked();
    void restartClicked();
    void settingsClicked();
    void quitClicked();
};

#endif // PAUSEMENU_H
