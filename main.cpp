#include "mainwindow.h"
#include <QToolBar>
#include <QApplication>
#include <QAction>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}