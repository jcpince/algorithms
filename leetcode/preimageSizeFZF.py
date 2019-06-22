#! /usr/bin/python3

# 793. Preimage Size of Factorial Zeroes Function
# Hard
#
# Let f(x) be the number of zeroes at the end of x!. (Recall that x! = 1 * 2 * 3 * ... * x, and by convention, 0! = 1.)
#
# For example, f(3) = 0 because 3! = 6 has no zeroes at the end, while f(11) = 2 because 11! = 39916800 has 2 zeroes at the end. Given K, find how many non-negative integers x have the property that f(x) = K.
#
# Example 1:
# Input: K = 0
# Output: 5
# Explanation: 0!, 1!, 2!, 3!, and 4! end with K = 0 zeroes.
#
# Example 2:
# Input: K = 5
# Output: 0
# Explanation: There is no x such that x! ends in K = 5 zeroes.
#
# Note:
#
#     K will be an integer in the range [0, 10^9].
#


last_fact = 1
cache = {last_fact: 1}

def fact(N):
    global last_fact, cache
    if N < 2:
        return 1
    if N in cache:
        return cache[N]
    result = cache[last_fact]
    for i in range(last_fact+1, N+1):
        result = result * i
        cache[i] = result
    return cache[N]

def f(N):
    result = fact(N)
    nb0s = 0
    while result % 10 == 0:
        result = result // 10
        nb0s += 1
    return nb0s

class Solution:
    def trailing_0s(self, N):
        nb_0s = 0
        current_factor = 5
        while N >= current_factor:
            nb_0s += N // current_factor
            current_factor *= 5
        return nb_0s

    def preimageSizeFZF(self, K: int) -> int:
        min_boundary = K * 4
        max_boundary = max(min_boundary + 2, K * 5.5)
        assert(self.trailing_0s(min_boundary) <= K)
        assert(self.trailing_0s(max_boundary) >= K)
        while min_boundary != max_boundary:
            #print("Check between %d and %d" % (min_boundary, max_boundary))
            delta_half = (max_boundary - min_boundary) // 2
            if delta_half == 0:
                break
            nb_0s = self.trailing_0s(min_boundary + delta_half)
            #print("self.trailing_0s(%d) returned %d" % (min_boundary + delta_half, nb_0s))
            if nb_0s == K: return 5
            if nb_0s > K:
                max_boundary = min_boundary + max(delta_half, 1)
            else:
                min_boundary += max(delta_half, 1)
        return 0


def check_solution():
    s = Solution()
    assert(s.preimageSizeFZF(25) == 5)
    assert(s.preimageSizeFZF(3) == 5)
    assert(s.preimageSizeFZF(1) == 5)
    assert(s.preimageSizeFZF(11) == 0)
    assert(s.preimageSizeFZF(12) == 5)
    assert(s.preimageSizeFZF(28) == 5)
    assert(s.preimageSizeFZF(29) == 0)
    assert(s.preimageSizeFZF(30) == 0)
    assert(s.preimageSizeFZF(31) == 5)
    assert(s.preimageSizeFZF(79) == 0)
    assert(s.preimageSizeFZF(311) == 0)
    assert(s.preimageSizeFZF(28245) == 5)
    assert(s.preimageSizeFZF(28246) == 0)
    assert(s.preimageSizeFZF(28247) == 0)
    assert(s.preimageSizeFZF(28248) == 5)

check_solution()
print("All tests succeeded!!")
