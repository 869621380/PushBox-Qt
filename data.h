#ifndef DATA_H
#define DATA_H
#include <QMap>
#include<QVector>
#include<QObject>
class data
{
public:
    explicit data(QObject *parent = nullptr);
    //添加基本地图数据
    void  insert(int index,int checkpoint[16][16]);
    //基本地图数据
    QMap<int,QVector<QVector<int>>>theData;
private:
};

#endif // DATA_H
