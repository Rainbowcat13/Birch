#include "Splay_tree.h"

int Splay_tree::recountHeights(Node *&p) {
    if (p == nullptr) {
        return 0;
    }
    return p->h = std::max(recountHeights(p->right),
                           recountHeights(p->left)) + 1;
}

void setParent(Node*& v, Node* p) {
    if (v != nullptr) {
        v->parent = p;
    }
}

void keepParents(Node*& v) {
    if (v == nullptr)
        return;
    setParent(v->right, v);
    setParent(v->left, v);
}

Splay_tree::Splay_tree() {
    tree = nullptr;
}

void Splay_tree::rotate(Node* p, Node* v) {
    auto g = p->parent;
    if (g != nullptr) {
        if (g->left == p) {
            g->left = v;
        }
        else {
            g->right = v;
        }
    }
    setParent(v, g);
    if (p->left == v) {
        p->left = v->right;
        setParent(v->right, p);
        v->right = p;
        setParent(p, v);
    }
    else {
        p->right = v->left;
        setParent(v->left, p);
        v->left = p;
        setParent(p, v);
    }

//    keepParents(v);
//    keepParents(p);
    v->parent = g;
}

Node* Splay_tree::splay(Node *v) {
    if (v->parent == nullptr) {
        return v;
    }
    auto p = v->parent;
    auto g = p->parent;
    if (g == nullptr) {
        rotate(p, v);
        return v;
    }
    else {
        auto zigzig = (g->left == p) == (p->left == v);
        if (zigzig) {
            rotate(g, p);
            rotate(p, v);
        }
        else {
            rotate(p, v);
            rotate(g, v);
        }
        return splay(v);
    }
}

Node* Splay_tree::find(int key) {
    return findNode(tree, key);
}

Node* Splay_tree::findNode(Node* cur, int key) {
    if (cur == nullptr) {
        return nullptr;
    }
    if (key == cur->key) {
        return splay(cur);
    }
    if (key < cur->key && cur->left != nullptr) {
        return findNode(cur->left, key);
    }
    if (key > cur->key && cur->right != nullptr) {
        return findNode(cur->right, key);
    }
    return splay(cur);
}

std::pair<Node*, Node*> Splay_tree::split(Node *cur, int key) {
    if (cur == nullptr) {
        return {nullptr, nullptr};
    }
    cur = findNode(cur, key);
    if (cur->key == key) {
        if (cur->left != nullptr)
            setParent(cur->left, nullptr);
        if (cur->right != nullptr)
            setParent(cur->right, nullptr);
        return {cur->left, cur->right};
    }
    else if (cur->key < key) {
        auto r = cur->right;
        cur->right = nullptr;
        if (r != nullptr)
            setParent(r, nullptr);
        return {cur, r};
    }
    else {
        auto l = cur->left;
        cur->left = nullptr;
        if (l != nullptr)
            setParent(l, nullptr);
        return {l, cur};
    }
}

void Splay_tree::insert(int key) {
    auto spl = split(tree, key);
    auto nr = new Node(key);
    nr->left = spl.first;
    nr->right = spl.second;
    keepParents(nr);
    tree = nr;
    recountHeights(tree);
}

Node* Splay_tree::merge(Node *left, Node *right) {
    if (right == nullptr) {
        return left;
    }
    if (left == nullptr) {
        return right;
    }
    right = findNode(right, left->key);
    right->left = left;
    left->parent = right;
    return right;
}

void Splay_tree::remove(int key) {
    auto v = findNode(tree, key);
    setParent(v->left, nullptr);
    setParent(v->right, nullptr);
    tree = merge(v->left, v->right);
    recountHeights(tree);
}

Node* Splay_tree::begin() {
    Node* min = tree;
    while (min != nullptr && min->left != nullptr) {
        min = min->left;
    }
    return min;
}

Node* Splay_tree::end() {
    return nullptr;
}

Node* Splay_tree::get_tree() {
    return tree;
}

void Splay_tree::clear() {
    tree = nullptr;
}
