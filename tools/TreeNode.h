#ifndef __TREENODE__
#define __TREENODE__

#include <bits/stdc++.h>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode() : val(0), left(NULL), right(NULL) {}
};

void vector2tree(vector<int> &v, struct TreeNode *tree);
vector<int> tree2vector(struct TreeNode *tree);

#endif
