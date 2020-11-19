#ifndef BIRCH_AVL_TREE_H
#define BIRCH_AVL_TREE_H

#include "Node.h"

class AVL_tree {
public:
    Node * root;

    AVL_tree() {
        this->root = nullptr;
    }

    int height() {
        return _height(root);
    }

    void insert(int k) {
        if (_findKey(root, k) == nullptr)
            root = _insert(root, k);
        root->parent = nullptr;
    }

    void remove(int k) {
        if (_findKey(root, k) != nullptr)
            root = _remove(root, k);
        root->parent = nullptr;
    }

    int maxLen() {
        return _maxLen(root);
    }

    Node * find(int k) {
        return _findKey(root, k);
    }

    Node* get_tree() {
        return root;
    }

    Node* begin() {
        Node *min = root;
        while (min != nullptr && min->left != nullptr) {
            min = min->left;
        }
        return min;
    }

    Node* end() {
        return nullptr;
    }

    void clear() {
        delete root;
        root = nullptr;
    }

private:
    int _height(Node * p);
    int _balanceDiff(Node * p);
    void _fixHeight(Node * p);
    int _maxLen(Node * p);
    Node * _rotateRight(Node * p);
    Node * _rotateLeft(Node * q);
    Node * _balance(Node * p);
    Node * _insert(Node * p, int k);
    Node * _findMin(Node * p);
    Node * _removeMin(Node * p);
    Node * _remove(Node * p, int k);
    Node * _findKey(Node * p, int k);
};

#endif //TREESPRESENTATION_AVLTREE_H
