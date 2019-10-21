#include "mainwindow.h"
#include "AVL_tree.h"
#include "RB_tree.h"
#include <QApplication>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
    AVL_tree atree = AVL_tree();
    RB_tree rtree = RB_tree();

    for (int i = 1; i < 10; i++) {
        atree.insert(i);
        rtree.insert(i);
    }

//    atree.remove(3);
//    atree.remove(9);
//    atree.remove(1);

//    for (auto it = rtree.begin(); it != nullptr; it=it->next()) {
//        qDebug() << it->key;
//    }

}