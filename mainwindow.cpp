#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    // Set main window design
    setFixedSize(1366, 768);
    setWindowTitle(QString("Trees"));
    setStyleSheet("MainWindow{background-color: rgb(176, 224, 230)};");

    mainScene = new QGraphicsScene();
    mainScene->setBackgroundBrush(QColor(255, 248, 220));
    mainCanvas = new QGraphicsView(mainScene);

    // Created main and default widgets
    mCentralWidget = new QWidget;
    mainFont = QFont("Arial", 12, QFont::Bold);
    mainPen = QPen(Qt::black, 3);
    atree = AVL_tree();
    rtree = RB_tree();
    stree = Splay_tree();
    currentTree = 0;

    del = new QPushButton("delete");
    del->setFont(mainFont);
    del->setStyleSheet("background-color: rgb(255, 192, 203);");
    connect(del, SIGNAL(clicked()), this, SLOT(deleteNode()));

    add = new QPushButton("add");
    add->setFont(mainFont);
    add->setStyleSheet("background-color: rgb(255, 192, 203);");
    connect(add, SIGNAL(clicked()), this, SLOT(addNode()));

    clear = new QPushButton("clear");
    clear->setFont(mainFont);
    clear->setStyleSheet("background-color: rgb(255, 192, 203);");
    connect(clear, SIGNAL(clicked()), this, SLOT(clearCanvas()));

    treeKind = new QComboBox;
    treeKind->addItem("AVL");
    treeKind->addItem("Red-black");
    treeKind->addItem("Splay");
    treeKind->setStyleSheet("QComboBox{background-color: rgb(192, 192, 192);"
                            "selection-background-color: rgb(192, 192, 192);"
                            "selection-color: black;"
                            "}");
    treeKind->setFont(mainFont);
    connect(treeKind, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeCurrentTree(int)));


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
    mainLayout->addWidget(clear, 25, 100, 10, 10);\
    mainLayout->addWidget(treeKind, 35, 100, 10, 10);


    mCentralWidget->setLayout(mainLayout);
    setCentralWidget(mCentralWidget);
}

void MainWindow::addNode() {
    int key;
    try {
        key = vertex->text().toInt();
    }
    catch(...) {
        return;
    }
    try {
        if (currentTree == 0) {
            atree.insert(key);
        }
        if (currentTree == 1) {
            rtree.insert(key);
        }
        if (currentTree == 2) {
            stree.insert(key);
        }
    }
    catch(std::invalid_argument) {
        return;
    }
    renderTree();
    if (currentTree == 0) {
        renderLines(atree.get_tree());
    }
    else if (currentTree == 1) {
        renderLines(rtree.get_tree());
    }
    else {
        renderLines(stree.get_tree());
    }
}

void MainWindow::deleteNode() {
    int key;
    try {
        key = vertex->text().toInt();
    }
    catch(...) {
        return;
    }
    if (currentTree == 0 && atree.find(key) == nullptr) {
        return;
    }
    if (currentTree == 1 && rtree.find(key) == nullptr) {
        return;
    }
    if (currentTree == 2 && stree.find(key) == nullptr) {
        return;
    }
    try {
        if (currentTree == 0) {
            atree.remove(key);
        }
        if (currentTree == 1) {
            rtree.remove(key);
        }
        if (currentTree == 2) {
            stree.remove(key);
        }
    }
    catch(std::invalid_argument) {
        return;
    }
    renderTree();
    if (currentTree == 0) {
        renderLines(atree.get_tree());
    }
    else if (currentTree == 1) {
        renderLines(rtree.get_tree());
    }
    else {
        renderLines(stree.get_tree());
    }
}

void MainWindow::renderTree() {
    mainScene->clear();
    mainScene->update();
    int prev = 0;
    if (currentTree == 0) {
        for (auto elem = atree.begin(); elem != atree.end(); elem = elem->next()) {
            auto x = prev++ * 150;
            auto y = 1000 - elem->h * 150;
            auto xe = x - 15 - 5 * (10 - QString::number(elem->key).size());
            elem->high = {xe + 75, y};
            elem->low = {xe + 75, y + 30};


            auto e = new QGraphicsEllipseItem(xe, y, 150, 30);
            e->setPen(mainPen);
            auto t = new QGraphicsTextItem(QString::number(elem->key));
            t->setFont(mainFont);
            t->setX(x);
            t->setY(y);
            mainScene->addItem(e);
            mainScene->addItem(t);
        }
    }
    else if (currentTree == 1) {
        for (auto elem = rtree.begin(); elem != rtree.end(); elem = elem->next()) {
            auto x = prev++ * 150;
            auto y = 1000 - elem->h * 150;
            auto xe = x - 15 - 5 * (10 - QString::number(elem->key).size());
            elem->high = {xe + 75, y};
            elem->low = {xe + 75, y + 30};


            auto e = new QGraphicsEllipseItem(xe, y, 150, 30);
            if (elem->color) {
                e->setBrush(QBrush(Qt::red));
            }
            else {
                e->setBrush(QBrush(Qt::black));
            }
            e->setPen(mainPen);
            auto t = new QGraphicsTextItem(QString::number(elem->key));
            t->setFont(mainFont);
            t->setDefaultTextColor(QColor(255, 248, 220));
            t->setX(x);
            t->setY(y);
            mainScene->addItem(e);
            mainScene->addItem(t);
        }
    }
    else {
        for (auto elem = stree.begin(); elem != stree.end(); elem = elem->next()) {
            auto x = prev++ * 150;
            auto y = 1000 - elem->h * 150;
            auto xe = x - 15 - 5 * (10 - QString::number(elem->key).size());
            elem->high = {xe + 75, y};
            elem->low = {xe + 75, y + 30};


            auto e = new QGraphicsEllipseItem(xe, y, 150, 30);
            e->setPen(mainPen);
            auto t = new QGraphicsTextItem(QString::number(elem->key));
            t->setFont(mainFont);
            t->setX(x);
            t->setY(y);
            mainScene->addItem(e);
            mainScene->addItem(t);
        }
    }
}

void MainWindow::renderLines(Node* p) {
    if (p == nullptr) {
        return;
    }
    if (p->left != nullptr) {
        QLine l = QLine(p->low, p->left->high);
        mainScene->addLine(l, mainPen);
    }
    if (p->right != nullptr) {
        QLine l = QLine(p->low, p->right->high);
        mainScene->addLine(l, mainPen);
    }
    renderLines(p->left);
    renderLines(p->right);
}

void MainWindow::changeCurrentTree(int type) {

    if (currentTree == 0) {
        if (type == 0) {
            return;
        }
        else if (type == 1) {
            rtree.clear();
            for (auto elem = atree.begin(); elem != atree.end(); elem=elem->next()) {
                rtree.insert(elem->key);
            }
        }
        else {
            stree.clear();
            for (auto elem = atree.begin(); elem != atree.end(); elem=elem->next()) {
                stree.insert(elem->key);
            }
        }
    }
    else if (currentTree == 1) {
        if (type == 0) {
            atree.clear();
            for (auto elem = rtree.begin(); elem != rtree.end(); elem=elem->next()) {
                atree.insert(elem->key);
            }
        }
        else if (type == 1) {
            return;
        }
        else {
            stree.clear();
            for (auto elem = rtree.begin(); elem != rtree.end(); elem=elem->next()) {
                stree.insert(elem->key);
            }
        }
    }
    else {
        if (type == 0) {
            atree.clear();
            for (auto elem = stree.begin(); elem != stree.end(); elem=elem->next()) {
                atree.insert(elem->key);
            }
        }
        else if (type == 1) {
            rtree.clear();
            for (auto elem = stree.begin(); elem != stree.end(); elem=elem->next()) {
                rtree.insert(elem->key);
            }
        }
        else {
            return;
        }
    }

    currentTree = type;
    renderTree();
    if (currentTree == 0) {
        renderLines(atree.get_tree());
    }
    else if (currentTree == 1) {
        renderLines(rtree.get_tree());
    }
    else {
        renderLines(stree.get_tree());
    }
}

void MainWindow::clearCanvas() {
    mainScene->clear();
    mainScene->update();
    atree.clear();
    rtree.clear();
    stree.clear();
}

