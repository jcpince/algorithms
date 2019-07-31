#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

/*
59. Spiral Matrix II
Medium

Given a positive integer n, generate a square matrix filled with elements from 1 to n2 in spiral
order.

Example:

Input: 3
Output:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> m(n, std::vector<int>(n));
        int row = 0, col = 0, layer = 0, value = 1;
        while (col < n / 2) {
            while (col < (n - layer - 1)) m[row][col++] = value++;
            while (row < (n - layer - 1)) m[row++][col] = value++;
            while (col > layer) m[row][col--] = value++;
            m[row--][col] = value++;
            while (row > layer) m[row--][col] = value++;
            layer++;
            row = layer;
            col = layer;
        }
        if (n % 2) m[n/2][n/2] = value;
        return m;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    int n = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<vector<int>> result = s.generateMatrix(n);

    if (result == expected) return 0;

    printf("generateMatrix(%d) returned %s but expected %s\n", n,
        array2str(result).c_str(), array2str(expected).c_str());
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
