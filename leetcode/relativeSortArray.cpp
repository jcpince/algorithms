#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        sort(arr1.begin(), arr1.end());
        vector<int> ans(arr1.size());
        vector<int>::iterator it = arr1.begin();
        int idx = 0;
        for (int a : arr2) {
            it = find(arr1.begin(), arr1.end(), a);
            if (it == arr1.end()) continue;

            int arr1_idx = distance(arr1.begin(), it);
            while (arr1_idx < arr1.size() && arr1[arr1_idx] == a) {
                ans[idx++] = a;
                arr1[arr1_idx] = -1; // mark arr1[x] as used
                arr1_idx++;
            }
        }

        if (idx < (int)arr1.size())
            for (int a : arr1)
                if (a > 0) ans[idx++] = a;
        return ans;
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> arr1 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["arr1"];
    vector<int> arr2 = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["arr2"];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<int> result = s.relativeSortArray(arr1, arr2);

    if (check_result(result, expected)) return 0;

    printf("relativeSortArray(%s, %s) returned %s but expected %s\n", array2str(arr1).c_str(),
        array2str(arr2).c_str(), array2str(result).c_str(), array2str(expected).c_str());
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
