#include <QApplication>
#include"beginpage.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    class::beginPage w;
    w.show();
    return a.exec();
}
