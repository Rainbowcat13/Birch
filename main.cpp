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
//    AVL_tree a;
//    int n;
//    std::cin >> n;
//    for (int i = 0; i < n; i++) {
//        int q, t;
//        std::cin >> t >> q;
//        if (t == 1) {
//            a.insert(q);
//        }
//        else {
//            a.remove(q);
//        }
//        for (auto elem = a.begin(); elem != nullptr;) {
//            std::cout << elem->key << ' ';
//            elem=elem->next();
//        }
//        std::cout << '\n';
//    }
}

/*
4
1 2
1 5
1 7
2 5

4
1 10
1 9
1 11
2 10
*/