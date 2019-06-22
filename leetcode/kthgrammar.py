#! /usr/bin/python3

class Solution:
    cache = {}
    def kthGrammar(self, N: int, K: int) -> int:
        if N in self.cache: return self.cache[N][K-1]
        self.cache[N] = self.NthRow(N)
        print("Row(%d) : %s" % (N, self.cache[N]))
        return self.cache[N][K-1]

    def NthRow(self, N:int) -> list:
        if N == 1: return [0]
        if N in self.cache: return self.cache[N]
        if N-1 in self.cache:
            prev = self.cache[N-1]
        else:
            prev = self.NthRow(N-1)
            self.cache[N-1] = prev
        idx = 0
        max_idx = 2 * len(prev)
        while idx < max_idx:
            if prev[idx] == 0:
                prev.insert(idx+1, 1)
            else:
                prev.insert(idx+1, 0)
            idx += 2
        return prev

    row_cached = '0'
    def kthGrammar(self, N: int, K: int) -> int:
        N -= 1
        K -= 1
        if K >= len(self.row_cached):
            self.update_row_cached(N, K)
        #print("Row(%d) : %s" % (N+1, self.row_cached))
        return int(self.row_cached[K])

    def update_row_cached(self, N:int, K: int) -> None:
        if len(self.row_cached) > K:
            return
        missing_01s = len(self.row_cached)
        idx = 0
        while missing_01s:
            to_add = '0'
            if self.row_cached[idx] == '0':
                to_add = '1'
            self.row_cached += to_add
            missing_01s -= 1
            idx += 1
        self.update_row_cached(N, K)

    def kthGrammar(self, N: int, K: int) -> int:
        if K < 3:
            return K - 1
        K -= 1
        pivot = 1
        while K >= (pivot * 2):
            pivot *= 2
        return int(1 - self.get_mirror(pivot, K))

    def get_mirror(self, pivot:int, K: int) -> int:
        if K <= 1:
            return 1 - K
        while pivot > K:
            pivot /= 2
        return 1 - self.get_mirror(pivot/2, K-pivot)

    translate = {
        0: [0, 1],
        1: [1, 0]
    }

    def kthGrammar_sol1(self, N: int, K: int) -> int:
        if N == 1 and K == 1:
            return 0

        index = (K+1) % 2
        source = (K+1) // 2

        res = self.kthGrammar_sol1(N-1, source)
        return res if index == 0 else res ^ 1

    def kthGrammar_sol2(self, N, K):
        if N == 1:
            if K == 1:
                return 0
            else:
                return 1

        half = 2**(N - 1)
        if K <= half:
            return self.kthGrammar_sol2(N - 1, K)
        else:
            res = self.kthGrammar_sol2(N - 1, K - half)
            if res == 0:
                return 1
            else:
                return 0

    def kthGrammar_sol3(self, N: 'int', K: 'int') -> 'int':
        # my solution ... 28 ms ... 100 % without bar ... 12.4 MB ... 87 %
        def find(N, K):
            if N == 1:
                return 0
            if K <= 2**(N-2):                           # row 3: "0110"
                return find(N-1, K)
            else:
                return 1 - find(N-1, K - 2**(N-2))      # row 4: "0110" + "1001"

        return find(N, K)

def check_solution():
    s = Solution()
    # N = 1
    # K = 1
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 0)
    #
    # N = 2
    # K = 1
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 0)
    #
    # N = 2
    # K = 2
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 1)
    #
    # N = 3
    # K = 3
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 1)
    #
    # N = 3
    # K = 4
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 0)
    #
    # N = 4
    # K = 5
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 1)
    #
    # N = 5
    # K = 5
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 1)
    #
    # N = 6
    # K = 5
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 1)
    #
    # N = 7
    # K = 5
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 1)
    #
    #
    # N = 8
    # K = 5
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 1)
    #
    #
    # N = 8
    # K = 10
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 0)
    #
    # N = 30
    # K = 434991989
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 0)
    #
    # N = 30
    # K = 434991990
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 1)
    #
    # N = 60
    # K = 84349919900
    # res = s.kthGrammar(N, K)
    # print("kthGrammar(%d, %d) = %d" % (N, K, res))
    # assert(res == 1)

    N = 30
    K = 434991990
    for idx in range(0, 800000):
        s.kthGrammar(N, K)

check_solution()
