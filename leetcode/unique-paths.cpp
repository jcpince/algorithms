/*
62. Unique Paths
Medium

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

Example 1:
Input: m = 3, n = 7
Output: 28

Example 2:
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down

Example 3:
Input: m = 7, n = 3
Output: 28

Example 4:
Input: m = 3, n = 3
Output: 6

Constraints:
1 <= m, n <= 100
It's guaranteed that the answer will be less than or equal to 2 * 109.

  1,  1 => 1
  2,  1 => 1
  3,  1 => 1
  ...
 99,  1 => 1

           1
  2,  2 => 2
  2,  3 => 3
  ...
  2, 99 => 99

R(2, n) = n
R(2, n) = Sum(R(1, n))

            1
            3
  3,  3 =>  6
  3,  4 => 10
  3,  5 => 15
  3,  6 => 21
  3,  7 => 28
  3,  8 => 36
  3,  9 => 45
  ...
  3, 99 => 4950

R = 1 + 2 + 3 + ... + n
R = 1 + 2 + 3 + ... + R(2, n)
R(3, n) = Sum(R(2, n))

            1
            4
           10
  4,  4 => 20
  4,  5 => 35
  4,  6 => 56
  4,  7 => 84
  4,  8 => 120
  4,  9 => 165
  ...
  4, 99 => 166650

R = 1+3+6+10+15+21+28+36+...+R(n-1)
R = 1 + 3 + 6 + ... + R(3, n)
R(4, n) = Sum(R(3, n))

            1
            5
           15
           35
  5,  5 => 70
  5,  6 => 126
  5,  7 => 210
  5,  8 => 330
  5,  9 => 495
  ...
  5, 99 => 4249575

R(5, n) = Sum(R(4, n))

=> R(m, n) = Sum(R(m-1, n)), with R(1, n) = 1
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#define UPPER_LIMIT (2000000000)

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    int _build_array(int array[], int m, int n) {
        if (m == 1)
            // R(1, n) = 1
            for (int idx = 0 ; idx < n ; idx++)
                array[idx] = 1;
        else {
            // R(m, n) = Sum(R(m-1, n)), with R(1, n) = 1
            if (_build_array(array, m-1, n)) return -1;
            int sum = 1;
            for (int idx = 1 ; idx < n ; idx++) {
                sum += array[idx];
                if (sum > UPPER_LIMIT) return -1;
                array[idx] = sum;
            }
        }
        return 0;
    }

public:
    int uniquePaths(int _m, int _n) {
        // R(m, n) == R(n, m)
        int m = min(_m, _n);
        int n = max(_m, _n);
        if (m < 2 || n < 2) return 1;

        int array[n];
        if (_build_array(array, m-1, n)) return -1;
        int sum = 1;
        for (int idx = 1 ; idx < n ; idx++) {
            sum += array[idx];
            if (sum > UPPER_LIMIT) return -1;
        }
        return sum;
    }
};

int run_test_case(void *__s, TestCase *tc) {
        UNUSED(__s);
        int m = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["m"];
        int n = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["n"];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution _s;
        int result = _s.uniquePaths(m, n);

        if (result == expected) return 0;

        printf("uniquePaths(%d, %d) returned %d but expected %d\n", m, n, result, expected);
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
                cout << errors_count << " test(s) failed over a total of "
                        << tests_ran << endl;

        return errors_count;
}