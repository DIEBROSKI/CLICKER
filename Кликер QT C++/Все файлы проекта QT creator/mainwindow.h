#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButtonClick();
    void handleUpgradeClick();
    void updateUpgradeButton();
    void updateLevelBar();
    void unlockAchievement(const QString& achievement);
    void updateNextAchievement();

private:
    Ui::MainWindow *ui;
    int clickCount;
    int clickRate;
    int upgradePrice;
    int level;
    int levelThreshold;
    int nextAchievementClicks;
    int getNextAchievement();
};

#endif // MAINWINDOW_H
