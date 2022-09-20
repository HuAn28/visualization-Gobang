#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QMouseEvent>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QCoreApplication>
#include <QSound>
#include "config.h"
#include "checkerboard.h"
#include "ai.h"
#include "welcome.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Init();
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void playGame();
    void turnGridLocation(int *newX, int *newY, int oldX, int oldY);
    void readNum(QString fileName);
    void addNum(int id);

private slots:
    void on_actionNewGame_triggered();
    void on_Repentance_clicked();
    void on_actionReadGame_triggered();
    void on_actionSaveGame_triggered();
    void on_sureClick_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
    int x;
    int y;
    bool true_down;
    bool ifVictory;
    Lineup id;
    Lineup victoryId;
    AI ai;
    CheckerBoard checkerboard;
    Welcome *welcome = NULL;
    int Black_num;
    int White_num;
    int Equality_num;
    QSound *clickSound;
};
#endif // MAINWINDOW_H
