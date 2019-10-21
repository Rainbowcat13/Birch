#ifndef BIRCH_AVL_TREE_H
#define BIRCH_AVL_TREE_H
#include "Node.h"
#include "AVL_tree.h"
#include "Node.h"
#include <stdexcept>
#include "commoncode.h"

class AVL_tree {
    Node *tree, *min, *max;
    void balance(Node*& p);
    void insertNode(Node* nw, Node*& cur, Node* p);
    void removeNode(Node* rm);
    Node* findNode(int val, Node* cur);

public:
    AVL_tree();
    void insert(int newValue);
    void remove(int value);
    Node* find(int value);
    Node* begin();
    Node* end();
};


#endif
