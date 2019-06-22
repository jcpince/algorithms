#! /usr/bin/python3

# 796. Rotate String
# Easy
#
# We are given two strings, A and B.
#
# A shift on A consists of taking string A and moving the leftmost character to the rightmost position. For example, if A = 'abcde', then it will be 'bcdea' after one shift on A. Return True if and only if A can become B after some number of shifts on A.
#
# Example 1:
# Input: A = 'abcde', B = 'cdeab'
# Output: true
#
# Example 2:
# Input: A = 'abcde', B = 'abced'
# Output: false
#
# Note:
#
#     A and B will have length at most 100.
#


class Solution:
    def rotateString(self, A: str, B: str) -> bool:
        length = len(A)
        if length != len(B): return False
        if length == 0: return True

        start_char = A[0]
        offset = B.find(start_char)
        start_idx = offset
        # print("Find %s in %s returned %d" % (start_char, B[0:], start_idx))
        while offset != -1:
            # print("Compare %s to %s and then %s to %s" % (A[:length-start_idx],
            #     B[start_idx:], A[length-start_idx:], B[:start_idx]))
            if (A[:length-start_idx] == B[start_idx:]) and \
                    (A[length-start_idx:] == B[:start_idx]):
                return True
            if start_idx == length-1:
                break
            start_idx += 1 # skip the first character
            offset = B[start_idx:].find(start_char)
            # print("Find %s in %s returned %d" % (start_char, B[start_idx:], offset))
            start_idx += offset
        return False

def check_solution():
    s = Solution()

    assert(s.rotateString("abcde", "abced") == False)
    assert(s.rotateString("abcde", "abcde") == True)
    assert(s.rotateString("ohbrwzxvxe", "uornhegseo") == False)
    assert(s.rotateString("ohbrwzxvxe", "zxvxeohbrw") == True)
    assert(s.rotateString("ohbrwzxvxe", "hbrwzxvxeo") == True)

    print("All tests passed successfully!!")

check_solution()
