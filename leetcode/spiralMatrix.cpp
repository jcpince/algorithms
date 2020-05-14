/*
54. Spiral Matrix
Medium

Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

Example 1:

Input:
[
[ 1, 2, 3 ],
[ 4, 5, 6 ],
[ 7, 8, 9 ]
]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:

Input:
[
[1, 2, 3, 4],
[5, 6, 7, 8],
[9,10,11,12]
]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

class Solution {
public:
        vector<int> spiralOrder(vector<vector<int>>& matrix) {
                int left = 0, right, top = 0, bottom = matrix.size();
                int x, y, idx = 0, res_size;

                if (bottom == 0) return {};
                if (bottom == 1) return matrix[0];

                right = matrix[0].size();
                res_size = right * bottom;
                vector<int> result(res_size);
                while (idx < res_size) {
                        x = left; y = top;
                        while (x < right)
                                result[idx++] = matrix[y][x++];
                        x = right - 1; y++;
                        // cout << "result0: [" << x << "," << y
                        // << "] -- " << array2str(result) << endl;
                        if (idx >= res_size) break;
                        while (y < bottom)
                                result[idx++] = matrix[y++][x];
                        y = bottom - 1; x--;
                        // cout << "result1: [" << x << "," << y
                        // << "] -- " << array2str(result) << endl;
                        if (idx >= res_size) break;
                        while (x >= left)
                                result[idx++] = matrix[y][x--];
                        x = left; y--;
                        // cout << "result2: [" << x << "," << y
                        // << "] -- " << array2str(result) << endl;
                        if (idx >= res_size) break;
                        while (y > top)
                                result[idx++] = matrix[y--][x];
                        // cout << "result3: [" << x << "," << y+1
                        // << "] -- " << array2str(result) << endl;
                        left++;
                        right--;
                        top++;
                        bottom--;
                }
                return result;
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<vector<int>> m = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        vector<int> result = s.spiralOrder(m);

        if (result == expected) return 0;

        printf("spiralOrder(%s) returned %s but expected %s\n",
                array2str(m).c_str(), array2str(result).c_str(),
                array2str(expected).c_str());
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
