#! /usr/bin/python3

# 795. Number of Subarrays with Bounded Maximum
# Medium
#
# We are given an array A of positive integers, and two positive integers L and R (L <= R).
#
# Return the number of (contiguous, non-empty) subarrays such that the value of the maximum array element in that subarray is at least L and at most R.
#
# Example :
# Input:
# A = [2, 1, 4, 3]
# L = 2
# R = 3
# Output: 3
# Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].
#
# Note:
#
#     L, R  and A[i] will be an integer in the range [0, 10^9].
#     The length of A will be in the range of [1, 50000].

from typing import List

import collections

class Solution:
    def serie_sum(self, n):
        return (n * (n+1)) / 2

    def numSliceSubarrays(self, A: List[int], L: int) -> int:

        return 0

    def numSubarrayBoundedMax(self, A: List[int], L: int, R: int) -> int:
        nb = 0
        current_size = 0
        current_low = 0
        for e in A:
            if e < L:
                current_low += 1
            elif e <= R:
                current_size += 1
            else:
                if current_size > 0:
                    if current_low == 0:
                        nb += self.serie_sum(current_size)
                    #print("e(%d), current_low(%d), current_size(%d)" % (e, current_low, current_size))
                    else:
                        nb += self.serie_sum(current_low + current_size) - current_low
                        #print("nb set to %d" % nb)
                current_size = 0
                current_low = 0
        # last segment if any
        if current_size > 0:
            nb += self.serie_sum(current_low + current_size) - current_low
            #print("nb set to %d" % nb)
        return nb

def check_solution():
    s = Solution()

    assert(s.numSubarrayBoundedMax([2,1,4,3], 2, 3) == 3)
    assert(s.numSubarrayBoundedMax([2,1,3,4,3], 2, 3) == 6)
    assert(s.numSubarrayBoundedMax([1,2,3,2,1,4], 2, 3) == 13)
    assert(s.numSubarrayBoundedMax([1,2,3,2,1,4], 3, 3) == 9)
    assert(s.numSubarrayBoundedMax([3,2,3,2,3,4], 2, 3) == 15)
    assert(s.numSubarrayBoundedMax([3,1,1,1,1,4], 2, 3) == 5)
    assert(s.numSubarrayBoundedMax([3,1,1,1,1,4], 3, 3) == 5)

    print("All tests passed successfully!!")

check_solution()
