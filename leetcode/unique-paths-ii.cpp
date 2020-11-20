/*
63. Unique Paths II
Medium

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and space is marked as 1 and 0 respectively in the grid.

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

class Solution {
    unsigned m, n;
    int *grid;

    int inline cell(unsigned row, unsigned col) {
        return grid[row * n + col];
    }

    void inline set_cell(unsigned row, unsigned col, int val) {
        grid[row * n + col] = val;
    }

    void dump_grid() {
        printf("m %d, n %d\n", m, n);
        for (unsigned row = 0 ; row < m ; row++) {
            for (unsigned col = 0 ; col < n ; col++)
                printf("%5d ", cell(row, col));
            printf("\n");
        }
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        unsigned row, col;
        m = obstacleGrid.size();
        assert(m);
        n = obstacleGrid[0].size();
        assert(n);

        int _grid[m*n];
        grid = &_grid[0];

        if (obstacleGrid[0][0] + obstacleGrid[m-1][n-1]) return 0;

        memset(grid, 0, sizeof(_grid));
        for (row = 0 ; row < m ; row++)
            for (col = 0 ; col < n ; col++)
                if (obstacleGrid[row][col]) set_cell(row, col, -1);

        //printf("cel(0, 0) %d, cell(%d, %d) %d\n", cell(0,0),
        //    m-1, n-1, cell(m-1, n-1));

        /* first row set to 1 until first obstacle */
        for (col = 0 ; col < n && !cell(0, col) ; col++)
            set_cell(0, col, 1);
        for (; col < n ; col++)
            set_cell(0, col, 0);

        /* first col set to 1 until first obstacle */
        for (row = 1 ; row < m && !cell(row, 0) ; row++)
            set_cell(row, 0, 1);
        for (; row < m ; row++)
            set_cell(row, 0, 0);

        /* inner grid*/
        for (row = 1 ; row < m ; row++)
            for (col = 1 ; col < n ; col++) {
                if (cell(row, col)) set_cell(row, col, 0);
                else set_cell(row, col, cell(row-1, col) + cell(row, col-1));
            }
        // printf("%s(%s) => \n", __func__,
        //    array2str(obstacleGrid).c_str());
        // dump_grid();

        return cell(m-1, n-1);
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