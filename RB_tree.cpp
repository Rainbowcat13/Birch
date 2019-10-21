#include "RB_tree.h"

int height(Node *p) {
    return p == nullptr ? 1 : p->h;
}

RB_tree::RB_tree() {
    tree = max = min = nullptr;
}

Node* RB_tree::begin() {
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

Node* RB_tree::end() {
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

void RB_tree::insert(int value) {
    Node* nw = new Node(value, 1, nullptr);
    if (tree == nullptr) {
        nw->color = 0;
        tree = nw;
        return;
    }
    insertNode(nw, tree, nullptr);
}

void RB_tree::insertNode(Node* nw, Node*& cur, Node* p) {
    if (cur == nullptr) {
        cur = nw;
        nw->parent = p;
    }
    else if (cur->key > nw->key) {
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

void RB_tree::balance(Node*& p) {
    if (!p->parent->color) {
        return;
    }
    Node* g = p->parent->parent;
    Node* uncle;
    if (g->left == p->parent) {
        uncle = g->right;
    }
    else {
        uncle = g->left;
    }
    if (uncle->color) {
        g->color = 1;
        p->parent->color = 0;
        uncle->color = 0;
        p->color = 1;
        return balance(g);
    }
    else {
        if (p->parent == g->left) {
            rotate_right(p);
        }
        else {
            rotate_left(p);
        }
        p->color = 1;
        p->parent->color = 0;
        g->color = 0;
        uncle->color = 0;
    }
}