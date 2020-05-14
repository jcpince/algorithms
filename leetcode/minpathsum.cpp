#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

static const auto _=[](){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);cout.tie(nullptr);
        return 0;
}();

class Solution {
        void minps(const vector<vector<int>>& grid, int row, int col,
                        int current, int &best) {
                current += grid[row][col];

                if (!row && !col) {
                        best = min(current, best);
                        return;
                }
                if (current >= best) return;

                if (row) minps(grid, row-1, col, current, best);
                if (col) minps(grid, row, col-1, current, best);
        }
        int ref(const vector<vector<int>>& grid) {
                int sum = 0;
                for (int idx = 0 ; idx < (int)grid.size() ; idx++)
                        sum += grid[idx][0];

                for (int idx = 0 ; idx < (int)grid[0].size() ; idx++)
                        sum += grid[grid[0].size()-1][idx];

                return sum;
        }
public:
        int minPathSum2(vector<vector<int>>& grid) {
                if (!grid.size()) return 0;
                if (!grid[0].size()) return 0;

                int best = ref(grid);
                minps(grid, grid.size()-1, grid[0].size()-1, 0, best);
                return best;
        }

        int minPathSum_ref(vector<vector<int>>& grid) {
                int m = grid.size();
                int n = grid[0].size();
                vector<vector<int>> dp(m,vector<int>(n,0));
                dp[0][0] = grid[0][0];
                for(int i=1;i<m;i++)
                        dp[i][0] = dp[i-1][0] + grid[i][0];
                for(int j=1;j<n;j++)
                        dp[0][j] = dp[0][j-1] + grid[0][j];
                for(int i=1;i<m;i++)
                        for(int j=1;j<n;j++)
                                dp[i][j] = min(dp[i-1][j],dp[i][j-1]) + grid[i][j];
                return dp[m-1][n-1];
        }
        int minPathSum(vector<vector<int>>& grid) {
                if (!grid.size()) return 0;
                if (!grid[0].size()) return 0;

                int rows = grid.size();
                int cols = grid[0].size();
                vector<vector<int>> cache(rows,vector<int>(cols, INT_MAX));

                /* setup the boundaries */
                cache[0][0] = grid[0][0];
                for (int col = 1 ; col < cols ; col++)
                        cache[0][col] = cache[0][col-1] + grid[0][col];

                for (int row = 1 ; row < rows ; row++)
                        cache[row][0] = cache[row-1][0] + grid[row][0];

                /* now, compute the best solution for each cell individually */
                for (int row = 1 ; row < rows ; row++)
                        for (int col = 1 ; col < cols ; col++)
                                cache[row][col] =
                                        min(cache[row-1][col],
                                                        cache[row][col-1])
                                        + grid[row][col];

                return cache[rows-1][cols-1];
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<vector<int>> grid = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        int result = s.minPathSum(grid);

        if (result == expected) return 0;

        printf("minPathSum(%s) returned %d but expected %d\n",
        array2str(grid).c_str(), result, expected);
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
