
#include <QtGui>
#include "mainwindow.h"
#include "glwidget.h"
#include <QLayout>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
   // ShortCutter sc;
    /*GLWidget g1;
    g1.show();
    QGridLayout l1;
    l1.addWidget(&g1);
    QWidget MW;
    MW.setLayout(&l1);
    MW.show();*/
    return a.exec();
}
