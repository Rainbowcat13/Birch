#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    // Set main window design
    setFixedSize(1366, 768);
    setWindowTitle(QString("Trees"));
    setStyleSheet("MainWindow{background-color: rgb(176, 224, 230)};");

    mainScene = new QGraphicsScene();
    mainCanvas = new QGraphicsView(mainScene);

    // Created main and default widgets
    mCentralWidget = new QWidget;
    mainFont = QFont("Arial", 12, QFont::Bold);
    atree = AVL_tree();

    // jopa1
    del = new QPushButton("delete");
    del->setFont(mainFont);
    del->setStyleSheet("background-color: rgb(255, 192, 203);");
    connect(del, SIGNAL(clicked()), this, SLOT(deleteNode()));

    // jopa2
    add = new QPushButton("add");
    add->setFont(mainFont);
    add->setStyleSheet("background-color: rgb(255, 192, 203);");
    connect(add, SIGNAL(clicked()), this, SLOT(addNode()));


    //jopa3
    vertex = new QLineEdit;
    vertex->setFont(mainFont);
    vertex->setMaxLength(10);


    // Configured layout and added all widgets
    auto mainLayout = new QGridLayout;
    mainLayout->addWidget(mainCanvas, 0, 0, 100, 100);
    mainLayout->addWidget(vertex, 0, 100, 5, 10);
    mainLayout->addWidget(add, 5, 100, 10, 10);
    mainLayout->addWidget(del, 15, 100, 10, 10);

    mCentralWidget->setLayout(mainLayout);
    setCentralWidget(mCentralWidget);
}

void MainWindow::addNode() {
    //qDebug() << "ADD JOPA";
    int key;
    try {
        key = vertex->text().toInt();
    }
    catch(...) {
        return;
    }
    qDebug() << key;
    try {
        atree.insert(key);
    }
    catch(std::invalid_argument) {
        return;
    }
    renderTree();
}

void MainWindow::deleteNode() {
    //qDebug() << "DEL JOPA";
    int key;
    try {
        key = vertex->text().toInt();
    }
    catch(...) {
        return;
    }
    if (atree.find(key) == nullptr) {
        return;
    }
    qDebug() << key;
    qDebug() << "PIZDA";
    try {
        atree.remove(key);
    }
    catch(std::invalid_argument) {
        return;
    }
    renderTree();
}

void MainWindow::renderTree() {
    qDebug() << "NAHUY";
    mainScene->clear();
    qDebug() << "AAA";
    for (auto elem = atree.begin(); elem != nullptr; elem=elem->next()) {
        auto e = new QGraphicsEllipseItem(elem->key * 20, 200, 20, 20);
        auto t = new QGraphicsTextItem(QString::number(elem->key));
        t->setFont(mainFont);
        t->setX(elem->key * 20);
        qDebug() << elem->h;
        t->setY(elem->h * 20);
        // mainScene->addItem(e);
        mainScene->addItem(t);
    }
//    for (auto elem: nodes) {
//        qDebug() << elem.node->key << " JOPA ";
//    }
//    qDebug() << "HUY";
//    for (auto elem = atree.begin(); elem != nullptr; elem=elem->next()) {
//        qDebug() << elem->key << " PIZDA ";
//    }
}

