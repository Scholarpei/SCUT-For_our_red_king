#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "game.h"
#include <QPainter>
#include "game.h"
#include "spritecomponent.h"
#include "standard.h"

MainWindow::MainWindow(QWidget *parent):
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//设置统计界面
    ui->StatisticWidget->hide();
    this->setWindowTitle(QString("为了红王"));
    this->setFocusPolicy(Qt::StrongFocus);     //对主窗口进行强关注
    this->setWindowIcon(QIcon(SYSTEM::icon));
    this->setFixedSize(SYSTEM::windowWidth,SYSTEM::windowHeight);             //!<设置分辨率
    mPainter = new QPainter(this);

    mGame = new Game(this,this);        //创建Game对象
}

//!数据统计界面
void MainWindow::showStatisticWidget()
{
    this->mGame->updateStatistic();
    GameStatisticInterface data = this->mGame->getLocalStatistic();

    qDebug("combo %d lo %d",data.maxCombos,mGame->mStatistic.maxCombos);
    qDebug("passlevel %d lo %d",data.maxPassLevelNumber,mGame->mStatistic.maxPassLevelNumber);
    qDebug("already %d,lo %d",data.alreadyKillMonsterNumber,mGame->mStatistic.alreadyKillMonsterNumber);

    ui->maxCombosLineEdit->setText(QString(QString::number(data.maxCombos)));
    ui->maxPassLevelNumberLineEdit->setText(QString(QString::number(data.maxPassLevelNumber)+"关"));
    ui->alreadyKillMonsterNumberLineEdit->setText(QString(QString::number(data.alreadyKillMonsterNumber)+"只"));

    ui->StatisticWidget->show();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    // qDebug("调用paintEvent msprites大小%d",mGame->mSprites.size());
    mPainter->begin(this);
    for (auto sprite:mGame->mSprites)
    {
        sprite->Draw();
    }
    mPainter->end();
}

MainWindow::~MainWindow()
{
    delete mGame;
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(!event->isAutoRepeat())
        mGame->keyPressInput(event->key());
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if(!event->isAutoRepeat())
        mGame->keyReleaseInput(event->key());
}

void MainWindow::mousePressEvent(QMouseEvent * e)
{
    mGame->mousePressInput(e);
}
void MainWindow::mouseReleaseEvent(QMouseEvent * e)
{
    mGame->mouseReleaseInput(e);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"关闭游戏event";
    this->ui->StatisticWidget->hide();
    if(mGame->mIsRuning)
        this->mGame->ExitGame(),event->ignore();//如果从右上角退出不会清除数据，因此执行ExitGame函数
    else event->accept();
}

void MainWindow::on_staBackButton_clicked()
{
    qDebug()<<"返回界面button";
    this->mGame->stop = false;
}

void MainWindow::on_staBackMainLevelButton_clicked()
{
    qDebug()<<"返回主菜单button";
    //切换关卡到主菜单并更新数据
    this->mGame->mGoToNextLevel = 1;//主菜单
    this->mGame->updateStatistic();//更新
    this->mGame->stop = false;
    this->ui->StatisticWidget->hide();
}

