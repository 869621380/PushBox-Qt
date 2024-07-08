#ifndef RANKLISTPAGE_H
#define RANKLISTPAGE_H
#include<Database.h>
#include<QVBoxLayout>
#include <QObject>
#include <QWidget>

class rankListPage: public QWidget{
public:
    rankListPage(QWidget*parent);
    void paintEvent(QPaintEvent *);
    void initialize(int level);//加载当前关卡排行榜
public slots:
    void comboBoxIndexChanged(int index);
private:
    DataBase db;//数据库
    QVBoxLayout *mainLayout;//布局管理器
    QComboBox *comboBox;
};

#endif // RANKLISTPAGE_H
