#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
	struct si { const TreeNode* node; const int depth; };
	bool inline isleaf(const TreeNode* node) {
		return node && !node->left && !node->right;
	}
public:
    bool isValidSequence(const TreeNode* root, const vector<int>& arr) {
        if (root->val != arr.front()) return false;
	if (arr.size() == 1) return isleaf(root);
	int depth = 1;
        stack<struct si> tovisit;
	const TreeNode* node = root;
        while (node && depth < (int)arr.size()) {
	    
	    bool rok = (node->right && node->right->val == arr[depth]);
	    bool lok = (node->left && node->left->val == arr[depth]);
	    if (!rok && !lok) {
		    if (tovisit.empty()) return false;
		    struct si s = tovisit.top();
		    tovisit.pop();
		    node = s.node;
		    depth = s.depth;
		    //printf("Pop %d\n", node->val);
		    continue;
	    }
	    depth++;
	    if (depth == (int)arr.size() &&
			    ((lok && isleaf(node->left)) || 
			     	(rok && isleaf(node->right)))) return true;
	    if (rok && lok) {
		    struct si s = { node->left, depth };
		    tovisit.push(s);
		    //printf("Pushed %d\n", node->left->val);
		    node = node->right;
	    } else {
		    node = lok ? node->left : node->right;
	    }
        }
        return false;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> vtree = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["tree"];
    vector<int> arr = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["arr"];
    bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    struct TreeNode tree[vtree.size()];
    bzero(tree, vtree.size()*sizeof(struct TreeNode));
    vector2tree(vtree, tree);

    Solution s;
    bool result = s.isValidSequence(tree, arr);

    if (result == expected) return 0;

    printf("isValidSequence(%s, %s) returned %d but expected %d\n",
	array2str(vtree).c_str(), array2str(arr).c_str(),
        result, expected);
    assert(continue_on_failure);
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
