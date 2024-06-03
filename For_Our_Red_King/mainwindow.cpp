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
    ui->setupUi(this);//设置主菜单ui界面
    this->setWindowTitle(QString("为了红王"));
    this->setFocusPolicy(Qt::StrongFocus);     //对主窗口进行强关注
    this->setWindowIcon(QIcon(SYSTEM::icon));
    this->setFixedSize(SYSTEM::windowWidth,SYSTEM::windowHeight);             //!<设置分辨率
    mPainter = new QPainter(this);

    mGame = new Game(this,this);        //创建Game对象
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
