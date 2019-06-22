#! /usr/bin/python3

# 786. K-th Smallest Prime Fraction
# Hard
#
# A sorted list A contains 1, plus some number of primes.  Then, for every p < q in the list, we consider the fraction p/q.
#
# What is the K-th smallest fraction considered?  Return your answer as an array of ints, where answer[0] = p and answer[1] = q.
#
# Examples:
# Input: A = [1, 2, 3, 5], K = 3
# Output: [2, 5]
# Explanation:
# The fractions to be considered in sorted order are:
# 1/5, 1/3, 2/5, 1/2, 3/5, 2/3.
# The third fraction is 2/5.
#
# Input: A = [1, 7], K = 1
# Output: [1, 7]
#
# Note:
#
#     A will have length between 2 and 2000.
#     Each A[i] will be between 1 and 30000.
#     K will be between 1 and A.length * (A.length - 1) / 2.


from typing import List
from heapq import heappush, heappop

class Solution:
    def kthSmallestPrimeFraction(self, A, K):
        if K == 1: return A[0], A[-1]
        # Initialize our heap with A0/Ai (A0/Amax being the smallest)
        base = [(A[0]/A[i], 0, i, A[i]) for i in range(len(A)-1, 0, -1)]
        #print(base)
        for _ in range(K):
            (_, p, q, ai) = heappop(base)
            # Everytime a fraction pops out, it is the smallest and can be replaced by the same
            # fraction where we increase p (until p == q since it is 1)
            #print("Pop (%d, %d) -- %d/%d" % (p, q, A[p], A[q]))
            if p < (q - 1):
                #print("Push (%d, %d) -- %d/%d" % (p+1, q, A[p+1], A[q]))
                heappush(base, (A[p+1]/ai, p+1, q, ai))
        #print("K(%d) %d/%d = %f" % (K, A[p], A[q], A[p] / A[q]))
        return A[p], A[q]

def check_solution():
    s = Solution()

    A = [1, 2, 3, 5]
    K = 1
    p, q = s.kthSmallestPrimeFraction(A, K)
    assert((p == 1) and (q == 5))

    A = [1, 2, 3, 5]
    K = 3
    p, q = s.kthSmallestPrimeFraction(A, K)
    assert((p == 2) and (q == 5))

    A = [1, 2, 3, 5, 7]
    K = 5
    p, q = s.kthSmallestPrimeFraction(A, K)
    assert((p == 2) and (q == 5))

    A = [1,7,23,29,47]
    K = 8
    p, q = s.kthSmallestPrimeFraction(A, K)
    assert((p == 23) and (q == 47))

    print("All tests passed successfully!!")

check_solution()
