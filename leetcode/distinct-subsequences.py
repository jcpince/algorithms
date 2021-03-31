# 115. Distinct Subsequences
# Hard
#
# Given two strings s and t, return the number of distinct subsequences of s which equals t.
#
# A string's subsequence is a new string formed from the original string by deleting some (can be none) of the characters without disturbing the remaining characters' relative positions. (i.e., "ACE" is a subsequence of "ABCDE" while "AEC" is not).
#
# It is guaranteed the answer fits on a 32-bit signed integer.
#
# Example 1:
# Input: s = "rabbbit", t = "rabbit"
# Output: 3
#
# Example 2:
# Input: s = "babgbag", t = "bag"
# Output: 5
#
# Constraints:
#
#     1 <= s.length, t.length <= 1000
#     s and t consist of English letters.

# Solution: Build a 2D array with s as columns and t as rows starting from ""
# dp[i][j] represents the solution of s[:j], t[:i] which is:
# dp[i][j-1] if s[j] != t[i]
# dp[i][j-1] + dp[i-1][j-1] if s[j] == t[i]

debug = False
def dbg_print(*args):
    global debug
    if debug:
        print("%s" % args)

class SolutionBase:
    def numDistinct(self, s: str, t: str) -> int:
        tlen = len(t)
        slen = len(s)
        if slen < tlen: return 0
        if slen == tlen:
            if s == t: return 1
            else: return 0
        if tlen == 0: return 1

        dp = [[1] * (slen+1)]
        for i in range(tlen):
            dp.append([0] * (slen+1))
        dbg_print(dp[0])
        for i in range(1, tlen+1):
            for j in range(1, slen+1):
                dp[i][j] = dp[i][j-1]
                if s[j-1] == t[i-1]:
                    dp[i][j] += dp[i-1][j-1]
            dbg_print(dp[i])
        return dp[tlen][slen]

# Now, simply uses two rows
class Solution1:
    def numDistinct(self, s: str, t: str) -> int:
        tlen = len(t)
        slen = len(s)
        if slen < tlen: return 0
        if slen == tlen:
            if s == t: return 1
            else: return 0
        if tlen == 0: return 1

        dp0 = [0] * (slen+1)
        dp = [1] * (slen+1)
        for i in range(1, tlen+1):
            dbg_print(dp)
            dp0, dp = dp, dp0
            dp[0] = 0
            for j in range(1, slen+1):
                dp[j] = dp[j-1]
                if s[j-1] == t[i-1]:
                    dp[j] += dp0[j-1]
        dbg_print(dp)
        return dp[slen]


# Now, simply uses one row
class Solution:
    def numDistinct(self, s: str, t: str) -> int:
        tlen = len(t)
        slen = len(s)
        if slen < tlen: return 0
        if slen == tlen:
            if s == t: return 1
            else: return 0
        if tlen == 0: return 1

        dp = [1] * (slen+1)
        for i in range(1, tlen+1):
            dbg_print(dp)
            dp0 = dp[0]
            dp[0] = 0
            for j in range(1, slen+1):
                _dp0 = dp[j]
                dp[j] = dp[j-1]
                if s[j-1] == t[i-1]:
                    dp[j] += dp0
                dp0 = _dp0
        dbg_print(dp)
        return dp[slen]

solbase = Solution1()
sol = Solution()

ucs = [
    ["baaab", "baab"],
    ["rabbbit", "rabbis"],
    ["rabbbit", "rabbit"],
    ["rbbbt", "rbbt"],
    ["rbbt", "rbt"],
    ["babgbag", "bag"],
    ["babgbagga"*100, "bag"],
    ["a"*1000, "a"*999],
    ["", "rabbit"],
    ["rabbbit", ""],
    ["", ""]
    ]
for [s, t] in ucs:
    expected = solbase.numDistinct(s, t)
    dbg_print("==============")
    res = sol.numDistinct(s, t)
    if (res == expected):
        print("sol.numDistinct(%s, %s) returned %d: Success" % (s, t, expected))
    else:
        print("sol.numDistinct(%s, %s) returned %d but expected %d: Fail!!!!!!" % (s, t, res, expected))
