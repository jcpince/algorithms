class Solution:
    cache = {}
    def climbStairs(self, N: int) -> int:
        if N == 0: return 0
        if N == 1: return 1
        if N == 2: return 2
        if N in self.cache: return self.cache[N]
        result1 = self.climbStairs(N-1)
        self.cache[N - 1] = result1
        result2 = self.climbStairs(N-2)
        self.cache[N - 2] = result2
        return result1 + result2

def check_solution():
    s = Solution()
    print("climbStairs(2) = %d" % s.climbStairs(2))
    print("climbStairs(3) = %d" % s.climbStairs(3))
    print("climbStairs(4) = %d" % s.climbStairs(4))
    print("climbStairs(5) = %d" % s.climbStairs(5))
    print("climbStairs(6) = %d" % s.climbStairs(6))
    print("climbStairs(7) = %d" % s.climbStairs(7))

check_solution()

# 2: 2
# 2
# 1 + 1
#
# 3: 3
# 1 + 1 + 1
# 2 + 1
# 1 + 2
#
# 4: 5
# 1 + 1 + 1 + 1
# 1 + 1 + 2
# 1 + 2 + 1
# 2 + 1 + 1
# 2 + 2
#
# 5: 8
# 1 + 1 + 1 + 1 + 1
# 1 + 1 + 1 + 2
# 1 + 1 + 2 + 1
# 1 + 2 + 1 + 1
# 2 + 1 + 1 + 1
# 1 + 2 + 2
# 2 + 1 + 2
# 2 + 2 + 1
