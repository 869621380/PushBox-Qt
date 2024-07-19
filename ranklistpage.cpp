#include "ranklistpage.h"


rankListPage::rankListPage(QWidget *parent){
    setWindowModality(Qt::ApplicationModal);
    Q_UNUSED(parent);
    setFixedSize(1000, 800);
    setWindowTitle("排行榜");
    setWindowIcon(QIcon(":/image/man.png"));

    QComboBox *comboBox = new QComboBox(this);
    comboBox->addItem("关卡 1");
    comboBox->addItem("关卡 2");
    comboBox->addItem("关卡 3");
    comboBox->addItem("关卡 4");
    comboBox->addItem("关卡 5");
    comboBox->addItem("关卡 6");
    comboBox->addItem("关卡 7");
    comboBox->addItem("关卡 8");
    comboBox->addItem("关卡 9");
    comboBox->addItem("关卡 10");


    comboBox->setFixedSize(200, 30);
    comboBox->move(400,20);
    connect(comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &rankListPage::comboBoxIndexChanged);

    initialize(1);

}

//图片渲染
void rankListPage::paintEvent(QPaintEvent *){
   QPainter painter(this);
   QPixmap pix;

   pix.load(":/image/background2.png");
   painter.drawPixmap(0, 0, pix);
   pix.load(":/image/bg.png");
   painter.setOpacity(0.7);
   painter.drawPixmap(150, 100, pix);
}

//初始化
void rankListPage::initialize(int level) {
    //删除之前创建的所有 label
    QList<QLabel*> labels = findChildren<QLabel*>();
    for (QLabel* label : labels) {
        delete label;
    }
    //插入新的 label
    QVector<QString> idData = db.findUserId(level);
    QVector<int> stepData = db.findUserStep(level);

    QLabel *rankLabel = new QLabel(this);
    rankLabel->setFixedWidth(200);
    rankLabel->setFixedHeight(60);
    rankLabel->setText("排名");
    rankLabel->setFont(QFont("黑体", 12));
    rankLabel->setStyleSheet("color: black;");
    rankLabel->move(200, 40);
    rankLabel->show();

    QLabel *idLabel = new QLabel(this);
    idLabel->setFixedWidth(200);
    idLabel->setFixedHeight(60);
    idLabel->setText("玩家");
    idLabel->setFont(QFont("黑体", 12));
    idLabel->setStyleSheet("color: black;");
    idLabel->move(400, 40);
    idLabel->show();

    QLabel *stepLabel = new QLabel(this);
    stepLabel->setFixedWidth(200);
    stepLabel->setFixedHeight(60);
    stepLabel->setText("最小步数");
    stepLabel->setFont(QFont("黑体", 12));
    stepLabel->setStyleSheet("color: black;");
    stepLabel->move(575, 40);
    stepLabel->show();

    int totalCount = db.getTotalCount(level);
    for (int i = 1; i <= totalCount; i++) {
        QLabel *rankLabel = new QLabel(this);
        rankLabel->setFixedWidth(200);
        rankLabel->setFixedHeight(60);
        rankLabel->setText(QString::number(i));
        rankLabel->setFont(QFont("黑体", 12));
        //rankLabel->setStyleSheet("color: white;");
        rankLabel->move(200, 70 * i+20);
        rankLabel->show();

        QLabel *idLabel = new QLabel(this);
        idLabel->setFixedWidth(200);
        idLabel->setFixedHeight(60);
        idLabel->setText(idData[i - 1]);
        idLabel->setFont(QFont("黑体", 12));
        //idLabel->setStyleSheet("color: white;");
        idLabel->move(400, 70 * i+20);
        idLabel->show();

        QLabel *stepLabel = new QLabel(this);
        stepLabel->setFixedWidth(200);
        stepLabel->setFixedHeight(60);
        stepLabel->setText(QString::number(stepData[i - 1]));
        stepLabel->setFont(QFont("黑体", 12));
        //stepLabel->setStyleSheet("color: white;");
        stepLabel->move(600, 70 * i+20);
        stepLabel->show();
    }
    if(totalCount==0){
        QLabel *NoDataLabel = new QLabel(this);
        NoDataLabel->setFixedWidth(300);
        NoDataLabel->setFixedHeight(60);
        NoDataLabel->setText("当前关卡暂无人上榜");
        NoDataLabel->setFont(QFont("黑体", 12));
        //NoDataLabel->setStyleSheet("color: white;");
        NoDataLabel->move(350, 200);
        NoDataLabel->show();
    }
}

//下拉框选择改变时更换排行榜数据
void rankListPage::comboBoxIndexChanged(int index) {
    initialize(index + 1);
}
