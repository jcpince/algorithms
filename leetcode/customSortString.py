#! /usr/bin/python3

# 791. Custom Sort String
# Medium
#
# S and T are strings composed of lowercase letters. In S, no letter occurs more than once.
#
# S was sorted in some custom order previously. We want to permute the characters of T so that they match the order that S was sorted. More specifically, if x occurs before y in S, then x should occur before y in the returned string.
#
# Return any permutation of T (as a string) that satisfies this property.
#
# Example :
# Input:
# S = "cba"
# T = "abcd"
# Output: "cbad"
# Explanation:
# "a", "b", "c" appear in S, so the order of "a", "b", "c" should be "c", "b", and "a".
# Since "d" does not appear in S, it can be at any position in T. "dcba", "cdba", "cbda" are also valid outputs.
#
#
#
# Note:
#
#     S has length at most 26, and no character is repeated in S.
#     T has length at most 200.
#     S and T consist of lowercase letters only.

class Solution:
    def customSortString(self, S: str, T: str) -> str:
        origin = ord('a')
        sorted_t = [[] for _ in range(26)]
        pos_s = [25 for _ in range(26)]
        for idx, c in enumerate(S):
            pos_s[ord(c) - origin] = idx
        for c in T:
            sorted_t[pos_s[ord(c) - origin]].append(c)
        result = ''
        for g in sorted_t[:-1]:
            if len(g) != 0:
                result += g[0] * len(g)
        for c in sorted_t[-1]:
            result += c
        return result
