#include "AVL_tree.h"

AVL_tree::AVL_tree() {
    tree = min = max = nullptr;
}

Node* AVL_tree::begin() {
    if (min == nullptr) {
        min = tree;
    }
    if (min == nullptr) {
        return min;
    }
    while (min->left != nullptr) {
        min = min->left;
    }
    return min;
}

Node* AVL_tree::end() {
    if (max == nullptr) {
        max = tree;
    }
    if (max == nullptr) {
        return max;
    }
    while (max->right != nullptr) {
        max = max->right;
    }
    return max;
}

void AVL_tree::insert(int newValue) {
    Node* newNode = new Node(newValue);
    insertNode(newNode, tree, nullptr);
}

void AVL_tree::insertNode(Node *nw, Node *&cur, Node* p) {
    if (cur == nullptr) {
        cur = nw;
        cur->parent = p;
        return;
    }
    if (cur->key > nw->key) {
        insertNode(nw, cur->left, cur);
    }
    else if (cur->key == nw->key) {
        throw std::invalid_argument("Non-unique elements in tree!");
    }
    else {
        insertNode(nw, cur->right, cur);
    }
    balance(cur);
}

void AVL_tree::balance(Node *&p) {
    int hl = AVLheight(p->left);
    int hr = AVLheight(p->right);
    if (abs(hl - hr) < 2) {
        return;
    }
    auto cpp = p->parent;
    recountHeight(p);
    if (hr == hl - 2) {
        rotate_left(p);
    }
    else {
        rotate_right(p);
    }
    p->parent = cpp;
    recountHeight(p->left);
    recountHeight(p->right);
    recountHeight(p);
}

Node* AVL_tree::findNode(int val, Node* cur) {
    if (cur == nullptr) {
        return nullptr;
    }
    if (cur->key == val) {
        return cur;
    }
    if (cur->key > val) {
        return findNode(val, cur->left);
    }
    return findNode(val, cur->right);
}

Node* AVL_tree::find(int value) {
    return findNode(value, tree);
}

void AVL_tree::remove(int value) {
    Node* remNode = find(value);
    if (remNode == nullptr) {
        throw std::invalid_argument("No element to delete!");
    }
    removeNode(remNode);
}

void AVL_tree::removeNode(Node *rm) {
    Node* newcur;
    bool f = 0;
    if (isLeaf(rm)) {
        newcur = rm;
        f = 1;
    }
    else if (rm->left == nullptr) {
        newcur = rm->right;
        while (newcur->left != nullptr) {
            newcur = newcur->left;
        }
        delete rm;
        rm = newcur;
    }
    else {
        newcur = rm->left;
        while (newcur->right != nullptr) {
            newcur = newcur->right;
        }
        delete rm;
        rm = newcur;
    }
    if (newcur->parent != nullptr) {
        if (newcur->parent->left == newcur) {
            newcur->parent->left = nullptr;
        } else {
            newcur->parent->right = nullptr;
        }
    }
    Node* above = newcur->parent;
    if (f) {
        delete newcur;
    }
    newcur = nullptr;
    while (above != nullptr) {
        balance(above);
        above = above->parent;
    }
}
