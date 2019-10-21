#ifndef BIRCH_RB_TREE_H
#define BIRCH_RB_TREE_H
#include "AVL_tree.h"
#include "RB_tree.h"
#include "Node.h"
#include "commoncode.h"

class RB_tree {
    Node *tree, *min, *max;
    void balance(Node*& p);
    void insertNode(Node* nw, Node*& cur, Node* p);
//    void removeNode(Node* rm);
//    Node* findNode(int val, Node* cur);

public:
    RB_tree();
    void insert(int newValue);
//    void remove(int value);
//    Node* find(int value);
    Node* begin();
    Node* end();
};


#endif //BIRCH_RB_TREE_H
