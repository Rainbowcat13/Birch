#include "mainwindow.h"
#include "AVL_tree.h"
#include <QApplication>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
    AVL_tree tree = AVL_tree();

    for (int i = 1; i < 10; i++) {
        tree.insert(i);
    }

    for (auto elem: tree) {
        qDebug() << elem.key << " JOPA";
    }

}