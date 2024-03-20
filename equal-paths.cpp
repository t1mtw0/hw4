#ifndef RECCHECK
// if you want to add any #includes like <iostream> you must do them here
// (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;

// You may add any prototypes of helper functions here

int equalPathsRec(Node *root) {
    if (root == NULL) return 0;
    int leftDepth = equalPathsRec(root->left);
    int rightDepth = equalPathsRec(root->right);
    if (leftDepth == -1 || rightDepth == -1) return -1;
    if (leftDepth == rightDepth - 1 && leftDepth == 0) return rightDepth + 1;
    if (rightDepth == leftDepth - 1 && rightDepth == 0) return leftDepth + 1;
    if (rightDepth != leftDepth) return -1;
    return leftDepth + 1;
}

bool equalPaths(Node *root) {
    // Add your code below
    if (equalPathsRec(root) != -1) return true;
    return false;
}
