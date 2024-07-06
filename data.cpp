#include "data.h"

data::data(QObject *parent){

    Q_UNUSED(parent);

    //关卡1
    int checkpoint1[16][16] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,2,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,1,0,1,1,1,1,0,0,0,0},
        {0,0,0,0,1,1,1,3,0,3,2,1,0,0,0,0},
        {0,0,0,0,1,2,0,3,4,1,1,1,0,0,0,0},
        {0,0,0,0,1,1,1,1,3,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,2,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    insert(1,checkpoint1);

    //关卡2
    int checkpoint2[16][16] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0},
        {0,0,0,0,1,4,0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,1,0,3,3,1,0,1,1,1,0,0,0},
        {0,0,0,0,1,0,3,0,1,0,1,2,1,0,0,0},
        {0,0,0,0,1,1,1,0,1,1,1,2,1,0,0,0},
        {0,0,0,0,0,1,1,0,0,0,0,2,1,0,0,0},
        {0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0},
        {0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,0},
        {0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
    insert(2,checkpoint2);

    //关卡3
    int checkpoint3[16][16] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,4,3,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,3,0,1,1,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,3,0,1,0,0,0,0,0,0},
    {0,0,0,0,1,2,3,0,0,1,0,0,0,0,0,0},
    {0,0,0,0,1,2,2,0,2,1,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };
    insert(3,checkpoint3);

}

//地图数据插入
void data::insert(int index,int checkpoint[16][16]){
    QVector<QVector<int>> v;
    for(int i = 0 ; i < 16 ; i++){
        QVector<int> t;
        for(int j = 0 ; j < 16 ; j++)
            t.push_back(checkpoint[i][j]);
        v.push_back(t);
    }
    theData.insert(index,v);
}
