/*
51. N-Queens
Hard

The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.

Example:

Input: 4
Output: [
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.
*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#define FREE_SPACE       0
#define QUEEN_SPACE      -1
#define QUEEN_PATH_SPACE 1

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

typedef int* board_t;
#define cell(board, n, row, col) board[n * row + col]


class Solution {
    vector<vector<string>> result;
    board_t board;
    int n;

    void set_queen(int row, int col) {
        int idx;
        int diag_row, diag_col;

        // mark the col
        for (idx = 0 ; idx < n ; idx++)
            if (idx != row)
                cell(board, n, idx, col) += QUEEN_PATH_SPACE;

        // mark the row
        for (idx = 0 ; idx < n ; idx++)
            if (idx != col)
                cell(board, n, row, idx) += QUEEN_PATH_SPACE;

        // mark the right diagonal
        diag_row = max(row - col, 0);
        diag_col = max(col - row, 0);
        for (; diag_row < n && diag_col < n ; diag_row++, diag_col++)
            if (idx != diag_row)
                cell(board, n, diag_row, diag_col) += QUEEN_PATH_SPACE;

        // mark the left diagonal
        diag_row = min(col + row, n - 1);
        diag_col = (col + row < n - 1 ? 0 : col + row - n + 1);
        for (; diag_row > -1 && diag_col < n ; diag_row--, diag_col++)
            if (idx != diag_row)
                cell(board, n, diag_row, diag_col) += QUEEN_PATH_SPACE;

        cell(board, n, row, col) = QUEEN_SPACE;
    }

    void reset_queen(int row, int col) {
        int idx;
        int diag_row, diag_col;

        // mark the col
        for (idx = 0 ; idx < n ; idx++)
            if (idx != row)
                cell(board, n, idx, col) -= QUEEN_PATH_SPACE;

        // mark the row
        for (idx = 0 ; idx < n ; idx++)
            if (idx != col)
                cell(board, n, row, idx) -= QUEEN_PATH_SPACE;

        // mark the right diagonal
        diag_row = max(row - col, 0);
        diag_col = max(col - row, 0);
        for (; diag_row < n && diag_col < n ; diag_row++, diag_col++)
            if (idx != diag_row)
                cell(board, n, diag_row, diag_col) -= QUEEN_PATH_SPACE;

        // mark the left diagonal
        diag_row = min(col + row, n - 1);
        diag_col = (col + row < n - 1 ? 0 : col + row - n + 1);
        for (; diag_row > -1 && diag_col < n ; diag_row--, diag_col++)
            if (idx != diag_row)
                cell(board, n, diag_row, diag_col) -= QUEEN_PATH_SPACE;

        cell(board, n, row, col) = FREE_SPACE;
    }

    void push_solution(board_t board) {
        vector<string> sboard = {};
        for (int idx = 0 ; idx < n ; idx++) {
            string row = string(n, '.');
            for (int jdx = 0 ; jdx < n ; jdx++)
                if (cell(board, n, idx, jdx) == QUEEN_SPACE)
                    row[jdx] = 'Q';
            sboard.push_back(row);
        }
        result.push_back(sboard);
    }

    void print_board(board_t board) {
        printf("Board:\n");
        for (int idx = 0 ; idx < n ; idx++) {
            string row = string(n*3, ' ');
            for (int jdx = 0 ; jdx < n ; jdx++)
                if (cell(board, n, idx, jdx) == QUEEN_SPACE)
                    row[3*jdx + 1] = 'Q';
                else if (cell(board, n, idx, jdx) == FREE_SPACE)
                    row[3 * jdx+ 1] = '.';
                else row[3 * jdx + 1] = 'o';
            printf("%s\n", row.c_str());
        }
    }
#ifdef DEBUG
    #define debug_print_board print_board
#else
    #define debug_print_board(...)
#endif

    void findnextqueen(int row_idx) {
#if DEBUG
        int sav_board[n][n];
        memcpy(sav_board, board, sizeof(sav_board));
#endif
        int col_idx = 0;
        while (col_idx < n) {
            if (cell(board, n, row_idx, col_idx) == FREE_SPACE) {
                set_queen(row_idx, col_idx);
                if (row_idx < n - 1)
                    findnextqueen(row_idx+1);
                else
                    push_solution(board);
                reset_queen(row_idx, col_idx);
#if DEBUG
                if (memcmp(sav_board, board, sizeof(sav_board))) {
                    printf("%s(%d)\n", __func__, row_idx);
                    print_board(board);
                    printf("should be\n");
                    print_board((board_t)sav_board);
                    assert(false);
                }
#endif
            }
            col_idx++;
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        if (n == 1) return {{"Q"}};
        if (n < 4) return {};
        int _board[n][n];
        this->n = n;
        result.clear();
        board = (board_t)_board;
        memset(board, FREE_SPACE, sizeof(_board));

        int col_idx = 0;
        while (col_idx < n) {
            set_queen(0, col_idx);
            findnextqueen(1);
            reset_queen(0, col_idx);
            col_idx++;
        }
        return result;
    }
};

int run_test_case(void *__s, TestCase *tc) {
        UNUSED(__s);
        int n = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        vector<vector<string>> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution _s;
        vector<vector<string>> result = _s.solveNQueens(n);

        if (result == expected) return 0;

        printf("solveNQueens(%d) returned %s but expected %s\n", n,
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
                cout << errors_count << " test(s) failed over a total of "
                        << tests_ran << endl;

        return errors_count;
}