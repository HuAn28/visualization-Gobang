#include "welcome.h"
#include <QPushButton>
#include <QLabel>
#include <QDebug>

Welcome::Welcome(QWidget *parent) : QMainWindow(parent)
{
    resize(400, 500);
    setMinimumSize(400, 500);
    setMaximumSize(400, 500);
    setWindowTitle("开始五子棋游戏");

    // 创建一个按钮
    QPushButton* btn = new QPushButton("开始游戏", this);
    // 移动btn按钮
    btn->move(160, 330);
    btn->setFixedSize(80, 30);

    // 选择关卡按钮音效
    QSound *chooseSound = new QSound(":/music/TapButtonSound.wav", this);

    connect(btn, &QPushButton::clicked, [=](){
        qDebug() << "点击了返回按钮";
        chooseSound->play();
        this->toMain();
    });
}

void Welcome::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/img/bg.jpg");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
