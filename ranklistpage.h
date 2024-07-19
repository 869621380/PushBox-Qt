#ifndef RANKLISTPAGE_H
#define RANKLISTPAGE_H
#include<Database.h>
#include<QVBoxLayout>
#include<QPainter>
#include<QLabel>

class rankListPage: public QWidget{
public:
    rankListPage(QWidget*parent);
    void paintEvent(QPaintEvent *);
    void initialize(int level);//加载当前关卡排行榜

public slots:
    void comboBoxIndexChanged(int index);//下拉框选择改变时更换排行榜数据

private:
    DataBase db;//数据库
    QComboBox *comboBox;//关卡选择下拉框

};

#endif // RANKLISTPAGE_H
