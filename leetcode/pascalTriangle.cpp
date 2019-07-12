/*
https://leetcode.com/problems/pascals-triangle/

118. Pascal's Triangle
Easy

Given a non-negative integer numRows, generate the first numRows of Pascal's triangle.


In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]

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
public:
    vector<vector<int>> generate(int numRows) {

        if (numRows == 0) return {};
        if (numRows == 1) return {{1}};

        vector<int> v1 = {1, 1}, v2, *pprev = &v1, *pcurrent = &v2;
        vector<vector<int>> result = {{1}, v1};
        for (int row = 2 ; row < numRows ; row++) {
            pcurrent->push_back(1);
            for (size_t idx = 1 ; idx < pprev->size() ; idx++)
                pcurrent->push_back((*pprev)[idx-1] + (*pprev)[idx]);
            pcurrent->push_back(1);
            result.push_back(*pcurrent);
            /* swap */
            pprev->erase(pprev->begin(), pprev->end());
            vector<int> *tmp = pprev;
            pprev = pcurrent;
            pcurrent = tmp;
        }

        return result;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    int numRows = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<vector<int>> result = s.generate(numRows);

    if (check_result(result, expected)) return 0;

    printf("generate(%d) returned %s but expected %s\n", numRows,
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
