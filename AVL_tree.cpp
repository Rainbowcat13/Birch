#include "AVL_tree.h"

int height(Node* p) {
    return p == nullptr ? 0 : p->h;
}

void recountHeight(Node*& p) {
    if (p == nullptr)
        return;
    p->h = std::max(height(p->left), height(p->right)) + 1;
}

bool isLeaf(Node* p) {
    return p->left == nullptr && p->right == nullptr;
}

AVL_tree::AVL_tree() {
    tree = nullptr;
}

Node* AVL_tree::begin() {
    Node* min = tree;
    while (min != nullptr && min->left != nullptr) {
        min = min->left;
    }
    return min;
}

Node* AVL_tree::end() {
    return nullptr;
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
    auto cpp = p->parent;
    recountHeight(p);
    if (abs(hl - hr) < 2) {
        return;
    }
    if (hr == hl - 2) {
        Node* q = p->left;
        int hnl = height(q->left);
        int hc = height(q->right);
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
    else {
        Node *q = p->right;
        int hnr = height(q->right);
        int hc = height(q->left);
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
    p->parent = cpp;
    recountHeight(p->left);
    recountHeight(p->right);
    recountHeight(p);
}

Node*& AVL_tree::findNode(int val, Node*& cur) {
    if (cur == nullptr) {
        return cur;
    }
    if (cur->key == val) {
        return cur;
    }
    if (cur->key > val) {
        return findNode(val, cur->left);
    }
    return findNode(val, cur->right);
}

Node*& AVL_tree::find(int value) {
    return findNode(value, tree);
}

void AVL_tree::remove(int value) {
    Node*& remNode = find(value);
    if (remNode == nullptr) {
        throw std::invalid_argument("No element to delete!");
    }
    removeNode(remNode);
}

void AVL_tree::removeNode(Node *&rm) {
    Node* newcur;
    bool f = 0;
    if (isLeaf(rm)) {
        newcur = rm->parent;
        rm = nullptr;
        goto out;
    }
    else if (rm->left == nullptr) {
        newcur = rm->right;
        while (newcur->left != nullptr) {
            newcur = newcur->left;
        }
    }
    else {
        newcur = rm->left;
        while (newcur->right != nullptr) {
            newcur = newcur->right;
        }
    }
    rm->key = newcur->key;
    if (newcur->parent != nullptr) {
        if (newcur == newcur->parent->right) {
            newcur->parent->right = nullptr;
        }
        else {
            newcur->parent->left = nullptr;
        }
    }
    newcur = rm;
    out:;
    while (newcur != nullptr) {
        balance(newcur);
        newcur = newcur->parent;
    }
}