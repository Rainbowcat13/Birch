#ifndef BIRCH_COMMONCODE_H
#define BIRCH_COMMONCODE_H
#include "Node.h"
#include <algorithm>

int RBheight(Node *p);
int AVLheight(Node* p);
void recountHeight(Node *&p);
bool isLeaf(Node *p);
void rotate_left(Node*& p);
void rotate_right(Node*& p);
int color(Node* p);

#endif //BIRCH_COMMONCODE_H
