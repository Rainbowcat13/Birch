#ifndef BIRCH_SPLAY_TREE_H
#define BIRCH_SPLAY_TREE_H
#include "Node.h"


class Splay_tree {
    Node *tree;
    void rotate(Node* v, Node* p);
    Node* splay(Node* p);
    Node* findNode(Node* p, int key);
    std::pair<Node*, Node*> split(Node* cur, int key);
    Node* merge(Node* left, Node* right);
    int recountHeights(Node*& p);

public:
    Splay_tree();
    void insert(int key);
    void remove(int key);
    Node* find(int key);
    Node* begin();
    Node* end();
    Node* get_tree();
    void clear();
};


#endif //BIRCH_SPLAY_TREE_H
