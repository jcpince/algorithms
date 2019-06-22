class Solution:
    cache = {}
    cache_root = None
    nb_rec = 0

    def pow(self, x: float, n: int) -> float:
        return x**n

    def _myPow1(self, x: float, n: int) -> float:
        self.nb_rec += 1
        if n == 0: return 1
        if n not in self.cache:
            self.cache[n] = x * self._myPow1(x, n-1)
        return self.cache[n]

    def _myPow2(self, x: float, n: int) -> float:
        #self.nb_rec += 1
        if n == 0: return 1
        if n == 1: return x
        if n % 2:
            if (n-1) not in self.cache:
                self.cache[n-1] = self._myPow2(x, n-1)
            #print("_myPow2(%f, %d) = %f" % (x, n-1, self.cache[n-1]))
            return x * self.cache[n-1]
        n //= 2
        if n not in self.cache:
            self.cache[n] = self._myPow2(x, n)
        #print("_myPow2(%f, %d) = %f" % (x, n, self.cache[n]))
        return self.cache[n] * self.cache[n]

    def myPow(self, x: float, n: int) -> float:
        if n == 0: return 1
        if self.cache_root != x:
            self.cache_root = x
            self.cache = {}
        if n < 0: return 1.0 / self._myPow2(x, -n)
        return self._myPow2(x, n)

def check_solution():
    s = Solution()
    root = 2
    power = 2
    result = s.myPow(root, power)
    print("myPow(%f, %d) = %f" % (root, power, result))
    assert(result == s.pow(root, power))
    power = 3
    result = s.myPow(root, power)
    print("myPow(%f, %d) = %f" % (root, power, result))
    assert(result == s.pow(root, power))
    power = 10
    result = s.myPow(root, power)
    print("myPow(%f, %d) = %f" % (root, power, result))
    assert(result == s.pow(root, power))
    power = 50
    result = s.myPow(root, power)
    print("myPow(%f, %d) = %f" % (root, power, result))
    assert(result == s.pow(root, power))
    power = -2
    result = s.myPow(root, power)
    print("myPow(%f, %d) = %f" % (root, power, result))
    power = -4
    result = s.myPow(root, power)
    print("myPow(%f, %d) = %f" % (root, power, result))
    assert(result == s.pow(root, power))
    # power = 123456
    # result = s.myPow(root, power)
    # print("myPow(%f, %d) = %ld" % (root, power, result))
    # assert(result == s.pow(root, power))
    root = 2.1
    power = 3
    result = s.myPow(root, power)
    print("myPow(%f, %d) = %f" % (root, power, result))
    assert(result == s.pow(root, power))
    print("nb_rec = %d" % s.nb_rec)

check_solution()
