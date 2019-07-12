#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG
#define PERFS_TESTS_COUNT 15000

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

#ifdef DEBUG
const bool continue_on_failure = false;
#endif

#define DEAD    0
#define ALIVE   1
#define UNDEF   2

class Solution {
    /*int inline count_dead(int c1, int c2, int c3, int c4, int c6, int c7, int c8, int c9) {
        int dead = 0;
        if (c1 == DEAD) dead++;
        if (c2 == DEAD) dead++;
        if (c3 == DEAD) dead++;
        if (c4 == DEAD) dead++;
        if (c6 == DEAD) dead++;
        if (c7 == DEAD) dead++;
        if (c8 == DEAD) dead++;
        if (c9 == DEAD) dead++;
        return dead;
    }*/
    int inline count_alive(int c1, int c2, int c3, int c4, int c6, int c7, int c8, int c9) {
        int alive = 0;
        if (c1 == ALIVE) alive++;
        if (c2 == ALIVE) alive++;
        if (c3 == ALIVE) alive++;
        if (c4 == ALIVE) alive++;
        if (c6 == ALIVE) alive++;
        if (c7 == ALIVE) alive++;
        if (c8 == ALIVE) alive++;
        if (c9 == ALIVE) alive++;
        return alive;
    }
    int inline update_cell(int c1, int c2, int c3, int c4, int c5, int c6, int c7, int c8, int c9) {
        int alive = count_alive(c1,c2,c3,c4,c6,c7,c8,c9);
        if (c5 == DEAD)
            return (alive == 3) ? ALIVE : DEAD; // dead or reproduction
        if (alive < 2) return DEAD; // underpopulation
        return alive > 3 ? DEAD : ALIVE; // overpopulation or alive
    }
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();

        // cache c4 and the upper row
        vector<int> row0, row1 = board[0];

        int c1, c2, c3, c5, c6, c7, c8, c9;
        for (int y = 0 ; y < m ; y++) {
            int left0 = UNDEF;
            for (int x = 0 ; x < n ; x++) {
                c1 = (y > 0) and (x > 0) ? row0[x-1] : UNDEF;
                c2 = (y > 0) ? row0[x] : UNDEF;
                c3 = (y > 0) and ((x+1) < n) ? row0[x+1] : UNDEF;

                c5 = board[y][x];
                c6 = ((x+1) < n) ? board[y][x+1] : UNDEF;

                c7 = ((y+1) < m) and (x > 0) ? board[y+1][x-1] : UNDEF;
                c8 = ((y+1) < m) ? board[y+1][x] : UNDEF;
                c9 = ((y+1) < m) and ((x+1) < n) ? board[y+1][x+1] : UNDEF;

                board[y][x] = update_cell(c1,c2,c3, left0,c5,c6, c7,c8,c9);
                left0 = c5;
            }
            row0 = row1;
            if ((y+1) < m) row1 = board[y+1];
        }
    }
};

int run_test_case(void *_s, TestCase *tc)
{
    UNUSED(_s);
    vector<vector<int>> board = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<vector<int>> result = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    vector<vector<int>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    s.gameOfLife(result);

    if (check_result(result, expected)) return 0;

    printf("gameOfLife(%s) returned %s but expected %s\n", array2str(board).c_str(),
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
