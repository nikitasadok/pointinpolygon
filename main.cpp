#include "drawer.h"
#include "mainwindow.h"
#include "beachline.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow d;
    d.show();
    return a.exec();
}
