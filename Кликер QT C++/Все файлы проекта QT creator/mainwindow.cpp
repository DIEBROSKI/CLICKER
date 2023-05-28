#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->clickButton, &QPushButton::clicked, this, &MainWindow::handleButtonClick);

    clickCount = 0;
    clickRate = 1;
    upgradePrice = 10;
    level = 1;
    levelThreshold = 100;
    nextAchievementClicks = 1;

    connect(ui->clickButton, &QPushButton::clicked, this, &MainWindow::handleButtonClick);
    connect(ui->upgradeButton, &QPushButton::clicked, this, &MainWindow::handleUpgradeClick);

    updateUpgradeButton();
    updateLevelBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleButtonClick()
{
    clickCount += clickRate;
    ui->clickLabel->setText(QString("Clicks: %1").arg(clickCount));
    updateUpgradeButton();
    updateLevelBar();

    if (clickCount >= levelThreshold) {
        level++;
        levelThreshold *= 10;
        unlockAchievement(QString("Level Up: Level %1").arg(level));
        updateLevelBar();
    }
    static int colorIndex = 0;
    QStringList colors = {"#FF90FF", "#CCC9FF", "#FFCCFF"};

    setStyleSheet(QString("background-color: %1;").arg(colors[colorIndex]));

    colorIndex = (colorIndex + 1) % colors.size();
}


void MainWindow::handleUpgradeClick()
{
    if (clickCount >= upgradePrice) {
        clickCount -= upgradePrice;
        clickRate++;
        upgradePrice *= 2;
        ui->clickLabel->setText(QString("Clicks: %1").arg(clickCount));
        updateUpgradeButton();

    }
}

void MainWindow::updateUpgradeButton()
{
    ui->upgradeButton->setText(QString("Upgrade (%1 clicks)").arg(upgradePrice));
    ui->upgradeButton->setEnabled(clickCount >= upgradePrice);
}

void MainWindow::updateLevelBar()
{
    int progress = static_cast<int>((static_cast<double>(clickCount) / levelThreshold) * 100);
    ui->levelProgressBar->setValue(progress);
    ui->levelProgressBar->setFormat(QString("%1%").arg(progress));

    ui->levelLabel->setText(QString("Level: %1").arg(level));
    int achievementProgress = levelThreshold - clickCount;
    ui->progressLabel->setText(QString("Progress: %1").arg(achievementProgress));

    if (clickCount >= nextAchievementClicks) {
        unlockAchievement(QString("Achievement: %1 clicks").arg(nextAchievementClicks));
        updateNextAchievement();
    }
}


int MainWindow::getNextAchievement()
{
    if (nextAchievementClicks == 1)
        return 1;
    else if (nextAchievementClicks == 10)
        return 10;
    else if (nextAchievementClicks == 100)
        return 100;
    else if (nextAchievementClicks == 1000)
        return 1000;
    else if (nextAchievementClicks == 10000)
        return 10000;
    else if (nextAchievementClicks == 100000)
        return 100000;
    else if (nextAchievementClicks == 1000000)
        return 1000000;

    return 0;
}

void MainWindow::updateNextAchievement()
{
    if (nextAchievementClicks == 1)
        nextAchievementClicks = 10;
    else if (nextAchievementClicks == 10)
        nextAchievementClicks = 100;
    else if (nextAchievementClicks == 100)
        nextAchievementClicks = 1000;
    else if (nextAchievementClicks == 1000)
        nextAchievementClicks = 10000;
    else if (nextAchievementClicks == 10000)
        nextAchievementClicks = 100000;
    else if (nextAchievementClicks == 100000)
        nextAchievementClicks = 1000000;
}

void MainWindow::unlockAchievement(const QString& achievement)
{
    ui->achievementsListWidget->addItem(achievement);
}
