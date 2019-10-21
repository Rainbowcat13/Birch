#include "commoncode.h"

int RBheight(Node *p) {
    return p == nullptr ? 1 : p->h;
}

int AVLheight(Node* p) {
    return p == nullptr ? 0 : p->h;
}

void recountHeight(Node *&p) {
    if (p == nullptr)
        return;
    if (p->color == -1)
        p->h = std::max(AVLheight(p->left), AVLheight(p->right)) + 1;
    else
        p->h = std::max(RBheight(p->left), RBheight(p->right)) + 1;
}

bool isLeaf(Node *p) {
    return p->left == nullptr && p->right == nullptr;
}

void rotate_left(Node*& p) {
    Node* q = p->left;
    int hnl, hc;
    if (p->color == -1) {
        hnl = AVLheight(q->left);
        hc = AVLheight(q->right);
    }
    else {
        hnl = RBheight(q->left);
        hc = RBheight(q->right);
    }
    if (hnl >= hc) {
        p->left = q->right;
        if (q->right != nullptr) q->right->parent = p;
        q->right = p;
        if (p != nullptr) p->parent = q;
        p = q;
    }
    else {
        Node* r = q->right;
        p->left = r->right;
        if (r->right != nullptr) r->right->parent = p;
        q->right = r->left;
        if (r->left != nullptr) r->left->parent = q;
        r->left = q;
        if (q != nullptr) q->parent = r;
        r->right = p;
        if (p != nullptr) p->parent = r;
        p = r;
    }
}

void rotate_right(Node*& p) {
    Node *q = p->right;
    int hnr, hc;
    if (p->color == -1) {
        hnr = AVLheight(q->left);
        hc = AVLheight(q->right);
    }
    else {
        hnr = RBheight(q->left);
        hc = RBheight(q->right);
    }
    if (hnr >= hc) {
        p->right = q->left;
        if (q->left != nullptr) q->left->parent = p;
        q->left = p;
        if (p != nullptr) p->parent = q;
        p = q;
    }
    else {
        Node* r = q->left;
        p->right = r->left;
        if (r->left != nullptr) r->left->parent = p;
        q->left = r->right;
        if (r->right != nullptr) r->right->parent = q;
        r->left = p;
        if (p != nullptr) p->parent = r;
        r->right = q;
        p = r;
    }
}

int color(Node* p) {
    if (p == nullptr)
        return 0;
    return p->color;
}