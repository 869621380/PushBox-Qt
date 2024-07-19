#include "freemodelPage.h"

freeModelPage::freeModelPage(QWidget *parent) : QWidget(parent){
    Q_UNUSED(parent);
    setWindowModality(Qt::ApplicationModal);
    setWindowIcon(QIcon(":/image/man.png"));
    setFixedSize(1000, 800);
    setWindowTitle("自主开发模式");
    setWindowIcon(QIcon(":/image/kun.png"));
    initialize();
    fillAllButton();
    startButton();
}

//资源初始化
void freeModelPage::initialize(){
    selected=11;
    config=new class::data(0);
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
             initialData[i][j] = config->theData[0][j][i];
             currentData[i][j]=config->theData[0][j][i];
        }
    }
    QLabel *message = new QLabel(this);
    message->setFixedWidth(300);
    message->setFixedHeight(60);
    message->setText("点击图标选中填充物\n点击格子进行填充");
    message->setFont(QFont("黑体", 10));
    message->setStyleSheet("color: black;");
    message->move(815, 50);
    message->show();

}

//图片渲染
void freeModelPage::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/whiteground.png");
    painter.drawPixmap(0, 0, pix);
    int d = 50;
    //游戏内各类型图标渲染
    QString str;
    pix.load(":image/floor.png");
    painter.drawPixmap(900,125,pix);
    pix.load(":image/wall.png");
    painter.drawPixmap(900,225,pix);
    pix.load(":image/des.png");
    painter.drawPixmap(900,325,pix);
    pix.load(":image/balls.png");
    painter.drawPixmap(900,425,pix);
    pix.load(":image/man.png");
    painter.drawPixmap(900,525,pix);

    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            if(currentData[i][j]==0){
                str=":image/floor.png";
                pix.load(str);
                painter.drawPixmap(d*i,d*j,pix);
            }
            else if(currentData[i][j]==1){
                str=":image/wall.png";
                pix.load(str);
                painter.drawPixmap(d*i,d*j,pix);
            }
            else if(currentData[i][j]==2){
                str=":image/des.png";
                pix.load(str);
                painter.drawPixmap(d*i,d*j,pix);
            }
            else if(currentData[i][j]==3){
                str=":image/balls.png";
                pix.load(str);
                painter.drawPixmap(d*i,d*j,pix);
            }
            else if(currentData[i][j]==4){
                str=":image/man.png";
                pix.load(str);
                painter.drawPixmap(d*i,d*j,pix);
            }
        }
    }
    painter.setFont(QFont("黑体"));
    QString msg = "地板：";
    painter.drawText(QRect(825,145,105,35),msg);
    msg="墙壁：";
    painter.drawText(QRect(825,245,105,35),msg);
    msg="目的地：";
    painter.drawText(QRect(825,345,105,35),msg);
    msg="箱子：";
    painter.drawText(QRect(825,445,105,35),msg);
    msg="人物：";
    painter.drawText(QRect(825,545,105,35),msg);
}

//鼠标点击
void freeModelPage::mousePressEvent(QMouseEvent* event){
    if (event->button() == Qt::LeftButton) {
            QPoint clickPos = event->pos();
            if (clickPos.x() >= 900 && clickPos.x() <= 900+50 && clickPos.y() >= 125 && clickPos.y() <= 125+50) {
                selected=0;
            }
            else if (clickPos.x() >= 900 && clickPos.x() <= 900+50 && clickPos.y() >= 225 && clickPos.y() <= 225+50) {
                selected=1;
            }
            else if (clickPos.x() >= 900 && clickPos.x() <= 900+50 && clickPos.y() >= 325 && clickPos.y() <= 325+50) {
                selected=2;
            }
            else if (clickPos.x() >= 900 && clickPos.x() <= 900+50 && clickPos.y() >= 425 && clickPos.y() <= 425+50) {
                selected=3;
            }
            else if (clickPos.x() >= 900 && clickPos.x() <= 900+50 && clickPos.y() >= 525 && clickPos.y() <= 525+50) {
                selected=4;
            }
            else if(clickPos.x()>=50&&clickPos.x()<750&&clickPos.y()>=50&&clickPos.y()<750){
                currentData[clickPos.x()/50][clickPos.y()/50]=selected;
                update();
            }
        }
}
void freeModelPage::fillAllButton(){
    fillAllBtn = new QPushButton("一键填充");
    fillAllBtn->setParent(this);
    fillAllBtn->resize(120,80);
    fillAllBtn->setStyleSheet("background-color:gray");
    fillAllBtn->setFont(QFont("仿宋", 14));
    fillAllBtn->move(840, 615);

    connect(fillAllBtn, &QPushButton::clicked,[=](){
        for(int i=0;i<16;i++){
            for(int j=0;j<16;j++){
                if(currentData[i][j]==11)
                    currentData[i][j]=0;
            }
        }
        update();
    });
    fillAllBtn->show();
}

void freeModelPage::startButton(){
    startBtn = new QPushButton("开始游戏");
    startBtn->setParent(this);
    startBtn->resize(120,80);
    startBtn->setStyleSheet("background-color:gray");
    startBtn->setFont(QFont("仿宋", 14));
    startBtn->move(840, 700);
    connect(startBtn, &QPushButton::clicked,[=](){
        if(!checkRight()){
              QMessageBox::critical(this, "Validation Failed", "关卡设计不合理，请重新尝试");
        }
        else{
            MainWindow*m=new MainWindow(this,currentData);
            m->show();
        }
    });
}

bool freeModelPage::checkRight(){
    int numOfBall=0;
    int numOfDes=0;
    int numOfKun=0;
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            if(currentData[i][j]==4)numOfKun++;
            else if(currentData[i][j]==2)numOfDes++;
            else if(currentData[i][j]==3)numOfBall++;
            else if(currentData[i][j]==11)return false;
        }
    }
    if(numOfKun!=1)return false;
    else if(numOfDes!=numOfBall or numOfDes<1)return false;
    return true;
}
