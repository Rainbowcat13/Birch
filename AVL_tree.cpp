#include "AVL_tree.h"
#include <QVector>
#include <stdexcept>

int height(Node* p) {
    return p == nullptr ? 0 : p->h;
}

bool isLeaf(Node* p) {
    return p->left == nullptr && p->right == nullptr;
}

AVL_tree::AVL_tree() {
    tree = min = max = nullptr;
}

Node* AVL_tree::begin() {
    return min;
}

Node* AVL_tree::end() {
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
    int hl = height(p->left);
    int hr = height(p->right);
    p->h = std::max(hl, hr) + 1;
    if (abs(hl - hr) < 2) {
        return;
    }
    if (hr == hl - 2) {
        Node* q = p->left;
        int hnl = height(q->left);
        int hc = height(q->right);
        if (hnl >= hc) {
            p->left = q->right;
            q->right = p;
            p = q;
        }
        else {
            Node* r = q->right;
            p->left = r->right;
            q->right = r->left;
            r->left = q;
            r->right = p;
            p = r;
        }
    }
    else {
        Node *q = p->right;
        int hnr = height(q->right);
        int hc = height(q->left);
        if (hnr >= hc) {
            p->right = q->left;
            q->left = p;
            p = q;
        }
        else {
            Node* r = q->left;
            p->right = r->left;
            q->left = r->right;
            r->left = p;
            r->right = q;
            p = r;
        }
    }
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
    if (isLeaf(rm)) {
        delete rm;
        return;
    }
    Node* newcur;
    if (rm->left == nullptr) {
        Node* newcur = rm->right;
        while (newcur->left != nullptr) {
            newcur = newcur->left;
        }
        delete rm;
        rm = newcur;
    }
    else {
        Node* newcur = rm->left;
        while (newcur->right != nullptr) {
            newcur = newcur->right;
        }
        delete rm;
        rm = newcur;
    }
    Node* above = newcur->parent;
    newcur = nullptr;
    while (above != nullptr) {
        balance(above);
        above = above->parent;
    }
}
