#include <string>
#include "AVL_tree.h"

void recountParents(Node*& p) {
    if (p == nullptr) {
        return;
    }
    if (p->left != nullptr) {
        p->left->parent = p;
    }
    if (p->right != nullptr) {
        p->right->parent = p;
    }
}

int AVL_tree::_height(Node * p) {
    recountParents(p);
    return p != nullptr ? p->h : 0;
}

int AVL_tree::_balanceDiff(Node * p) {
    recountParents(p);
    return _height(p->right) - _height(p->left);
}

void AVL_tree::_fixHeight(Node * p) {
    int height_left = _height(p->left);
    int height_right = _height(p->right);
    p->h = (height_left > height_right ? height_left : height_right) + 1;
    recountParents(p);
}

Node * AVL_tree::_rotateRight(Node * p) {
    Node * q = p->left;
    recountParents(p);
    recountParents(q);
    p->left = q->right;
    recountParents(p);
    q->right = p;
    recountParents(q);
    _fixHeight(p);
    recountParents(p);
    _fixHeight(q);
    recountParents(q);
    return q;
}

Node * AVL_tree::_rotateLeft(Node * q) {
    Node * p = q->right;
    recountParents(p);
    recountParents(q);
    q->right = p->left;
    recountParents(q);
    p->left = q;
    recountParents(p);
    _fixHeight(q);
    recountParents(q);
    _fixHeight(p);
    recountParents(p);
    return p;
}

Node * AVL_tree::_balance(Node * p) {
    _fixHeight(p);
    recountParents(p);
    if (_balanceDiff(p) == 2) {
        if (_balanceDiff(p->right) < 0) {
            Node* q = _rotateRight(p->right);
            recountParents(q);
            p->right = q;
            recountParents(p);
        }
        return _rotateLeft(p);
    }
    if (_balanceDiff(p) == -2) {
        if (_balanceDiff(p->left) > 0) {
            recountParents(p);
            p->left = _rotateLeft(p->left);
            recountParents(p);
        }
        recountParents(p);
        return _rotateRight(p);
    }
    return p;
}

Node * AVL_tree::_insert(Node * p, int k) {
    if (p == nullptr) {
        return new Node(k);
    }
    if (k < p->key) {
        p->left = _insert(p->left, k);
        recountParents(p);
    }
    else {
        p->right = _insert(p->right, k);
        recountParents(p);
    }
    return _balance(p);
}

Node * AVL_tree::_findMin(Node * p) {
    recountParents(p);
    return p->left != nullptr ? _findMin(p->left) : p;
}

Node * AVL_tree::_removeMin(Node * p) {
    recountParents(p);
    if (p->left == nullptr) {
        return p->right;
    }
    p->left = _removeMin(p->left);
    recountParents(p);
    return _balance(p);
}

Node * AVL_tree::_remove(Node * p, int k) {
    if (p == nullptr) {
        return nullptr;
    }
    if (k < p->key) {
        p->left = _remove(p->left, k);
        recountParents(p);
    } else if (k > p->key) {
        p->right = _remove(p->right, k);
        recountParents(p);
    } else {
        Node * q = p->left;
        Node * r = p->right;
        delete p;
        p = nullptr;
        if (r == nullptr) {
            return q;
        }
        Node * min = _findMin(r);
        min->right = _removeMin(r);
        recountParents(min);
        min->left = q;
        recountParents(min);
        return _balance(min);
    }
    return _balance(p);
}

Node * AVL_tree::_findKey(Node *p, int k) {
    if (p == nullptr)
        return nullptr;
    if (p->key == k) {
        return p;
    }
    if (p->key > k) {
        recountParents(p);
        return _findKey(p->left, k);
    }
    else {
        recountParents(p);
        return _findKey(p->right, k);
    }
}
