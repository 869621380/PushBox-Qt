#ifndef DATA_H
#define DATA_H

#include<QVector>
#include<QObject>
#include <QMap>

class data{
public:
    data(QObject *parent = nullptr); //添加基本地图数据
    data(int type=0);//自主设计模式的空白地图
    QMap<int,QVector<QVector<int>>>theData;    //基本地图数据
private:
    void  insert(int index,int checkpoint[16][16]);//地图数据插入
};

#endif // DATA_H
