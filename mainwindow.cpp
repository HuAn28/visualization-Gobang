#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
    welcome = new Welcome;
    welcome->show(); // 打开欢迎页
    // 监听欢迎页按钮的信号
    connect(welcome, &Welcome::toMain, this, [=](){
        welcome->hide();
        this->show();
    });

    // 落子音效
    clickSound = new QSound(":/music/luoZi.wav", this);

    // 读取胜负平局数
    // 获取程序当前运行目录
    QString fileName = QCoreApplication::applicationDirPath() + "/date.txt";
    qDebug() << fileName;
    // 读取
    readNum(fileName);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    true_down = true;
    ifVictory = false;
    victoryId = None;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 25, QPixmap(":/img/checkerboard.png"));
    for(int i = 0; i < checkerboard.GetRouteLen(); i++) {
        if (checkerboard.route[i].GetPlayerId() == White) {
            painter.drawPixmap(checkerboard.route[i].GetLocationX() * 28 + 20 - checkerboard.white_piece_img.width() / 2,
                               checkerboard.route[i].GetLocationY() * 28 + 40 - checkerboard.white_piece_img.height() / 2,
                               checkerboard.white_piece_img);
        }
        else if (checkerboard.route[i].GetPlayerId() == Black) {
            painter.drawPixmap(checkerboard.route[i].GetLocationX() * 28 + 20 - checkerboard.white_piece_img.width() / 2,
                               checkerboard.route[i].GetLocationY() * 28 + 40 - checkerboard.white_piece_img.height() / 2,
                               checkerboard.black_piece_img);
        }
        else {
            qDebug() << "代码有错误";
        }
    }
    if(true_down == false) {
        if(x == 0) {
            return;
        }
        if(y == 0) {
            return;
        }
        QBrush brush(Qt::red);
        if (id == White) {
            painter.setBrush(brush);
            painter.drawEllipse(QPoint(x * 28 + 20, y * 28 + 40), checkerboard.white_piece_img.width()/2, checkerboard.white_piece_img.height()/2);
            painter.drawPixmap(x * 28 + 20 - checkerboard.white_piece_img.width() / 2,
                               y * 28 + 40 - checkerboard.white_piece_img.height() / 2,
                               checkerboard.white_piece_img);
        }
        else if (id == Black) {
            painter.setBrush(brush);
            painter.drawEllipse(QPoint(x * 28 + 20, y * 28 + 40), checkerboard.white_piece_img.width()/2, checkerboard.white_piece_img.height()/2);
            painter.drawPixmap(x * 28 + 20 - checkerboard.white_piece_img.width() / 2,
                               y * 28 + 40 - checkerboard.white_piece_img.height() / 2,
                               checkerboard.black_piece_img);
        }
        else {

        }
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int xx, yy;
    true_down = false;
    id = None;
    if(checkerboard.GetRouteLen() == 0) {
        id = Black;
    }
    else if (checkerboard.GetRouteLen() > 0)
    {
        if(checkerboard.route[checkerboard.GetRouteLen() -1].GetPlayerId() == White) {
            id = Black;
        }
        else if (checkerboard.route[checkerboard.GetRouteLen() -1].GetPlayerId() == Black) {
            id = White;
        }
        else {
            qDebug() << "代码有错误";
        }
    }
    else {
        qDebug() << "代码有错误";
    }
    turnGridLocation(&xx, &yy, event->x(), event->y());

    if(checkerboard.GetNodeId(xx, yy) == None) {
        x = xx;
        y = yy;
        update();
    }
    else {
        return;
    }

    // 读取胜负平局数
    // 获取程序当前运行目录
    QString fileName = QCoreApplication::applicationDirPath() + "/date.txt";
    qDebug() << fileName;
    // 读取
    readNum(fileName);
}

void MainWindow::readNum(QString fileName)
{
    QFile file(fileName);
    // 设置打开方式
    bool isOpen = file.open(QIODevice::ReadOnly);
    if(isOpen == false) {
        qDebug() << "没打开";
        file.open(QIODevice::WriteOnly);
        file.write("000\n000\n000");
        file.close();
    }
    else
    {
        qDebug() << "打开了";
        QByteArray array;

        int i = 0;
        while(!file.atEnd())
        {
            array = file.readLine();
            if(i == 0) {
                Black_num = (int(array[0]) - 48) * 100 + (int(array[1]) - 48) * 10 + (int(array[2]) - 48);
            }
            else if (i == 1) {
                White_num = (int(array[0]) - 48) * 100 + (int(array[1]) - 48) * 10 + (int(array[2]) - 48);
            }
            else if (i == 2) {
                Equality_num = (int(array[0]) - 48) * 100 + (int(array[1]) - 48) * 10 + (int(array[2]) - 48);
            }
            i++;
        }
        file.close();

        // 显示胜负平局数
        ui->Bl->setNum(Black_num);
        ui->Wh->setNum(White_num);
        ui->Eq->setNum(Equality_num);
    }
}

void MainWindow::addNum(int id)
{
    if(id == 0) {  // 黑色
        Black_num++;
    }
    else if(id == 1) {  // 白色
        White_num++;
    }
    else if(id == 2) {  // 平局
        Equality_num++;
    }
    qDebug() << "4:" << Black_num;
    QString fileName = QCoreApplication::applicationDirPath() + "/date.txt";
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    char text[] = "000\n000\n000";
    text[0] = char(48 + Black_num / 100);
    text[1] = char(48 + Black_num % 100 / 10);
    text[2] = char(48 + Black_num % 10);

    qDebug() << "5:" << text[0] << "," << text[1] << "," << text[2];

    text[4] = char(48 + White_num / 100);
    text[5] = char(48 + White_num % 100 / 10);
    text[6] = char(48 + White_num % 10);

    text[8] = char(48 + Equality_num / 100);
    text[9] = char(48 + Equality_num / 10);
    text[10] = char(48 + Equality_num % 10);

    file.write(text);
    file.close();

    // 显示胜负平局数
    ui->Bl->setNum(Black_num);
    ui->Wh->setNum(White_num);
    ui->Eq->setNum(Equality_num);
}

void MainWindow::playGame()
{
    ifVictory = false;
    true_down = true;
    victoryId = None;
    checkerboard.NewGame();
    update();
}

void MainWindow::turnGridLocation(int *newX, int *newY, int oldX, int oldY)
{
    *newX = (oldX - 32 + 28) / 28;
    *newY = (oldY - 30) / 28;
    if(*newX < 1 || *newY < 1 || *newX > 19 || *newY > 19)
    {
        *newX = 0;
        *newY = 0;
    }
}


void MainWindow::on_actionNewGame_triggered()
{
    if(QMessageBox::Yes == QMessageBox::question(this, "ques", "是否打开一个新的游戏")) {
        qDebug() << "新游戏";
        playGame();
    }
    else {
        return;
    }
}

void MainWindow::on_Repentance_clicked()
{
    true_down = true;
    if(checkerboard.GetRouteLen() > 0) {
        if(checkerboard.route[checkerboard.GetRouteLen() -1].GetPlayerId() == White) {
            ui->labelPiece->setText("白棋");
        }
        else if (checkerboard.route[checkerboard.GetRouteLen() -1].GetPlayerId() == Black) {
            ui->labelPiece->setText("黑棋");
        }
        else {
            qDebug() << "代码有错误";
        }
        checkerboard.RepentStep();
        update();
    }
    else if(checkerboard.GetRouteLen() == 0) {
        QMessageBox::critical(this, "crit", "不能再撤回步数了");
    }
    else {
        qDebug() << "代码有错误";
    }
}


void MainWindow::on_actionReadGame_triggered()
{
    if(QMessageBox::Yes == QMessageBox::question(this, "ques", "是否加载存档游戏")) {
        qDebug() << "游戏存档";
        playGame();
        QString path = QFileDialog::getOpenFileName(this, "打开文件", "D:/");
        if(path == "") {
            qDebug() << "读取失败";
            return;
        }
        if(checkerboard.ReadGame(path)== true) {
            qDebug() << "读取成功";
            update();
            // 胜负判断函数
            if(checkerboard.JudgmentVOD() == true) {
                if(ifVictory == false) {
                    ifVictory = true;
                }
                if(QMessageBox::Yes == QMessageBox::question(this, "ques", "棋局已经有胜利方！是否打开一个新的游戏？")) {
                    playGame();
                }
            }
        }
    }
    else {
        return;
    }
}

void MainWindow::on_actionSaveGame_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, "打开文件", "D:/");
    if(path == "") {
        qDebug() << "保存失败";
        return;
    }
    QFile file(path);
    if(victoryId == White) {
        // 设置打开方式
        file.open(QIODevice::WriteOnly);
        file.write("White\n");
        file.close();
    }
    else if(victoryId == Black) {
        // 设置打开方式
        file.open(QIODevice::WriteOnly);
        file.write("Black\n");
        file.close();
    }
    else {
        // 设置打开方式
        file.open(QIODevice::WriteOnly);
        file.write("None\n");
        file.close();
    }
    if(checkerboard.SaveGame(path) == true) {
        qDebug() << "保存成功";
    }
}

void MainWindow::on_sureClick_clicked()
{
    // 检错处理
    if(y > 100)
    {
        return;
    }
    if(x > 100)
    {
        return;
    }

    qDebug() << x << y;
    if(checkerboard.PlaceNode(x, y, id) == true) {
        if(checkerboard.route[checkerboard.GetRouteLen() -1].GetPlayerId() == White) {
            ui->labelPiece->setText("黑棋");
            clickSound->play();
        }
        else if (checkerboard.route[checkerboard.GetRouteLen() -1].GetPlayerId() == Black) {
            ui->labelPiece->setText("白棋");
            clickSound->play();
        }
        else {
            qDebug() << "代码有错误";
        }
        update();
    }
    true_down = true;
    if(victoryId != None) {
        return;
    }

    // 胜负判断函数
    if(checkerboard.JudgmentVOD() == true) {
        if(ifVictory == false) {
            ifVictory = true;
            victoryId = checkerboard.route[checkerboard.GetRouteLen() -1].GetPlayerId();
            // 胜利方标记在victoryId这里面了，可以保存到文件，也可以显示在窗口里面
        }
        if(victoryId == White) {
            addNum(1);
        }
        if(victoryId == White && QMessageBox::Yes == QMessageBox::question(this, "ques", "白色胜利！是否打开一个新的游戏？")) {
            playGame();
        }

        if(victoryId == Black) {
            addNum(0);
        }
        if(victoryId == Black && QMessageBox::Yes == QMessageBox::question(this, "ques", "黑色胜利！是否打开一个新的游戏？")) {
            playGame();
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    id = None;
    if(checkerboard.GetRouteLen() == 0) {
        id = Black;
    }
    else if (checkerboard.GetRouteLen() > 0)
    {
        if(checkerboard.route[checkerboard.GetRouteLen() -1].GetPlayerId() == White) {
            id = Black;
        }
        else if (checkerboard.route[checkerboard.GetRouteLen() -1].GetPlayerId() == Black) {
            id = White;
        }
        else {
            qDebug() << "代码有错误";
        }
    }
    else {
        qDebug() << "代码有错误";
    }
    ai.InitScore(checkerboard);
    ai.ActionByAI(&x, &y);
    true_down = false;
    update();
}

void MainWindow::on_pushButton_5_clicked()
{
    QString fileName = QCoreApplication::applicationDirPath() + "/date.txt";
    qDebug() << "1:" << Black_num;
    readNum(fileName);
    if(QMessageBox::Yes == QMessageBox::question(this, "ques", "是否选择平局？")) {
        ifVictory = true;
        victoryId = None;
        addNum(2);
        if(QMessageBox::Yes == QMessageBox::question(this, "ques", "是否开始新的游戏？")) {
            playGame();
        }
    }
    qDebug() << "2:" << Black_num;
    readNum(fileName);
    qDebug() << "3:" << Black_num;
}

void MainWindow::on_pushButton_6_clicked()
{
    QString fileName = QCoreApplication::applicationDirPath() + "/date.txt";
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write("000\n000\n000");
    file.close();

    Black_num = 0;
    White_num = 0;
    Equality_num = 0;

    // 显示胜负平局数
    ui->Bl->setNum(Black_num);
    ui->Wh->setNum(White_num);
    ui->Eq->setNum(Equality_num);
}
