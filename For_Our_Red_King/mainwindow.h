#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
//#include "standard.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QPainter* mPainter;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
    void paintEvent(QPaintEvent *event);

private:
    Ui::MainWindow *ui;
    class Game* mGame;
};
#endif // MAINWINDOW_H
