#include "beginpage.h"

beginPage::beginPage(QWidget *parent){
    db.createDataBase();
    login=new loginPage(this);
    Q_UNUSED(parent);
    setFixedSize(1000,800);
    setWindowTitle("推箱子");
    setWindowIcon(QIcon(":/image/man.png"));
    player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/music/background.mp3"));
    player->play();
    button();
    connect(player, &QMediaPlayer::stateChanged, this, &beginPage::onStateChanged);
}

beginPage::~beginPage(){
    if(login!=nullptr)
    delete login;

}

//按钮
void beginPage::button(){
    loginButton();
    logOutButton();
    basicButton();
    rankListButton();
    freeModeButton();
}

//背景图片渲染
void beginPage::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/background.png");
    painter.drawPixmap(0, 0, pix);
    pix.load(":/image/b1.png");
    painter.drawPixmap(280, 280, pix);
    pix.load(":/image/b2.png");
    painter.drawPixmap(450, 260, pix);
    pix.load(":/image/b3.png");
    painter.drawPixmap(620, 280, pix);
}

//登录页面显示
void beginPage::showLoginPage(){
    if(!login->hasLogged())
    login->show();
    else{
        QLabel*msg=new QLabel(this);
        QPalette palette;
        palette.setColor(QPalette::WindowText, Qt::red);
        msg->setPalette(palette);
        msg->resize(200,100);
        msg->setFont(QFont("仿宋", 14));
        msg->setText("您已登录");
        msg->move(250,200);
        msg->show();
        QTimer::singleShot(1000, msg, &QWidget::deleteLater);
    }
}

//经典模式按钮
void beginPage::basicButton(){
    basicBtn = new QPushButton("开始游戏");
    basicBtn->setParent(this);
    basicBtn->resize(500,80);
    basicBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0.6);");
    basicBtn->setFont(QFont("仿宋", 14));
    basicBtn->move(250, 400);
    connect(basicBtn, &QPushButton::clicked,[=](){
        if(login->hasLogged()){
        m=new MainWindow(this,login->getId());
        m->show();
        }
        else{
            QLabel*msg=new QLabel(this);
            // 设置文本颜色为红色
            QPalette palette;
            palette.setColor(QPalette::WindowText, Qt::red);
            msg->setPalette(palette);
            msg->resize(150,100);
            msg->setFont(QFont("仿宋", 14));
            msg->setText("请先登录");
            msg->move(250,200);
            msg->show();
            QTimer::singleShot(1000, msg, &QWidget::deleteLater);
        }
    });
}

//账号登录按钮
void beginPage::loginButton(){
    loginBtn=new QPushButton("点击登录");
    loginBtn->setParent(this);
    loginBtn->resize(200,80);
    loginBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0.6);");
    loginBtn->setFont(QFont("仿宋", 14));
    loginBtn->move(250, 300);
    connect(loginBtn, &QPushButton::clicked, this, &beginPage::showLoginPage);
}

//退出登录按钮
void beginPage::logOutButton(){
    logOutBtn=new QPushButton("退出登录");
    logOutBtn->setParent(this);
    logOutBtn->resize(200,80);
    logOutBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0.6);");
    logOutBtn->setFont(QFont("仿宋", 14));
    logOutBtn->move(550, 300);
    connect(logOutBtn, &QPushButton::clicked,[=](){
       QLabel*msg=new QLabel(this);
       QPalette palette;
       palette.setColor(QPalette::WindowText, Qt::red);
       msg->setPalette(palette);
       msg->resize(200,100);
       msg->setFont(QFont("仿宋", 14));
       msg->move(250,200);
       QTimer::singleShot(1000, msg, &QWidget::deleteLater);
       if(login->hasLogged()){
           msg->setText("已退出登陆状态");
           login->logOut();
       }
       else msg->setText("您还未登录");
       msg->show();
    });
}

//排行榜按钮
void beginPage::rankListButton(){
    rankListBtn = new QPushButton("排行榜");
    rankListBtn->setParent(this);
    rankListBtn->resize(500,80);
    rankListBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0.6);");
    rankListBtn->setFont(QFont("仿宋", 14));
    rankListBtn->move(250, 500);
    connect(rankListBtn, &QPushButton::clicked,[=](){
        ranklist=new rankListPage(this);
        ranklist->show();
    });
}

//自主设计模式按钮
void beginPage::freeModeButton(){
    freeModeBtn = new QPushButton("自主设计模式");
    freeModeBtn->setParent(this);
    freeModeBtn->resize(500,80);
    freeModeBtn->setStyleSheet("background-color: rgba(255, 255, 255, 0.6);");
    freeModeBtn->setFont(QFont("仿宋", 14));
    freeModeBtn->move(250, 600);
    connect(freeModeBtn, &QPushButton::clicked,[=](){
          freeModel=new freeModelPage;
          freeModel->show();
    });
    freeModeBtn->show();
}

//音乐结束重新播放
void beginPage::onStateChanged(QMediaPlayer::State state){
    if (state == QMediaPlayer::StoppedState){
        player->play();
    }
}
