#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    bool inline reset_combination(vector<int> &base, int off) {
        if (off < 0 || base[off] > 9) return false;

        int digit = base[off++] + 1;
        for ( ; off < (int)base.size() ; off++) {
            if (digit > 9) return false;
            base[off] = digit++;
        }
        return true;
    }
    bool inline next_combination(vector<int> &base, int &off) {
        base[off]++;
        while (!reset_combination(base, off)) {
            off--;
            if (off < 0) return false;
            base[off]++;
        }
        off = base.size() - 1;
        return true;
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        if ((n > 45) || (k > 9) || (k == 0) || (n == 0)) return {}; // 45 for !9
        if (k == 1) {
            if (n < 10) return {{n}};
            return {};
        }

        vector<int> base(k);
        for (int i = 1 ; i <= k ; i++)
            base[i-1] = i;

        vector<vector<int>> ans;
        int off = k - 1;
        do {
            //printf("off %d: base %s\n", off, array2str(base).c_str());
            if (accumulate(base.begin(), base.end(), 0) == n)
                ans.push_back(base);
        } while (next_combination(base, off));
        return ans;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
    int n = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["n"];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<vector<int>> result = s.combinationSum3(k, n);

    if (check_result(result, expected)) return 0;

    printf("combinationSum3(%d, %d) returned %s but expected %s\n", k, n,
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
