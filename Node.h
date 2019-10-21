#ifndef BIRCH_NODE_H
#define BIRCH_NODE_H
#include <iostream>

struct Node {
    Node *right, *left, *parent;
    int key, color, h;// T key

    Node() {
        right = left = nullptr;
        color = -1;
        key = 0;
        h = 0;
    }

    Node(int k, int c=-1, Node* p=nullptr) {
        key = k;
        color = c;
        right = left = nullptr;
        parent = p;
        h = 1;
    };

    bool operator!=(const Node* b) {
        return b->key != key;
    }

    Node* next() {
        Node* p;
        if (right != nullptr) {
            p = right;
            while (p->left != nullptr) {
                p = p->left;
            }
            return p;
        }
        p = this;
        while (p->parent != nullptr) {
            if (p->parent->left == p) {
                return p->parent;
            }
            p = p->parent;
        }
        return nullptr;
    }
};

#endif
