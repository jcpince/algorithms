#! /usr/bin/python3

# 794. Valid Tic-Tac-Toe State
# Medium
#
# A Tic-Tac-Toe board is given as a string array board. Return True if and only if it is possible to reach this board position during the course of a valid tic-tac-toe game.
#
# The board is a 3 x 3 array, and consists of characters " ", "X", and "O".  The " " character represents an empty square.
#
# Here are the rules of Tic-Tac-Toe:
#
#     Players take turns placing characters into empty squares (" ").
#     The first player always places "X" characters, while the second player always places "O" characters.
#     "X" and "O" characters are always placed into empty squares, never filled ones.
#     The game ends when there are 3 of the same (non-empty) character filling any row, column, or diagonal.
#     The game also ends if all squares are non-empty.
#     No more moves can be played if the game is over.
#
# Example 1:
# Input: board = ["O  ", "   ", "   "]
# Output: false
# Explanation: The first player always plays "X".
#
# Example 2:
# Input: board = ["XOX", " X ", "   "]
# Output: false
# Explanation: Players take turns making moves.
#
# Example 3:
# Input: board = ["XXX", "   ", "OOO"]
# Output: false
#
# Example 4:
# Input: board = ["XOX", "O O", "XOX"]
# Output: true
#
# Note:
#
#     board is a length-3 array of strings, where each string board[i] has length 3.
#     Each board[i][j] is a character in the set {" ", "X", "O"}.
from typing import List

import collections

class Solution:
    def validTicTacToe(self, board: List[str]) -> bool:
        allboard = board[0] + ' ' + board[1] + ' ' + board[2]
        c = collections.Counter(allboard)
        if (c['X'] != c['O']) and (c['X'] != (c['O'] + 1)):
            return False

        diag = board[0][0] + board[1][1] + board[2][2]
        if diag == 'XXX':
            return c['X'] == (c['O'] + 1)
        if diag == 'OOO':
            return c['X'] == c['O']

        diag = board[0][2] + board[1][1] + board[2][0]
        if diag == 'XXX':
            return c['X'] == (c['O'] + 1)
        if diag == 'OOO':
            return c['X'] == c['O']

        if allboard.find('XXX') != -1:
            if allboard.find('OOO') != -1:
                return False
            return c['X'] == (c['O'] + 1)
        if allboard.find('OOO') != -1:
            return c['X'] == c['O']

        allboard = board[0][0] + board[1][0] + board[2][0] + ' ' + \
                board[0][1] + board[1][1] + board[2][1] + ' ' + \
                board[0][2] + board[1][2] + board[2][2]

        if (allboard.find('XXX') != -1):
            if (allboard.find('OOO') != -1):
                return False
            return c['X'] == (c['O'] + 1)
        if allboard.find('OOO') != -1:
            return c['X'] == c['O']

        return True

def check_solution():
    s = Solution()

    board = ["O  ", "   ", "   "]
    assert(s.validTicTacToe(board) == False)

    board = ["XOX", " X ", "   "]
    assert(s.validTicTacToe(board) == False)

    board = ["XXX", "   ", "OOO"]
    assert(s.validTicTacToe(board) == False)

    board = ["XOX", "XOO", "XO "]
    assert(s.validTicTacToe(board) == False)

    board = ["XOX", "XOO", "X  "]
    assert(s.validTicTacToe(board) == True)

    board = ["XOX", "XOO", "X O"]
    assert(s.validTicTacToe(board) == False)

    board = ["XOX", "O O", "XOX"]
    assert(s.validTicTacToe(board) == True)

    board = ["XXX", "O O", "   "]
    assert(s.validTicTacToe(board) == True)

    board = ["XXX","XOO","OO "]
    assert(s.validTicTacToe(board) == False)

    board = ["XXO","XOX","OXO"]
    assert(s.validTicTacToe(board) == False)

    print("All tests passed successfully!!")

check_solution()
