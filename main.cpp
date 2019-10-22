#include "mainwindow.h"
#include "AVL_tree.h"
#include "RB_tree.h"
#include <QApplication>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}