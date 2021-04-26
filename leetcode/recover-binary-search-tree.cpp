/*
  99. Recover Binary Search Tree
Hard

You are given the root of a binary search tree (BST), where exactly two nodes of the tree were swapped by mistake. Recover the tree without changing its structure.

Follow up: A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?

 

Example 1:
Input: root = [1,3,null,null,2]
Output: [3,1,null,null,2]
Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1 and 3 makes the BST valid.

Example 2:
Input: root = [3,1,4,null,null,2]
Output: [2,1,4,null,null,3]
Explanation: 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3 makes the BST valid.
 

Constraints:
The number of nodes in the tree is in the range [2, 1000].
-231 <= Node.val <= 231 - 1
*/

//#define DEBUG 1
#undef DEBUG

#include <TestsHelper.h>
#include <cstdint>

using namespace std;

const bool continue_on_failure = false;

#if 0
class Solution {
    struct minmax_t {
        TreeNode *min;
        TreeNode *max;
    };
    void __inline__ swap_nodes(TreeNode* n0, TreeNode* n1) {
        int tmp = n1->val;
        n1->val = n0->val;
        n0->val = tmp;
        //debug_print("%s(%d, %d)\n", __func__, n0->val, n1->val);
    }
    void recoverTree(TreeNode* node, struct minmax_t &minmax, bool &cont) {
        //debug_print("%s.0(%d, %d, %d, %d)\n", __func__, node->val, minmax.min->val, minmax.max->val, cont);
        
        //if (!cont) return;
        struct minmax_t lminmax = {.min = node, .max = node };
        struct minmax_t rminmax = {.min = node, .max = node };

        if (node->left) {
            cont = node->left->val < node->val;
            if (!cont) swap_nodes(node, node->left);
            recoverTree(node->left, lminmax, cont);
            if (cont and node->val < lminmax.max->val) {
                cont = false;
                swap_nodes(node, lminmax.max);
            }
            minmax.min = lminmax.min;
            //debug_print("%s.1(%d, %d, %d, %d)\n", __func__, node->val, (*minnode)->val, (*maxnode)->val, cont);
        }
        else minmax.min = node;
        //debug_print("%s.11(%d, %d, %d, %d)\n", __func__, node->val, (*_minnode)->val, (*_maxnode)->val, cont);

        if (cont and node->right) {
            cont = node->right->val > node->val;
            if (!cont) swap_nodes(node, node->right);
            recoverTree(node->right, rminmax, cont);
            if (cont and node->val > rminmax.min->val) {
                swap_nodes(node, rminmax.min);
                cont = false;
            }
            minmax.max = rminmax.max;
            //debug_print("%s.2(%d, %d, %d, %d)\n", __func__, node->val, (*minnode)->val, (*maxnode)->val, cont);
        }
        else minmax.max = node;
        
        /*if (cont and lminmax.max > rminmax.min) {
            swap_nodes(lminmax.max, rminmax.min);
            cont = false;
        }*/
        //debug_print("%s.3(%d, l(%d, %d), r(%d, %d), %d\n", __func__, node->val,
        //       lminmax.min->val, lminmax.max->val, rminmax.min->val, rminmax.max->val, cont);
    }
public:
    void recoverTree(TreeNode* root) {
        struct minmax_t minmax = {.min = root, .max = root };
        bool cont = true;
        recoverTree(root, minmax, cont);
    }
};
#endif

#if 1
class Solution {
    struct minmax_t {
        TreeNode *min;
        TreeNode *max;
    };
    void inline swap_nodes(TreeNode* n0, TreeNode* n1) {
        int tmp = n1->val;
        n1->val = n0->val;
        n0->val = tmp;
        debug_print("%s(%d, %d)\n", __func__, n0->val, n1->val);
    }
    void inline add_wrong_node(TreeNode *root, const char* lbl, set<TreeNode *> &wrong_nodes,
            TreeNode *wrong_node) {
        if (wrong_nodes.find(wrong_node) == wrong_nodes.end()) {
            debug_print("%s(%d) pushes %d\n", lbl, root->val, wrong_node->val);
            wrong_nodes.emplace(wrong_node);
        }
        if (wrong_nodes.find(root) == wrong_nodes.end()) {
            debug_print("%s(%d) pushes %d\n", lbl, root->val, root->val);
            wrong_nodes.emplace(root);
        }
    }
    void recoverTree(TreeNode* node, struct minmax_t &minmax, set<TreeNode *> &wrong_nodes) {
        debug_print("%s.0(%d, (%d, %d)\n", __func__, node->val,
               minmax.min->val, minmax.max->val);

        struct minmax_t lminmax = {.min = node, .max = node };
        struct minmax_t rminmax = {.min = node, .max = node };

        if (node->left) {
            if (node->left->val >= node->val)
                add_wrong_node(node, "l0", wrong_nodes, node->left);

            recoverTree(node->left, lminmax, wrong_nodes);
            if (node->val < lminmax.max->val)
                add_wrong_node(node, "l1", wrong_nodes, lminmax.max);
            minmax.min = lminmax.min;
        }
        else minmax.min = node;
        debug_print("%s.1(%d, l(%d, %d), r(%d, %d)\n", __func__, node->val,
               lminmax.min->val, lminmax.max->val, rminmax.min->val, rminmax.max->val);

        if (node->right) {
            if (node->right->val <= node->val)
                add_wrong_node(node, "r0", wrong_nodes, node->right);

            recoverTree(node->right, rminmax, wrong_nodes);
            if (node->val > rminmax.min->val)
                add_wrong_node(node, "r1", wrong_nodes, rminmax.min);
            minmax.max = rminmax.max;
        }
        else minmax.max = node;
        debug_print("%s.2(%d, l(%d, %d), r(%d, %d)\n", __func__, node->val,
               lminmax.min->val, lminmax.max->val, rminmax.min->val, rminmax.max->val);
    }
    bool isValidBST(const TreeNode* node, int64_t &__min, int64_t &__max) {
        bool result = true;

        if (node->left) {
            int64_t _min = (int64_t)node->val, _max = (int64_t)node->val;
            result &= node->left->val < node->val and
                        isValidBST(node->left, _min, _max) and
                            node->val > _max;
            __min = _min;
        }
        else __min = (int64_t)node->val;

        if (result and node->right) {
            int64_t _min = (int64_t)node->val, _max = (int64_t)node->val;
            result &= node->right->val > node->val and
                        isValidBST(node->right, _min, _max) and
                            node->val < _min;
            __max = _max;
        }
        else __max = (int64_t)node->val;

        return result;
    }
    bool isValidBST(const TreeNode* root) {
        int64_t _min = (int64_t)root->val, _max = (int64_t)root->val;
        return isValidBST(root, _min, _max);
    }
public:
    void recoverTree0(TreeNode* root) {
        struct minmax_t minmax = {.min = root, .max = root };
        set<TreeNode *> wrong_nodes;
        recoverTree(root, minmax, wrong_nodes);
        if (wrong_nodes.size() < 2) return;
        else {
            set<TreeNode *>::iterator it0 = wrong_nodes.begin(), it1 = it0;
            for ( ; it0 != wrong_nodes.end() ; it1 = ++it0) {
                it1++;
                for ( ; it1 != wrong_nodes.end() ; it1++)
                {
                    debug_print("%s - test swapping %d and %d\n",
                        __func__, (*it0)->val, (*it1)->val);
                    swap_nodes(*it0, *it1);
                    if (isValidBST(root)) return;
                    swap_nodes(*it0, *it1);
                }
            }
        }
    }

    void fun(TreeNode* root, TreeNode* &prev, TreeNode* &f1, TreeNode* &f2) {
        if(!root)
            return;
        fun(root->left, prev, f1, f2);
        if(f1 == nullptr && (prev == nullptr || prev->val >= root->val)) {
            f1 = prev;
        }
        if(f1 != nullptr && prev->val >= root->val) {
            f2 = root;
        }
        prev = root;
        fun(root->right, prev, f1, f2);
    }
    void recoverTree1(TreeNode* root){
        TreeNode* f1 = nullptr;
        TreeNode* f2 = nullptr;
        TreeNode* prev = nullptr;
        fun(root, prev, f1, f2);
        swap(f1->val, f2->val);
    }

    TreeNode *bad1, *bad2, *prev;
    /* In order traversal and check that prev > current*/
    void inorder_traversal_check(TreeNode* current) {
        if (!current) return;
        inorder_traversal_check(current->left);
        debug_print("Exploring %d\n", current->val);
        if (prev and prev->val > current->val) {
            if (!bad1) bad1 = prev;
            bad2 = current;
        }
        prev = current;
        inorder_traversal_check(current->right);
    }
    void recoverTree(TreeNode* root){
        bad1 = NULL;
        bad2 = NULL;
        prev = NULL;
        inorder_traversal_check(root);
        swap(bad1->val, bad2->val);
    }
};
#endif

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<int> vtree = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        vector<int> vexpected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        struct TreeNode tree[vtree.size()];
        bzero(tree, vtree.size()*sizeof(struct TreeNode));
        vector2tree(vtree, tree);
        struct TreeNode expected[vexpected.size()];
        bzero(expected, vexpected.size()*sizeof(struct TreeNode));
        vector2tree(vexpected, expected);

        Solution s;
        s.recoverTree(tree);
        vector<int> vresult = tree2vector(tree);
        if (vresult == vexpected) return 0;

        printf("recoverTree(%s) returned %s but expected %s\n",
            array2str(vtree).c_str(), array2str(vresult).c_str(),
            array2str(vexpected).c_str());

        assert(continue_on_failure);
        return 1;
}
