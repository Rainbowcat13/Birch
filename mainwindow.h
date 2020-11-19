#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <set>
#include <QKeyEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <stdexcept>
#include <QString>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QComboBox>
#include <QSet>
#include <QPoint>
#include "AVL_tree.h"
#include "RB_tree.h"
#include "Splay_tree.h"

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void renderTree();
    void renderLines(Node* p);

public slots:
    void addNode();
    void deleteNode();
    void changeCurrentTree(int type);
    void clearCanvas();

private:
    AVL_tree atree;
    RB_tree rtree;
    Splay_tree stree;
    QWidget* mCentralWidget;
    QFont mainFont;
    QPen mainPen;
    QLineEdit *vertex;
    QPushButton *del, *add, *clear;
    QGraphicsView* mainCanvas;
    QGraphicsScene* mainScene;
    QComboBox* treeKind;
    int currentTree;

};

#endif // MAINWINDOW_H
