#include "RB_tree.h"

void RB_tree::rotateLeft(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    if (y != nullptr) {
        y->parent = x->parent;
    }
    if (x->parent != nullptr) {
        if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    } else {
        tree = y;
    }
    y->left = x;
    if (x != nullptr) {
        x->parent = y;
    }
}

void RB_tree::rotateRight(Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    if (y != nullptr) {
        y->parent = x->parent;
    }
    if (x->parent) {
        if (x == x->parent->right)
            x->parent->right = y;
        else
            x->parent->left = y;
    } else {
        tree = y;
    }
    y->right = x;
    if (x != nullptr) {
        x->parent = y;
    }
}

void RB_tree::balanceInsert(Node *&x) {
    while (x != tree && x->parent->color == 1) {
        if (x->parent == x->parent->parent->left) {
            Node *y = x->parent->parent->right;
            if (y != nullptr && y->color == 1) {
                x->parent->color = 0;
                y->color = 0;
                x->parent->parent->color = 1;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    rotateLeft(x);
                }
                x->parent->color = 0;
                x->parent->parent->color = 1;
                rotateRight(x->parent->parent);
            }
        } else {
            Node *y = x->parent->parent->left;
            if (y != nullptr && y->color == 1) {
                x->parent->color = 0;
                y->color = 0;
                x->parent->parent->color = 1;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(x);
                }
                x->parent->color = 0;
                x->parent->parent->color = 1;
                rotateLeft(x->parent->parent);
            }
        }
    }
    tree->color = 0;
}

void RB_tree::insert(int key) {
    Node *current, *parent, *x;
    current = tree;
    parent = nullptr;
    while (current != nullptr) {
        if (key == current->key) {
            throw std::invalid_argument("Non-unique elements in tree!");
        }
        parent = current;
        current = key < current->key ? current->left : current->right;
    }
    x = new Node();
    x->parent = parent;
    x->left = nullptr;
    x->right = nullptr;
    x->color = 1;
    x->key = key;
    if (parent != nullptr) {
        if (key < parent->key)
            parent->left = x;
        else
            parent->right = x;
    } else {
        tree = x;
    }
    balanceInsert(x);
    recountHeights(tree);
}

void RB_tree::balanceRemove(Node *&x) {
    if (x == nullptr) {
        return;
    }

    while (x != tree && x->color == 0) {
        if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 0 && w->right->color == 0) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->right->color == 0) {
                    w->left->color = 0;
                    w->color = 1;
                    rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->right->color = 0;
                rotateLeft(x->parent);
                x = tree;
            }
        } else {
            Node *w = x->parent->left;
            if (w->color == 1) {
                w->color = 0;
                x->parent->color = 1;
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 0 && w->left->color == 0) {
                w->color = 1;
                x = x->parent;
            } else {
                if (w->left->color == 0) {
                    w->right->color = 0;
                    w->color = 1;
                    rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 0;
                w->left->color = 0;
                rotateRight(x->parent);
                x = tree;
            }
        }
    }
    x->color = 0;
}

void RB_tree::removeNode(Node *&z) {
    Node *x, *y;

    if (z->left == nullptr || z->right == nullptr) {
        y = z;
    } else {
        y = z->right;
        while (y->left != nullptr) {
            y = y->left;
        }
    }
    if (y->left != nullptr) {
        x = y->left;
    } else {
        x = y->right;
    }
    if (x != nullptr) {
        x->parent = y->parent;
    }
    if (y->parent != nullptr)
        if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
    else {
        tree = x;
    }
    if (y != z) {
        z->key = y->key;
    }
    if (y->color == 0) {
        balanceRemove(x);
    }
}

void RB_tree::remove(int key) {
    auto v = find(key);
    if (v == nullptr) {
        throw std::invalid_argument("No element to delete!");
    }
    removeNode(v);
    recountHeights(tree);
}

Node *RB_tree::find(int key) {
    Node *current = tree;
    while (current != nullptr) {
        if (key == current->key) {
            return current;
        } else {
            current = key < current->key ? current->left : current->right;
        }
    }
    return current;
}

RB_tree::RB_tree() {
    tree = nullptr;
}

Node *RB_tree::end() {
    return nullptr;
}

Node *RB_tree::begin() {
    Node *min = tree;
    while (min != nullptr && min->left != nullptr) {
        min = min->left;
    }
    return min;
}

void RB_tree::clear() {
    delete tree;
    tree = nullptr;
}

Node *RB_tree::get_tree() {
    return tree;
}

int RB_tree::recountHeights(Node *&p) {
    if (p == nullptr) {
        return 0;
    }
    return p->h = std::max(recountHeights(p->right),
                           recountHeights(p->left)) + 1;
}