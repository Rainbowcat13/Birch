#ifndef BIRCH_NODE_H
#define BIRCH_NODE_H

//template<typename T>
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

    Node* operator++(int) {
        if (right == nullptr) {
            return parent;
        }
        Node* p = right;
        while (p->left != nullptr) {
            p = p->left;
        }
        return p;
    }
};


#endif
