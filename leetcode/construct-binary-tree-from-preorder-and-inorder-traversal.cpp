/*
105. Construct Binary Tree from Preorder and Inorder Traversal
Medium

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given
preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7
*/

//#define DEBUG 1
#undef DEBUG

#include <TestsHelper.h>
#include <cstdint>

using namespace std;

const bool continue_on_failure = false;

#if 0
class Solution {
    int inline seek_right_idx(const int* &i, const int &r0, const int &val) {
        int r = r0;
        while (r < nb_nodes and i[r] != val) r++;
        return r;
    }
    int inline seek_left_idx(const int* &i, const int &l0, const int &val) {
        int l = l0;
        while (l >= 0 and i[l] != val) l--;
        return l;
    }
    TreeNode *buildTree(const int* &p, const int* &i, int &current) {

        if (current >= nb_nodes) return NULL;
        printf("%s(%d)\n", __func__, p[current]);0.
        

        TreeNode *root = new TreeNode(p[current++]);
        int newl = seek_left_idx(i, current, p[current]);
        if (newl > 0) root->left = buildTree(p, i, current, newl, r);
        int newr = seek_right_idx(i, current, p[current]);
        if (newr < nb_nodes) root->right = buildTree(p, i, current, newr + 1, r);
        return root;   
    }
    int nb_nodes;
    
public:
    TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {
        nb_nodes = preorder.size();
        if (!nb_nodes) return NULL;
        
        const int *p = preorder.data(), *i = inorder.data();
        int current = 0;
        TreeNode *root = buildTree(p, i, current);

        // printf("%s_main(%d, %d, %d)\n", __func__, root->val, l, r);
        // root->left = buildTree(p, current, nb_nodes, i, l, r);
        // printf("%s_main(%d, %d, %d)\n", __func__, p[current], l, r);
        // root->right = buildTree(p, current, nb_nodes, i, r + 1, nb_nodes);
        return root;
    }
};
#endif

class Solution {
    const inline int * seek_root(const int &val, const int *i) {
        while (*i != val)  i++;
        return i;
    }

    TreeNode *buildTree(const int* &p, int &psize, const int *i, const int isize) {

        printf("%s(%d, %d, %d, %d)\n", __func__, *p, psize, *i, isize);
        
        TreeNode *root = new TreeNode(*p++);
        psize--;
        if (!psize || !isize) return root;

        const int *i_root = seek_root(root->val, i);
        const int i_root_off = i_root - i;

        if (i_root != i)
            root->left = buildTree(p, psize, i, i_root_off);
        if (i_root_off != isize-1)
            root->right = buildTree(p, psize, i_root+1, isize - i_root_off - 1);
        return root;   
    }
    
public:
    TreeNode* buildTree(const vector<int>& preorder, const vector<int>& inorder) {
        int nb_nodes = preorder.size();
        if (!nb_nodes) return NULL;
        
        const int *p = preorder.data(), *i = inorder.data();
        return buildTree(p, nb_nodes, i, nb_nodes);
    }
};

void free_tree(TreeNode* root) {
    if (root->left) free_tree(root->left);
    if (root->right) free_tree(root->right);
    delete(root);
}

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<int> preorder = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["preorder"];
        vector<int> inorder = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["inorder"];
        vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        TreeNode* result = s.buildTree(preorder, inorder);
        vector<int> vresult = tree2vector(result);
        if (vresult == expected) {free_tree(result);return 0;}

        printf("buildTree(%s, %s) returned %s but expected %s\n",
            array2str(preorder).c_str(), array2str(inorder).c_str(),
            array2str(vresult).c_str(), array2str(expected).c_str());

        assert(continue_on_failure);
        free_tree(result);
        return 1;
}
