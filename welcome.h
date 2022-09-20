#ifndef WELCOME_H
#define WELCOME_H

#include <QMainWindow>
#include <QPainter>
#include <QSound>  // 播放声音的头文件，需要在pro里面加multimedia才能用

class Welcome : public QMainWindow
{
    Q_OBJECT
public:
    explicit Welcome(QWidget *parent = nullptr);
    // 绘图事件
    void paintEvent(QPaintEvent *);

signals:
    // 写一个自定义信号，告诉主场景，欢迎页要跳转主场景
    void toMain();
};

#endif // WELCOME_H
