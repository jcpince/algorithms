/*
63. Unique Paths II
Medium

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and space is marked as 1 and 0 respectively in the grid.

/* Only 1 obstacle supported */

Example 1:
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Example 2:
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1
 
Constraints:
m == obstacleGrid.length
n == obstacleGrid[i].length
1 <= m, n <= 100
obstacleGrid[i][j] is 0 or 1.

S - -
- O -
- - G

  3,  3 =>  6
  2, 2  =>  2 (S -> O)
  2, 2  =>  2 (O -> G)

  6 - 2 * 2 = 2

S - O
- - -
- - G

  3,  3 =>  6
  1,  3 =>  1 (S -> O)
  3,  1 =>  1 (O -> G)

  6 - 1 * 1 => 5

S - - - -
- - O - -
- - - - -
- - - - G

  5,  4 =>  35
  2,  3 =>  3 (S -> O)
  3,  3 =>  6 (O -> G)

  35 - 6 * 3 => 17

S  -  -  - O1
-  - O0  -  -
-  -  -  -  -
-  -  -  -  G

  5,  4 =>  35
  2,  3 =>  3 (S -> O0)
  3,  3 =>  6 (O0 -> G)
  5,  1 =>  1 (S -> O1)
  1,  4 =>  1 (O1 -> G)

  35 - (6 * 3)  - (1 * 1) => 16

=> R(m,n) = number of unique paths
=> Ro(S, G, O) = R(S, G) - R(S,O0) * R(O0,G) - R(S,O1) * R(O1,G)
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

#define SWAP(a, b) { \
    unsigned tmp = a; a = b; b = tmp; }

class Solution {
    unsigned SOm, SOn;
    uint64_t sumSO;
    unsigned OGm, OGn;
    uint64_t sumOG;
    uint64_t sumSG;

    uint64_t _build_array(uint64_t array[], unsigned m, unsigned n) {
        if (m == 1)
            // R(1, n) = 1
            for (unsigned idx = 0 ; idx < n ; idx++)
                array[idx] = 1;
        else {
            // R(m, n) = Sum(R(m-1, n)), with R(1, n) = 1
            if (_build_array(array, m-1, n)) return -1;
            uint64_t sum = 1;
            for (unsigned idx = 1 ; idx < n ; idx++) {
                sum += array[idx];
                array[idx] = sum;
                if (array[idx] < array[idx-1]) return -1;
            }
        }
        if (m == SOm) sumSO = array[SOn-1];
        if (m == OGm) sumOG = array[OGn-1];
        return 0;
    }
    uint64_t uniquePaths(unsigned m, unsigned n) {
        sumSG = ~0ULL; sumSO = ~0ULL; sumOG = ~0ULL;
        // R(m, n) == R(n, m)
        uint64_t array[n];
        if (_build_array(array, m-1, n)) return ~0;
        sumSG = 1;
        for (unsigned idx = 1 ; idx < n ; idx++) {
            sumSG += array[idx];
            array[idx] = sumSG;
            if (array[idx] < array[idx-1]) return ~0;
        }
        if (m == SOm) sumSO = array[SOn-1];
        if (m == OGm) sumOG = array[OGn-1];
        return 0;
    }
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        //printf("%s(%s)\n", __func__, array2str(obstacleGrid).c_str());
        unsigned m = obstacleGrid.size();
        assert(m);
        unsigned n= obstacleGrid[0].size();
        assert(n);
        if (m < 2 || n < 2) return 1 - accumulate(obstacleGrid[0].begin(), obstacleGrid[0].end(), 0);

        uint64_t SOx = ~0ULL, SOy;
        for (unsigned idx = 0 ; idx < m && SOx == ~0ULL ; idx++)
            for (unsigned jdx = 0 ; jdx < n ; jdx++)
                if (obstacleGrid[idx][jdx]) {
                    SOx = idx;
                    SOy = jdx;
                    break;
                }
        if (SOx == ~0ULL) {
            if (m > n) SWAP(m, n);
            assert(!uniquePaths(m, n));
            return sumSG;
        }

        if ((SOx == 0 && SOy == 0) || (SOx == m-1 && SOy == n-1))
            return 0;
        if (m == 2 || n == 2) return 1;

        SOm = SOx + 1;
        SOn = SOy + 1;
        OGm = m - SOx;
        OGn = n - SOy;
        if (m > n) {
            SWAP(m, n);
            SWAP(SOm, SOn);
            SWAP(OGm, OGn);
        }
        //printf("SO(m, n)=(%d, %d), OG(m, n)=(%d, %d)\n", SOm, SOn, OGm, OGn);
        assert(!uniquePaths(m, n));
        /*printf("SG %ld, SO %ld, OG %ld\n", sumSG, sumSO, sumOG);
        assert(sumSO != ~0ULL);
        assert(sumSG != ~0ULL);
        assert(sumOG != ~0ULL);*/
        return sumSG - sumSO * sumOG;
    }
};

int run_test_case(void *__s, TestCase *tc) {
        UNUSED(__s);
        vector<vector<int>> obstacleGrid = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution _s;
        int result = _s.uniquePathsWithObstacles(obstacleGrid);

        if (result == expected) return 0;

        printf("uniquePathsWithObstacles(%s) returned %d but expected %d\n",
            array2str(obstacleGrid).c_str(), result, expected);
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