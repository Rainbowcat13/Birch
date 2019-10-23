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
#include <QSet>
#include "AVL_tree.h"

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void renderTree();

public slots:
    void addNode();
    void deleteNode();

private:
    AVL_tree atree;
    QWidget* mCentralWidget;
    QFont mainFont;
    QLineEdit *vertex;
    QPushButton *del, *add;
    QGraphicsView* mainCanvas;
    QGraphicsScene* mainScene;

};

#endif // MAINWINDOW_H
