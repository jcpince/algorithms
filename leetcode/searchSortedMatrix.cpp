#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    bool findSorted(vector<int> &row, int target) {
        int l = 0, r = row.size()-1;

        while ((l + 1) < r) {
            int m = l + (r - l) / 2;
            if (row[m] == target) return true;
            if (row[m] > target) r = m-1;
            else l = m+1;
        }
        return ((row[l] == target) or (row[r] == target));
    }
public:
    bool searchMatrix_dichotomy(vector<vector<int>>& matrix, int target) {
        if (!matrix.size() or !matrix.front().size()) return false;
        for (size_t idx = 0 ; idx < matrix.size() ; idx++) {
            if ((matrix[idx].front() <= target) and (matrix[idx].back() >= target))
                if (findSorted(matrix[idx], target)) return true;
        }
        return false;
    }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if ((matrix.size() == 0) or (matrix.front().size() == 0)) return false;
        int n = (int)matrix.size(), m = (int)matrix.front().size();
        for (int row = (n-1), col = 0 ; (row >= 0) and (col < m) ; ) {
            if (matrix[row][col] == target) return true;
            else if (matrix[row][col] > target) row--;
            else col++;
        }
        return false;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<vector<int>> matrix = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["matrix"];
    int target = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["target"];
    bool expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    bool result = s.searchMatrix(matrix, target);

    if (result == expected) return 0;

    printf("searchMatrix(%s, %d) returned %d but expected %d\n", array2str(matrix).c_str(), target,
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
