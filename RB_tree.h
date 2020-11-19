#ifndef BIRCH_RB_TREE_H
#define BIRCH_RB_TREE_H
#include "Node.h"

class RB_tree {
    Node *tree;
    void balanceInsert(Node*& x);
    void balanceRemove(Node*& x);
    void rotateLeft(Node *x);
    void rotateRight(Node *x);
    void removeNode(Node*& z);
    int recountHeights(Node*& p);

public:
    RB_tree();
    void insert(int key);
    void remove(int key);
    Node* find(int key);
    Node* begin();
    Node* end();
    Node* get_tree();
    void clear();
};


#endif //BIRCH_RB_TREE_H
