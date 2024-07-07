#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent,QString id): QMainWindow(parent), ui(new Ui::MainWindow){
    currentMax=db.selecting(id);
    this->id=id;
    //打开当前窗口时禁止对其他窗口进行操作
    setWindowModality((Qt::ApplicationModal));
    ui->setupUi(this);
    //设置固定窗口
    setFixedSize(1000,800);
    setWindowTitle("推箱子");
    setWindowIcon(QIcon(":/image/kun.png"));
    initialize(1);
    button();
    checkWin();
    winMessage();
}

MainWindow::~MainWindow(){
    delete ui;
}

//资源初始化
void MainWindow::initialize(int theLevel){
    result=false;
    moveTimes=0;
    level=theLevel;
    updateRank=0;
    if(theLevel>currentMax){
        currentMax=theLevel;
        db.updateLevel(id,currentMax);
    }
    //每次关卡开始前清空栈内的移动数据
    while(!operationData.empty())operationData.pop();
    //获取地图数据
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
             initialData[i][j] = config.theData[theLevel][j][i];
             currentData[i][j]=config.theData[theLevel][j][i];
        }
    }
}

//图片资源渲染
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/image/blackground.png");
    // 画背景图
    painter.drawPixmap(0, 0, pix);
    int d = 50;
    //游戏内各类型图标渲染
    QString str;
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
                str=":image/ball.png";
                pix.load(str);
                painter.drawPixmap(d*i,d*j,pix);
            }
            else if(currentData[i][j]==4){
                person_x=i;
                person_y=j;
                str=":image/kun.png";
                pix.load(str);
                painter.drawPixmap(d*i,d*j,pix);
            }
        }
    }
    painter.setPen(Qt::white);
    QString levelMsg = QString("第 %1 关").arg(level);
    painter.drawText(QRect(35,35,105,35),levelMsg);
    QString moveMsg = QString("移动次数： %1").arg(moveTimes);
    painter.drawText(QRect(35,70,105,35),moveMsg);
}

//键盘案件响应
void MainWindow::keyReleaseEvent(QKeyEvent*event){
    //点击向上
    if(event->key() == Qt::Key_Up) {
        if(person_y!=0){
          int num=person_y-1;

          //找到第一个不是箱子的物体
          while(num>0&&currentData[person_x][num]==3){
              num--;
          }

          //只有能推得动箱子或者能移动才会运行
          if(!currentData[person_x][num] or currentData[person_x][num]==2){
              //在移动前对数据进行存储以方便回退
              QVector<int>t;
              for(int i=0;i<16;i++)t.push_back(currentData[person_x][i]);
              int tnum=100+person_x;//tnum蕴含了本次操作在哪一行，是行操作还是列操作
              operationData.push_back(QPair<int, QVector<int>>(tnum, t));//将每次操作数据进行记录
          for(int i=num;i<person_y;i++){
              currentData[person_x][i]=currentData[person_x][i+1];
          }
          currentData[person_x][person_y]=0;
          //如果物品或人物所在的地方本来是目的地，将目的地重新渲染出来
          for(int i=num;i<=person_y;i++){
              if(currentData[person_x][i]==0&&initialData[person_x][i]==2)
                  currentData[person_x][i]=2;
          }
          moveTimes++;
          person_y--;
      }
          update();
    }
  }
    //以下操作与向上移动的原理相似
    //点击向下
    if(event->key() == Qt::Key_Down) {
        if(person_y!=16){
          int num=person_y+1;
          while(num<16&&currentData[person_x][num]==3){
              num++;
          }
          //只有能推的动箱子或者能移动才会运行
          if(!currentData[person_x][num] or currentData[person_x][num]==2){
          //在移动前对数据进行存储以方便回退
          QVector<int>t;
          for(int i=0;i<16;i++)t.push_back(currentData[person_x][i]);
          int tnum=100+person_x;//tnum蕴含了本次操作在哪一行，是行操作还是列操作
          operationData.push_back(QPair<int, QVector<int>>(tnum, t));
          //移动从num位置到person_y位置的方块
          for(int i=num;i>person_y;i--){
              currentData[person_x][i]=currentData[person_x][i-1];
          }
          currentData[person_x][person_y]=0;
          for(int i=num;i>=person_y;i--){
              if(currentData[person_x][i]==0&&initialData[person_x][i]==2)
                  currentData[person_x][i]=2;
          }
          person_y++;
          moveTimes++;
      }
          update();
    }
  }
    //点击向左
    if(event->key() == Qt::Key_Left) {
        if(person_x!=0){
          int num=person_x-1;
          while(num>0&&currentData[num][person_y]==3){
              num--;
          }
        if(!currentData[num][person_y] or currentData[num][person_y]==2){
          QVector<int>t;
           for(int i=0;i<16;i++)t.push_back(currentData[i][person_y]);
          int tnum=200+person_y;
          operationData.push_back(QPair<int, QVector<int>>(tnum, t));
          for(int i=num;i<person_x;i++){
              currentData[i][person_y]=currentData[i+1][person_y];
          }
          currentData[person_x][person_y]=0;
          for(int i=num;i<=person_x;i++){
              if(currentData[i][person_y]==0&&initialData[i][person_y]==2)
                  currentData[i][person_y]=2;
          }
          moveTimes++;
          person_x--;
      }
          update();
    }
  }
    //点击向右
    if(event->key() == Qt::Key_Right) {
        if(person_x!=16){
          int num=person_x+1;
          while(num<16&&currentData[num][person_y]==3){
              num++;
          }
          if(!currentData[num][person_y] or currentData[num][person_y]==2){
              QVector<int>t;
              for(int i=0;i<16;i++)t.push_back(currentData[i][person_y]);
              int tnum=200+person_y;
              operationData.push_back(QPair<int, QVector<int>>(tnum, t));
          for(int i=num;i>person_x;i--){
              currentData[i][person_y]=currentData[i-1][person_y];
          }
          currentData[person_x][person_y]=0;
          for(int i=num;i>=person_x;i--){
              if(currentData[i][person_y]==0&&initialData[i][person_y]==2)
                  currentData[i][person_y]=2;
          }
          moveTimes++;
          person_x++;
      }
          update();
    }
  }
    //每次移动过后检查游戏是否胜利
    checkWin();
}

//侧边按钮
void MainWindow::button(){
    //上一关卡按钮
    QPushButton * lastBtn = new QPushButton("上一关卡");
    lastBtn->setParent(this);
    lastBtn->resize(120,80);
    lastBtn->setStyleSheet("background-color:gray");
    lastBtn->setFont(QFont("仿宋", 14));
    lastBtn->move(850, 100);

    connect(lastBtn, &QPushButton::clicked,[=](){
        //存在上一关卡才能点击
        if(level != MIN_LEVEL){
            initialize(level-1);
            update();
        }
    });

    //下一关卡按钮
    QPushButton * nextBtn = new QPushButton("下一关卡");
    nextBtn->setParent(this);
    nextBtn->resize(120,80);
    nextBtn->setStyleSheet("background-color:gray");
    nextBtn->setFont(QFont("仿宋", 14));
    nextBtn->move(850, 240);

    connect(nextBtn, &QPushButton::clicked,[=](){
        //只有在下一关卡已解锁的情况下才能使用
        if(level <currentMax){
            initialize(level+1);
            update();
        }
    });

    //重玩关卡按钮
    QPushButton * restartBtn = new QPushButton("重玩关卡");
    restartBtn->setParent(this);
    restartBtn->resize(120,80);
    restartBtn->setStyleSheet("background-color:gray");
    restartBtn->setFont(QFont("仿宋", 14));
    restartBtn->move(850, 380);

    connect(restartBtn, &QPushButton::clicked,[=](){
        initialize(level);
        update();
    });

    //回退一步按钮
    QPushButton * lastOpBtn = new QPushButton("回退一步");
    lastOpBtn->setParent(this);
    lastOpBtn->resize(120,80);
    lastOpBtn->setStyleSheet("background-color:gray");
    lastOpBtn->setFont(QFont("仿宋", 14));
    lastOpBtn->move(850, 520);

    connect(lastOpBtn, &QPushButton::clicked,[=](){
       if(!operationData.empty()){
       QPair<int,QVector<int>>p=operationData.top();
       operationData.pop();
       moveTimes--;
       if(p.first/100==1){
           int x=p.first%100;
           for(int i=0;i<16;i++){
               currentData[x][i]=p.second[i];
           }
       }
       else{
           int y=p.first%100;
           for(int i=0;i<16;i++){
               currentData[i][y]=p.second[i];
           }
       }}
        update();
    });

    //返回主菜单
    QPushButton * backBtn = new QPushButton("返回主菜单");
    backBtn->setParent(this);
    backBtn->resize(120,80);
    backBtn->setStyleSheet("background-color:gray");
    backBtn->setFont(QFont("仿宋", 14));
    backBtn->move(850, 660);

    connect(backBtn, &QPushButton::clicked,[=](){
        QWidget *parent = this->parentWidget();
           parent->show();// 显示父窗口
           this->close();
    });
}

//检查游戏胜利
void MainWindow::checkWin(){
    result=1;
    for(int i=0;i<16;i++){
        for(int j=0;j<16;j++){
            if(currentData[i][j]==3&&initialData[i][j]!=2)
                result=0;
        }
    }
    //获胜后检测是否能进入排行榜
    if(result){
        int rankListNum=db.getTotalCount(level);
        if(rankListNum<10){
            db.inserting(id,level,moveTimes);
            db.sortRecords(level);
            updateRank=1;
        }
        else if(rankListNum==10){
            int maxStepInRank=db.getLastStep(level);
            if(moveTimes<maxStepInRank){
                //如果该账号已经在排行榜中，检测是否需要更新
                if(db.judgeInRankList(id,level)){
                    db.inserting(id,level,moveTimes);
                }
                //否则删除排名最低的并添加当前用户进入排行榜
                else{
                    db.deleteLastRecord(level);
                    db.inserting(id,level,moveTimes);
                    updateRank=1;
                }
                //排行榜重新排序
                db.sortRecords(level);
            }
        }
        winMessage();
        if(level!=MAX_LEVEL){
            level++;
            initialize(level);
        }
    }
     update();
}

//胜利消息弹窗
void MainWindow::winMessage(){
        if (result) {
            QMessageBox msgBox;
            msgBox.setStyleSheet("QLabel{"
                                 "min-width:300px;"
                                 "min-height:150px;"
                                 "}");
            QString msg="恭喜通过第"+ QString::number(level) + "关\n共用："+QString::number(moveTimes)+"步";
            if(updateRank)msg+="\n恭喜您进入第 "+QString::number(level)+" 关排行榜前十";
            if(level==MAX_LEVEL)msg+="\n恭喜你已通过全部关卡";
            msgBox.setWindowTitle("message");
            msgBox.setText(msg);
            msgBox.setWindowIcon(QIcon(":/image/kun.png"));
            msgBox.exec();
        }
}
