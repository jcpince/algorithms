#ifndef __TREENODE__
#define __TREENODE__

#include <bits/stdc++.h>

using namespace std;

/**
 * Definition for a binary tree node.
 */
typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode() : val(0), left(NULL), right(NULL) {}
} TreeNode;

void vector2tree(vector<int> &v, TreeNode *tree);
vector<int> tree2vector(TreeNode *tree);
void deleteDynTree(TreeNode *tree);

#endif
