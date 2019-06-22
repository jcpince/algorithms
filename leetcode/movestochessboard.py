#! /usr/bin/python3

# 782. Transform to Chessboard
# Hard
#
# An N x N board contains only 0s and 1s. In each move, you can swap any 2 rows with each other, or any 2 columns with each other.
#
# What is the minimum number of moves to transform the board into a "chessboard" - a board where no 0s and no 1s are 4-directionally adjacent? If the task is impossible, return -1.
#
# Examples:
# Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
# Output: 2
# Explanation:
# One potential sequence of moves is shown below, from left to right:
#
# 0110     1010     1010
# 0110 --> 1010 --> 0101
# 1001     0101     1010
# 1001     0101     0101
#
# The first move swaps the first and second column.
# The second move swaps the second and third row.
#
#
# Input: board = [[0, 1], [1, 0]]
# Output: 0
# Explanation:
# Also note that the board with 0 in the top left corner,
# 01
# 10
#
# is also a valid chessboard.
#
# Input: board = [[1, 0], [1, 0]]
# Output: -1
# Explanation:
# No matter what sequence of moves you make, you cannot end with a valid chessboard.
#
# Note:
#
#     board will have the same number of rows and columns, a number in the range [2, 30].
#     board[i][j] will be only 0s or 1s.



from typing import List

class Solution:
    def movesToChessboard(self, board: List[List[int]]) -> int:
        row0 = board[0]
        chess_size = len(row0)
        if not self.check_init_cond(board, row0):
            #print("Init cond failed for board %s" % str(board))
            return -1

        # The board is movable
        first_is_one = self.check_row_1first(row0)
        #print("Swap columns for board %s -- first_is_one is %s" % (board, first_is_one))
        swap_count = 0
        expected_cell = 1 if first_is_one else 0
        for idx in range(len(row0)-1):
            cell = row0[idx]
            if cell != expected_cell:
                # find the swap
                swapped = False
                swap_count += 1
                #print("Looking for a column to swap index %d" % (idx))
                for jdx in range(idx+1, chess_size, 2):
                    if row0[jdx] == expected_cell:
                        swapped = True
                        #print("Found the column %d to swap with %d" % (jdx, idx))
                        self.swap_columns(board, idx, jdx)
                        row0 = board[0]
                        break
                assert(swapped)
            expected_cell = 1 if (expected_cell == 0) else 0

        first_is_one = self.check_column_1first(board)
        #print("Swap rows for board %s -- first_is_one is %s" % (board, first_is_one))
        expected_cell = 1 if first_is_one else 0
        for idx in range(len(board)-1):
            row = board[idx]
            if row[0] != expected_cell:
                # find the swap
                swapped = False
                swap_count += 1
                #print("Looking for a row to swap index %d" % (idx))
                for jdx in range(idx+1, chess_size, 2):
                    if board[jdx][0] == expected_cell:
                        swapped = True
                        #print("Found the row %d to swap with %d" % (jdx, idx))
                        self.swap_rows(board, idx, jdx)
                        break
                assert(swapped)
            expected_cell = 1 if (expected_cell == 0) else 0
        #print("%d swaps for %s" % (swap_count, board))
        return swap_count

    def swap_rows(self, board, index0, index1):
        if index0 == index1: assert(False)
        if index0 >= index1:
            index0, index1 = index1, index0
        l1 = board.pop(index1)
        l0 = board.pop(index0)
        board.insert(index0, l1)
        board.insert(index1, l0)

    def swap_columns(self, board, index0, index1):
        if index0 == index1: assert(False)
        for row in board:
            tmp = row[index0]
            row[index0] = row[index1]
            row[index1] = tmp

    def check_init_cond(self, board, row0):
        diff = 1
        ones = 0
        #print("check ones")
        for cell in row0:
            if cell == 1: ones += 1
        #print("Found %d ones" % ones)
        if (len(row0) % 2) == 0:
            if ones != len(row0)/2: return False
        elif (ones != int(len(row0)/2)) and (ones != int((len(row0)/2) + 1)): return False

        #print("check diff")
        for row in board[1:]:
            same_or_invert = self.is_same_or_invert_row(row0, row)
            if same_or_invert == 0: return False
            diff += same_or_invert
        #print(diff)
        if diff != -1 and diff != 0 and diff != 1: return False
        return True

    def is_same_or_invert_row(self, ref, row):
        if ref[0] == row[0]:
            for idx, e in enumerate(row[1:]):
                if e != ref[idx+1]: return 0
        else:
            for idx, e in enumerate(row[1:]):
                if e == ref[idx+1]: return 0
        return 1 if ref[0] == row[0] else -1

    def check_row_1first(self, row):
        # Find the right columns order, check 1s first
        ones_placed = 0
        ones = 0
        for idx in range(len(row)):
            if row[idx] == 1:
                ones += 1
                if idx % 2 == 0:
                    ones_placed += 1
        if ones < (len(row) / 2):
            return False
        if ones > (len(row) / 2):
            return True
        if ones_placed > (ones / 2):
            return True
        elif ones_placed == (ones / 2):
            return (row[0] == 1)
        return False

    def check_column_1first(self, board):
        # Find the right rows order, check 1s first
        ones_placed = 0
        ones = 0
        for idx in range(len(board)):
            if board[idx][0] == 1:
                ones += 1
                if idx % 2 == 0:
                    ones_placed += 1
        # if there are less 1s than 0s, it's 0s first
        if ones < (len(board) / 2):
            return False
        if ones > (len(board) / 2):
            return True
        if ones_placed > (ones / 2):
            return True
        elif ones_placed == (ones / 2):
            return (board[idx][0] == 1)
        return False

def check_solution():
    s = Solution()

    board = [[0, 1], [1, 0]]
    result = s.movesToChessboard(board)
    assert(result == 0)

    board = [[0, 1, 0, 1], [1, 0, 1, 0], [0, 1, 0, 1], [1, 0, 1, 0]]
    result = s.movesToChessboard(board)
    assert(result == 0)

    board = [[0, 1, 0, 1], [1, 0, 1, 0], [1, 0, 1, 0], [1, 0, 1, 0]]
    result = s.movesToChessboard(board)
    assert(result == -1)

    board = [[1, 1, 0, 1], [1, 0, 1, 0], [1, 0, 1, 0], [1, 0, 1, 0]]
    result = s.movesToChessboard(board)
    assert(result == -1)

    board = [[1, 0], [1, 0]]
    result = s.movesToChessboard(board)
    assert(result == -1)

    board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
    result = s.movesToChessboard(board)
    assert(result == 2)

    board = [   [1,0,0,1,0,0,1,1],
                [0,1,1,0,1,1,0,0],
                [0,1,1,0,1,1,0,0],
                [1,0,0,1,0,0,1,1],
                [1,0,0,1,0,0,1,1],
                [0,1,1,0,1,1,0,0],
                [1,0,0,1,0,0,1,1],
                [0,1,1,0,1,1,0,0]]
    result = s.movesToChessboard(board)
    assert(result == 3)

    board = [   [0,1,1,0,1,1,0,0],
                [0,1,1,0,1,1,0,0],
                [1,0,0,1,0,0,1,1],
                [1,0,0,1,0,0,1,1],
                [1,0,0,1,0,0,1,1],
                [0,1,1,0,1,1,0,0],
                [1,0,0,1,0,0,1,1],
                [0,1,1,0,1,1,0,0]]
    result = s.movesToChessboard(board)
    assert(result == 3)

    board = [   [1,1,0],
                [0,0,1],
                [0,0,1]]
    result = s.movesToChessboard(board)
    assert(result == 2)

    board = [   [1,0,0],
                [0,1,1],
                [1,0,0]]
    result = s.movesToChessboard(board)
    assert(result == 1)

    board = [   [0,0,0,0,1,1,0,1,0,1,1],
                [1,1,1,1,0,0,1,0,1,0,0],
                [1,1,1,1,0,0,1,0,1,0,0],
                [0,0,0,0,1,1,0,1,0,1,1],
                [0,0,0,0,1,1,0,1,0,1,1],
                [1,1,1,1,0,0,1,0,1,0,0],
                [1,1,1,1,0,0,1,0,1,0,0],
                [1,1,1,1,0,0,1,0,1,0,0],
                [0,0,0,0,1,1,0,1,0,1,1],
                [1,1,1,1,0,0,1,0,1,0,0],
                [0,0,0,0,1,1,0,1,0,1,1]]
    result = s.movesToChessboard(board)
    assert(result == 6)

    board = [   [0,1,1,0,1,1,0,1,0,1,0,1,0],
                [1,0,0,1,0,0,1,0,1,0,1,0,1],
                [1,0,0,1,0,0,1,0,1,0,1,0,1],
                [1,0,0,1,0,0,1,0,1,0,1,0,1],
                [1,0,0,1,0,0,1,0,1,0,1,0,1],
                [0,1,1,0,1,1,0,1,0,1,0,1,0],
                [0,1,1,0,1,1,0,1,0,1,0,1,0],
                [0,1,1,0,1,1,0,1,0,1,0,1,0],
                [0,1,1,0,1,1,0,1,0,1,0,1,0],
                [1,0,0,1,0,0,1,0,1,0,1,0,1],
                [0,1,1,0,1,1,0,1,0,1,0,1,0],
                [1,0,0,1,0,0,1,0,1,0,1,0,1],
                [1,0,0,1,0,0,1,0,1,0,1,0,1]]
    result = s.movesToChessboard(board)
    assert(result == 9)

    #print("All tests passed successfully!!")

check_solution()
