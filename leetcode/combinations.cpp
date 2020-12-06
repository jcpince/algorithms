/*
77. Combinations
Medium
Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

You may return the answer in any order.

Example 1:
Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

Example 2:
Input: n = 1, k = 1
Output: [[1]]

Constraints:
1 <= n <= 20
1 <= k <= n
*/

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
    vector<vector<int>> combine(int n, int k) {
        if (n == 1) return {{1}};
        vector<int> base(k);
        for (int idx = 0 ; idx < k ; idx++)
          base[idx] = idx+1;
        
        vector<vector<int>> result;
        int rank = k-1;
        do {
          //printf("rank %d, pushes %s\n", rank, array2str(base).c_str());
          result.push_back(base);
          base[rank]++;

          if (base[rank] > (n - k + rank + 1)) {
            while (rank and base[rank] >= (n - k + rank + 1))
              rank--;
            base[rank]++;
            for (int idx = rank + 1 ; idx < k ; idx++)
              base[idx] = base[idx-1] + 1;
            rank = k - 1;
          }
        } while (base[0] < (n - k + 1));

        if (base[k-1] == n)
          result.push_back(base);

        return result;    
    }
    vector<vector<int>> combine0(int n, int k) {
        if (n == 1) return {{1}};
        vector<int> base(k);
        for (int idx = 0 ; idx < k ; idx++)
          base[idx] = idx+1;
        
        vector<vector<int>> result;
        int rank = k-1, curr_rank = rank;
        do {
          printf("rank %d, curr_rank is %d, pushes %s\n", rank, curr_rank, array2str(base).c_str());
          result.push_back(base);
          base[curr_rank]++;

          if (base[curr_rank] > (n - k + curr_rank + 1)) {
            if (rank and curr_rank == rank) {
              base[--rank]++;
              for (int idx = rank + 1 ; idx < k ; idx++)
                base[idx] = base[idx-1] + 1;
              printf("swicthes to rank %d, reset curr_rank to %d\n", rank, k-1);
              curr_rank = k-1;
            } else {
              while (base[curr_rank] >= (n - k + curr_rank + 1))
                curr_rank--;
              base[curr_rank]++;
              for (int idx = curr_rank + 1 ; idx < k ; idx++)
                base[idx] = base[idx-1] + 1;
              printf("rank %d, swicthes to curr_rank to %d\n", rank, curr_rank);
            }
          }
        } while (curr_rank > 0);

        result.push_back(base);

        return result;    
    }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
    int n = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["n"];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<vector<int>> result = s.combine(n, k);

    if (check_result(result, expected)) return 0;

    printf("combinations(%d, %d) returned %s but expected %s\n", n, k,
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