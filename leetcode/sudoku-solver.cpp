#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

#define CELL_MASK 0x3fe // 9 numbers from 1 to 9
#define c2n(c) (c - '0')
#define n2c(n) ('0' + n)
#define DBL_CHECK 1

class Solution {
        struct context {
                int board[9][9] = {{0}};
                uint16_t rows[9] = {0};
                uint16_t columns[9] = {0};
                uint16_t suboxes[9] = {0};
                int guess_number = 0;
                int bet_values;
                int bet_row;
                int bet_col;
                context(struct context *ctx) {
                        memcpy(this, ctx, sizeof(struct context));
                }
                context() {
                        memset(this, 0, sizeof(struct context));
                }
        } __attribute__((packed, aligned(8)));
        const vector<vector<char>> solution;
        stack<struct context *> history;
        int coord2box(int row, int col) {
                int xoff = col / 3;
                if (row < 3)
                return xoff;
                else if (row < 6)
                return 3 + xoff;
                else
                return 6 + xoff;
        }
        string mask2binary(int mask) {
                string res = "0b";
                for (int i = 9 ; i >= 0 ; i--)
                        res += mask & 1<<i ? "1" : "0";
                return res;
        }
        // https://stackoverflow.com/questions/109023/how-to-count-the-number-of-set-bits-in-a-32-bit-integer
        // 'Hamming Weight', 'popcount' or 'sideways addition'
        uint32_t numberOfSetBits(uint32_t i) {
             // Java: use >>> instead of >>
             // C or C++: use uint32_t
             i = i - ((i >> 1) & 0x55555555);
             i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
             return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
        }
        void fillContext(const vector<vector<char>> &_board,
                                struct context &ctx) {
                int row_index = 0, box_index;
                for (const vector<char> row : _board) {
                        int col_index = -1;
                        for ( char c : row) {
                                int num = c2n(c);
                                col_index++;
                                box_index = coord2box(row_index, col_index);
                                if (c == '.' && ++ctx.guess_number) continue;
                                ctx.rows[row_index] |= 1 << num;
                                ctx.suboxes[box_index] |= 1 << num;
                                ctx.columns[col_index] |= 1 << num;
                                ctx.board[row_index][col_index] = num;
                        }
                        row_index++;
                }
        }
        void direct_solve(struct context& ctx) {
                int row_index, box_index;
                for (row_index = 0 ; row_index < 9 ; row_index++) {
                        int col_index;
                        if (ctx.rows[row_index] == CELL_MASK) // This row is filled already
                                continue;
                        for (col_index = 0 ; col_index < 9 ; col_index++) {
                                if (ctx.board[row_index][col_index]) // this cell is filled
                                        continue;
                                box_index = coord2box(row_index, col_index);
                                int allgroups = ctx.rows[row_index] | ctx.columns[col_index] | ctx.suboxes[box_index];
                                // just make sure that nothing out of bounds has been set
                                if ((allgroups | CELL_MASK) != CELL_MASK) {
                                        printf("Invalid allgroups 0x%x!!!\n", allgroups);
                                        printf("ctx.rows[%d]: 0x%x\n", row_index, ctx.rows[row_index]);
                                        printf("ctx.columns[%d]: 0x%x\n", col_index, ctx.columns[col_index]);
                                        printf("ctx.suboxes[%d]: 0x%x\n", box_index, ctx.suboxes[box_index]);
                                }
                                assert((allgroups | CELL_MASK) == CELL_MASK);
                                // printf("ctx.board[%d][%d]: %s\n",
                                //         row_index, col_index,
                                //         mask2binary(allgroups).c_str());
                                allgroups = (~allgroups & CELL_MASK);
                                uint32_t bits = numberOfSetBits(allgroups);
                                // assert((allgroups | CELL_MASK) == CELL_MASK);
                                // printf("ctx.board[%d][%d]: %s : %d bits set\n",
                                //         row_index, col_index,
                                //         mask2binary(allgroups).c_str(),
                                //         bits);
                                if (bits == 1) {
                                        // We have a solution for this cell
                                        int num = __builtin_ffs(allgroups) - 1;
                                        // printf("ctx.board[%d][%d]: %s : 1 bits set at pos %d => %d\n",
                                        //          row_index, col_index,
                                        //          mask2binary(allgroups).c_str(),
                                        //          val, num);
                                        ctx.board[row_index][col_index] = num;
                                        ctx.guess_number--;
                                        ctx.rows[row_index] |= 1 << num;
                                        ctx.suboxes[box_index] |= 1 << num;
                                        ctx.columns[col_index] |= 1 << num;
                                }
                        }
                }
        }
        int number_based_solve(struct context& ctx) {
                int box_index;

                for (int number = 1 ; number <= 9 ; number++) {
                        uint16_t num_mask = 1 << number;
                        for (int row_index = 0 ; row_index < 9 ; row_index+= 3) {
                                uint16_t row0 = ctx.rows[row_index];
                                uint16_t row1 = ctx.rows[row_index+1];
                                uint16_t row2 = ctx.rows[row_index+2];
                                int count = (row0 & num_mask ? 1 : 0) +
                                        (row1 & num_mask ? 1 : 0) +
                                        (row2 & num_mask ? 1 : 0);
                                if (count != 2) // check if only one is missing
                                        continue;
                                for (int col_index = 0 ; col_index < 9 ; col_index+= 3) {
                                        box_index = coord2box(row_index, col_index);
                                        if (ctx.suboxes[box_index] & num_mask) // check if this box is missing the num
                                                continue;

                                        uint16_t col0 = ctx.columns[col_index];
                                        uint16_t col1 = ctx.columns[col_index+1];
                                        uint16_t col2 = ctx.columns[col_index+2];
                                        count = (col0 & num_mask ? 1 : 0) +
                                                (col1 & num_mask ? 1 : 0) +
                                                (col2 & num_mask ? 1 : 0);
                                        if (count != 2) // right box but wrong condition
                                                break;

                                        /* Here, we have twice the num in the ctx.rows and ctx.columns groups */
                                        int cell_row_index = row0 & num_mask ? (row1 & num_mask ? row_index + 2 : row_index + 1) : row_index;
                                        int cell_col_index = col0 & num_mask ? (col1 & num_mask ? col_index + 2 : col_index + 1) : col_index;
                                        if (ctx.board[cell_row_index][cell_col_index]) {
                                                assert(!history.empty());
                                                // wrong bet
                                                return -1;
                                        }
                                        ctx.guess_number--;
                                        ctx.board[cell_row_index][cell_col_index] = number;
                                        ctx.rows[cell_row_index] |= 1 << number;
                                        ctx.suboxes[box_index] |= 1 << number;
                                        ctx.columns[cell_col_index] |= 1 << number;
                                        /*if (DBL_CHECK &&
                                                        solution[cell_row_index][cell_col_index] != n2c(number)) {
                                                printf("Setting ctx.board[%d][%d] to %d was a wrong decision!!!\n",
                                                        cell_row_index, cell_col_index, number);
                                                printBoard("board", (const int **)ctx.board);
                                                printBoard("solution", solution);
                                                abort();
                                        }*/
                                }
                        }
                }
                return 0;
        }
        struct context *apply_next_bet(struct context *ctx) {
                int new_bet = __builtin_ffs(ctx->bet_values) - 1;
                // printf("board[%d][%d] new candidate: %d\n",
                //         ctx->bet_row, ctx->bet_col, new_bet);
                ctx->bet_values &= ~(1 << new_bet) & CELL_MASK;
                ctx->board[ctx->bet_row][ctx->bet_col] = new_bet;
                if (ctx->bet_values)
                        history.push(ctx);
                ctx = new struct context(ctx);
                ctx->rows[ctx->bet_row] |= 1 << new_bet;
                int box_index = coord2box(ctx->bet_row, ctx->bet_col);
                ctx->suboxes[box_index] |= 1 << new_bet;
                ctx->columns[ctx->bet_col] |= 1 << new_bet;
                int allgroups = ctx->rows[ctx->bet_row] | ctx->columns[ctx->bet_col] | ctx->suboxes[box_index];
                // just make sure that nothing out of bounds has been set
                if ((allgroups | CELL_MASK) != CELL_MASK) {
                        printf("Invalid allgroups 0x%x!!!\n", allgroups);
                        printf("ctx.rows[%d]: 0x%x\n", ctx->bet_row, ctx->rows[ctx->bet_row]);
                        printf("ctx.columns[%d]: 0x%x\n", ctx->bet_col, ctx->columns[ctx->bet_col]);
                        printf("ctx.suboxes[%d]: 0x%x\n", box_index, ctx->suboxes[box_index]);
                }
                assert((allgroups | CELL_MASK) == CELL_MASK);
                return ctx;
        }
        int find_first_unknown(struct context& ctx) {
                for (int idx = 0 ; idx < 9 ; idx++) {
                        for (int jdx = 0 ; jdx < 9 ; jdx++) {
                                if (!ctx.board[idx][jdx]) {
                                        ctx.bet_values = 0;
                                        ctx.bet_row = idx;
                                        ctx.bet_col = jdx;
                                        int box_index = coord2box(idx, jdx);
                                        //printf("board[%d][%d] candidates: ", idx, jdx);
                                        for (int kdx = 1 ; kdx <= 9 ; kdx++) {
                                                int mask = 1 << kdx;
                                                if (ctx.rows[idx] & mask ||
                                                        ctx.columns[jdx] & mask ||
                                                        ctx.suboxes[box_index] & mask)
                                                        continue;
                                                //printf("%d, ", kdx);
                                                ctx.bet_values |= mask;
                                        }
                                        //printf("\n");
                                        return ctx.bet_values;
                                }
                        }
                }
                return 0;
        }
public:
        Solution(const vector<vector<char>> &solution): solution(solution) {}
        Solution() {}
        void printBoard(const char *name, const vector<vector<char>>& board) {
                printf("%s:\n", name);
                for (const vector<char> row : board) {
                        for ( char c : row)
                                if (c == '.') printf(" .,");
                                else printf(" %d,", c - '0');
                        printf("\n");
                }
        }
        void printBoard(const char *name, const int (&board)[9][9]) {

                printf("%s:\n", name);
                for (int idx = 0 ; idx < 9 ; idx++) {
                        for (int jdx = 0 ; jdx < 9 ; jdx++) {
                                int n = board[idx][jdx];
                                if (!n) printf(" .,");
                                else printf(" %d,", n);
                        }
                        printf("\n");
                }
        }
        bool isValidSudoku(const vector<vector<char>>& board) {
                int cols[9][9] = {{0}}, bx[9][9] = {{0}};
                int row_index = 0, box_index;

                for (const vector<char> row : board) {
                        int curr_row[9] = {0}, col_index = -1;
                        for ( char c : row) {
                                int num = c2n(c) - 1;
                                col_index++;
                                box_index = coord2box(row_index, col_index);
                                if (c == '.') continue;
                                // printf("board[%d][%d] is %d\n",
                                //         row_index, col_index, num+1);
                                if (curr_row[num]) {
                                        // printf("%c(%d) already in the row %d\n",
                                        //         c, num+1, row_index);
                                        return false;
                                }
                                if (cols[col_index][num]) {
                                        // printf("%c(%d) already in the col %d\n",
                                        //         c, num+1, col_index);
                                        return false;
                                }
                                if (bx[box_index][num]) {
                                        // printf("%c(%d) already in the box %d\n",
                                        //         c, num+1, box_index);
                                        return false;
                                }
                                curr_row[num] = 1;
                                cols[col_index][num] = 1;
                                bx[box_index][num] = 1;
                        }
                        row_index++;
                }
                return true;
        }
        bool isValidSudoku(struct context& ctx) {
                int cols[9][9] = {{0}}, bx[9][9] = {{0}};

                for (int row_index = 0 ; row_index < 9 ; row_index++) {
                        int curr_row[9] = {0}, box_index;
                        for (int col_index = 0 ; col_index < 9 ; col_index++) {
                                int num = ctx.board[row_index][col_index] - 1;
                                if (num == -1) continue;
                                // printf("board[%d][%d] is %d\n",
                                //         row_index, col_index, num+1);
                                if (curr_row[num]) {
                                        // printf("%c(%d) already in the row %d\n",
                                        //         c, num+1, row_index);
                                        return false;
                                }
                                if (cols[col_index][num]) {
                                        // printf("%c(%d) already in the col %d\n",
                                        //         c, num+1, col_index);
                                        return false;
                                }
                                box_index = coord2box(row_index, col_index);
                                if (bx[box_index][num]) {
                                        // printf("%c(%d) already in the box %d\n",
                                        //         c, num+1, box_index);
                                        return false;
                                }
                                curr_row[num] = 1;
                                cols[col_index][num] = 1;
                                bx[box_index][num] = 1;
                        }
                }
                return true;
        }
        void solveSudoku(vector<vector<char>>& _board) {

                int guess_number0 = 81;
                struct context *ctx = new struct context();

                /* build our representation */
                fillContext(_board, *ctx);

                /* Now, fill the board */
                //printf("The board has %d cells to fill\n", ctx->guess_number);
                while(ctx->guess_number) {
                        guess_number0 = ctx->guess_number;
                        direct_solve(*ctx);
                        if (number_based_solve(*ctx) < 0 || !isValidSudoku(*ctx)) {
                                // printf("Invalid move!!!\n");
                                // printf("Wrong guess, try the next...\n");
                                if (history.empty()) {
                                        printf("History empty, abort\n");
                                        return;
                                }
                                delete ctx;
                                ctx = history.top();
                                history.pop();
                                ctx = apply_next_bet(ctx);
                        } else if (ctx->guess_number && ctx->guess_number == guess_number0) {
                                /* time to guess something */
                                // printf("Dead end, %d still to guess, try a guess...\n", ctx->guess_number);
                                // printBoard("Dead end board", ctx->board);
                                if (find_first_unknown(*ctx)) {
                                        ctx->guess_number--;
                                        ctx = apply_next_bet(ctx);
                                        // printf("board[0][0]=%d\n", ctx->board[0][0]);
                                        // printf("history.board[0][0]=%d\n", history.top()->board[0][0]);

                                }
                                else {
                                        if (history.empty()) {
                                                printf("History empty, abort\n");
                                                abort();
                                        }
                                        delete ctx;
                                        ctx = history.top();
                                        //printBoard("Restored board from history", ctx->board);
                                        history.pop();
                                        ctx = apply_next_bet(ctx);
                                }
                        }
                }
                if (ctx->guess_number)
                        printf("Still %d numbers to guess...\n",
                                ctx->guess_number);

                /* Commit the changes */
                for (int idx = 0 ; idx < 9 ; idx++) {
                        for (int jdx = 0 ; jdx < 9 ; jdx++) {
                                if (_board[idx][jdx] == '.' && ctx->board[idx][jdx])
                                        _board[idx][jdx] = ctx->board[idx][jdx] + '0';
                        }
                }
                delete ctx;
                while(!history.empty()) {
                        ctx = history.top();
                        history.pop();
                        delete ctx;
                }
        }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<vector<string>> sboard = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        vector<vector<string>> sexp = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        /* vector<vector<string>> to vector<vector<char>>*/
        vector<vector<char>> board, board0;
        for ( vector<string> row : sboard) {
                vector<char> crow;
                for ( string num : row)
                        crow.push_back(num[0]);
                board.push_back(crow);
                board0.push_back(crow);
        }
        vector<vector<char>> expected;
        for ( vector<string> row : sexp) {
                vector<char> crow;
                for ( string num : row)
                crow.push_back(num[0]);
                expected.push_back(crow);
        }
        Solution s(expected);

        if (!s.isValidSudoku(board)) {
                printf("Initial board(%s) is not valid!\n",
                        array2str(sboard).c_str());
                abort();
        }

        if (!s.isValidSudoku(expected)) {
                printf("Expected board(%s) is not valid!\n",
                        array2str(sexp).c_str());
                abort();
        }

        s.solveSudoku(board);

        vector<vector<string>> sresult;
        for ( vector<char> row : board) {
                vector<string> crow;
                for ( char num : row)
                crow.push_back(string(1, num));
                sresult.push_back(crow);
        }

        if (board == expected) return 0;

        printf("solveSudoku() failed\n");
        s.printBoard("Initial board", board0);
        s.printBoard("Result", board);
        s.printBoard("Solution", expected);
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
