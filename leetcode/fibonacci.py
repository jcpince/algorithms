class Solution:
    cache = {}
    def fib(self, N: int) -> int:
        if N == 0: return 0
        if N == 1: return 1
        if N in self.cache:
            return self.cache[N]
        result1 = self.fib(N-1)
        self.cache[N - 1] = result1
        result2 = self.fib(N-2)
        self.cache[N - 2] = result2
        return result1 + result2

def check_solution():
    s = Solution()
    print("fib(4) = %d" % s.fib(4))

check_solution()
