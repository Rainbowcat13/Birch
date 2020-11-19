#include "mainwindow.h"
#include "AVL_tree.h"
#include "RB_tree.h"
#include "Splay_tree.h"
#include <QApplication>
#include <iostream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
//    AVL_tree a = AVL_tree();
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
//        for (auto elem = a.begin(); elem != a.end(); elem=elem->next()) {
//            std::cout << elem->key << ' ';
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

3
1 2
1 3
1 10

3
1 6
1 5
2 5

3
1 3
1 4
1 1

4
1 2
1 4
1 8
1 1

6 4 7 9 3 -1 1 0 30 5 2
6 1 5

ADD: -1 0 1 2 3 4 5 6 7 9 30
 DEL: 5 1 6
*/