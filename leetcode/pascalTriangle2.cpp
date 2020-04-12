/*
Pascal's Triangle II

Given a non-negative index k where k ≤ 33, return the kth index row of the Pascal's triangle.

Note that the row index starts from 0.


In Pascal's triangle, each number is the sum of the two numbers directly above it.

Example:

Input: 3
Output: [1,3,3,1]

Follow up:

Could you optimize your algorithm to use only O(k) extra space?

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
        vector<int> getRow(int k) {
                if (!k) return {1};
                vector<int> v0 = {1}, v1 = {1}, *hrow = &v0, *hrow0 = &v1, *_tmp;

                for (int i = 1 ; i < k ; i++) {
                        _tmp = hrow;
                        hrow = hrow0;
                        hrow0 = _tmp;
                        int last = hrow->size();
                        // printf("Loop: hrow0(%s), hrow(%s)\n",
                        //         array2str(*hrow0).c_str(),
                        //         array2str(*hrow).c_str());
                        for (int j = 1 ; j < last ; j++)
                                (*hrow)[j] = (*hrow0)[j-1] + (*hrow0)[j];
                        if (i & 0x1)
                                hrow->push_back(hrow0->back()*2);
                        else hrow->push_back((*hrow0)[last-1] + (*hrow0)[last]);
                }
                // printf("End: hrow0(%s), hrow(%s)\n",
                //         array2str(*hrow0).c_str(),
                //         array2str(*hrow).c_str());
                int mirror_idx = hrow->size() - (k & 0x1 ? 1 : 2);
                for (int i = mirror_idx ; i >= 0 ; i--)
                hrow->push_back((*hrow)[i]);

                return *hrow;
        }
        void getRowRecursive(vector<int> &row0, int k) {
                if (!k) return;

                int prev = 1;
                for ( unsigned int idx = 1 ; idx < row0.size() ; idx++ ) {
                        int sav = row0[idx];
                        row0[idx] = prev + row0[idx];
                        prev = sav;
                }
                row0.push_back(1);
                getRowRecursive(row0, k-1);
                }
        vector<int> getRow2(int k) {

                vector<int> row0 = {1};
                getRowRecursive(row0, k);
                return row0;
        }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    auto result = s.getRow2(k);

    if (result == expected) return 0;

    printf("getRow(%d) returned %s but expected %s\n",
        k, array2str(result).c_str(), array2str(expected).c_str());
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
