/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

 #include <bits/stdc++.h>

 //#define DEBUG 1
 #undef DEBUG
 #define PERFS_TESTS_COUNT 15000

 #include <TreeNode.h>
 #include <UnitTests.h>
 #include <TestsHelper.h>

 using namespace std;

 #ifdef DEBUG
 const bool continue_on_failure = false;
 #endif

 class Solution {
     struct TreeNode *find_target(TreeNode* node, int target) {
         if (node->val == target) return node;
         if (target < node->val) {
             if (!node->left) return NULL;
             return find_target(node->left, target);
         }
         if (!node->right) return NULL;
         return find_target(node->right, target);
     }
     int max_val(struct TreeNode* node) {
         while (node->right) node = node->right;
         return node->val;
     }
 public:
     bool findTarget(TreeNode* root, int k) {
         if (max_val(root) < (k/2)) return false;

         vector<struct TreeNode*> layer = {root};
         while (layer.size()) {
             struct TreeNode* node = layer.back();
             layer.pop_back();

             int diff = k - node->val;
             struct TreeNode* n1 = find_target(root, diff);
             if (n1) {
                 if (n1 != node) return true;
                 if (n1->right and (n1->right->val == diff)) return true;
             }
             if (node->left) layer.push_back(node->left);
             if (node->right) layer.push_back(node->right);
         }
         return false;
     }
 };

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> vtree = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["tree"];
    int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
    bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    struct TreeNode tree[vtree.size()];
    bzero(tree, vtree.size()*sizeof(struct TreeNode));
    vector2tree(vtree, tree);

    Solution s;
    bool result = s.findTarget(tree, k);

    if (result == expected) return 0;

    printf("findTarget(%s, %d) returned %d but expected %d\n", array2str(vtree).c_str(), k,
        result, expected);
    dev_assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv) {
    int tests_ran = 0;
    const char *tc_id = NULL;

    if (argc < 2 || argc > 3)
    {
        cerr << "Usage: " << argv[0] << " <json test file> [test case index or name]" << endl;
        cerr << "Where: [test case index or name] specifies which test to run (all by default)" <<
            endl;
        return -1;
    }

    UnitTests uts(NULL, &run_test_case, argv[1]);

    if (argc == 3) tc_id = argv[2];

    int errors_count = uts.run_test_cases(tc_id, tests_ran);
    if (errors_count == 0)
        cout << "All " << tests_ran << " test(s) succeeded!!!" << endl;
    else
        cout << errors_count << " test(s) failed over a total of " << tests_ran << endl;

    return errors_count;
    }
