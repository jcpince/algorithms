#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    void inline swap_layer(vector<vector<int>>& matrix, size_t layer) {
        size_t ms = matrix.size();
        size_t layer_end_index = ms - layer - 1;
        for (size_t index = 0 ; index < (layer_end_index - layer) ; index++) {
            // printf("Layer %d, index %d: pivots(%d, %d, %d, %d)\n", layer, index,
            //     matrix[layer][layer + index], matrix[layer_end_index-index][layer],
            //     matrix[layer_end_index][layer_end_index-index], matrix[layer+index][layer_end_index]);
            int tmp = matrix[layer][layer + index];
            matrix[layer][layer + index] = matrix[layer_end_index-index][layer];
            matrix[layer_end_index-index][layer] = matrix[layer_end_index][layer_end_index-index];
            matrix[layer_end_index][layer_end_index-index] = matrix[layer+index][layer_end_index];
            matrix[layer+index][layer_end_index] = tmp;
        }
    }
public:
    void rotate(vector<vector<int>>& matrix) {
        for (size_t layer = 0 ; layer < matrix.size() / 2 ; layer++)
            swap_layer(matrix, layer);
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<vector<int>> matrix = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<vector<int>> result = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    s.rotate(result);

    if (check_result(result, expected)) return 0;

    printf("rotate(%s) returned %s but expected %s\n", array2str(matrix).c_str(),
        array2str(result).c_str(), array2str(expected).c_str());
    dev_assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv)
{
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
