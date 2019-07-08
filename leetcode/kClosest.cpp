
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
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<vector<int>> result;
        vector<pair<uint64_t, vector<int>>> square_distances;

        size_t index = 0;
        for (vector<int> p : points)
            square_distances.push_back(
                make_pair((uint64_t)p[0] * (uint64_t)p[0] + (uint64_t)p[1] * (uint64_t)p[1], p));

        sort(square_distances.begin(), square_distances.end());
        for (index = 0 ; index < K ; index++) {
            pair<uint64_t, vector<int>> p = square_distances[index];
            result.push_back(p.second);
        }
        return result;
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<vector<int>> points = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["points"];
    int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<vector<int>> result = s.kClosest(points, k);

    if (check_result(result, expected)) return 0;

    printf("kClosest(%s, %d) returned %s but expected %s\n", array2str(points).c_str(), k,
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
