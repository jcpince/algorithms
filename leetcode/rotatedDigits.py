#! /usr/bin/python3

# 788. Rotated Digits
# Easy
#
# X is a good number if after rotating each digit individually by 180 degrees, we get a valid number that is different from X.  Each digit must be rotated - we cannot choose to leave it alone.
#
# A number is valid if each digit remains a digit after rotation. 0, 1, and 8 rotate to themselves; 2 and 5 rotate to each other; 6 and 9 rotate to each other, and the rest of the numbers do not rotate to any other number and become invalid.
#
# Now given a positive number N, how many numbers X from 1 to N are good?
#
# Example:
# Input: 10
# Output: 4
# Explanation:
# There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
# Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
#
# Note:
#
#     N  will be in range [1, 10000].
#

class Solution:
    up_to_10_same = 3
    up_to_10_rotate = 4
    up_to_100_same = 3*up_to_10_same # 3 symetric numbers for 0x, 1x and 8x
    up_to_100_rotate = 4*(up_to_10_same+up_to_10_rotate) + 3*up_to_10_rotate # 4 good numbers for 0x, 1x, 2x, 5x, 6x, 8x, 9x + 3 good for 2x, 5x, 6x, 9x
    up_to_1000_same = 3*up_to_100_same
    up_to_1000_rotate = 4*(up_to_100_same+up_to_100_rotate) + 3*up_to_100_rotate
    up_to_10000_same = 3*up_to_1000_same
    up_to_10000_rotate = 4*(up_to_1000_same+up_to_1000_rotate) + 3*up_to_1000_rotate
    cache = {   10:     [up_to_10_same,     up_to_10_rotate],
                100:    [up_to_100_same,    up_to_100_rotate],
                1000:   [up_to_1000_same,   up_to_1000_rotate]}

    def get_rotators(self, digit):
        if digit > 8:
            return 4
        elif digit > 5:
            return 3
        elif digit > 4:
            return 2
        elif digit > 1:
            return 1
        return 0

    def get_symetrics(self, digit):
        if digit > 7:
            return 3
        elif digit > 0:
            return 2
        else:
            return 1

    def is_rotator(self, digit):
        return digit in [2,5,6,9]

    def is_symetric(self, digit):
        return digit in [0,1,8]

    def is_invalid(self, digit):
        return digit in [3,4,7]

    def rotatedDigits(self, N: int) -> int:
        N0 = N
        result = 0
        global_rotate = False
        divisor = 1000
        digit = N // 1000
        if digit > 0:
            N -= 1000 * digit
            rot = self.get_rotators(digit - 1)
            sym = self.get_symetrics(digit - 1)
            result += rot * (self.up_to_1000_same+self.up_to_1000_rotate) + sym * self.up_to_1000_rotate
            if self.is_invalid(digit): return result
            if self.is_rotator(digit): global_rotate = True
        divisor = 100
        digit = N // 100
        #print("%d 100s" % digit)
        if digit > 0:
            N -= 100 * digit
            rot = self.get_rotators(digit - 1)
            sym = self.get_symetrics(digit - 1)
            if global_rotate:
                result += (rot+sym) * (self.up_to_100_same+self.up_to_100_rotate)
            else: result += rot * (self.up_to_100_same+self.up_to_100_rotate) + sym * self.up_to_100_rotate
            if self.is_invalid(digit): return result
            if self.is_rotator(digit): global_rotate = True
        print("N(%d) -> 100s result: %d -- global_rotate %s" % (N0, result, global_rotate))
        digit = N // 10
        #print("%d 10s" % digit)
        if digit > 0:
            N -= 10 * digit
            rot = self.get_rotators(digit - 1)
            sym = self.get_symetrics(digit - 1)
            #print("result += %d*%d + %d*%d" % (rot,self.up_to_10_same+self.up_to_10_rotate,sym,self.up_to_10_rotate))
            if global_rotate:
                result += (rot+sym) * (self.up_to_10_same+self.up_to_10_rotate)
            else: result += rot * (self.up_to_10_same+self.up_to_10_rotate) + sym * self.up_to_10_rotate
            if self.is_invalid(digit): return result
            if self.is_rotator(digit): global_rotate = True
        print("N(%d) -> 10s result: %d -- global_rotate %s" % (N0, result, global_rotate))
        if global_rotate:
            result += self.get_symetrics(N)
        result += self.get_rotators(N)
        print("N(%d) -> %d" % (N0, result))
        return result

    def rotatedDigits(self, N: int) -> int:
        N0 = N
        result = 0
        global_rotate = False
        divisor = 1000
        while N and divisor != 1:
            digit = N // divisor
            if digit > 0:
                N -= divisor * digit
                rot = self.get_rotators(digit - 1)
                sym = self.get_symetrics(digit - 1)
                if global_rotate:
                    # print("result += (%d + %d) * (%d + %d)" % (rot, sym, self.cache[divisor][0],
                    #     self.cache[divisor][1]))
                    result += (rot + sym) * (self.cache[divisor][0] + self.cache[divisor][1])
                else:
                    # print("result += %d * (%d + %d) + %d * %d" % (rot, self.cache[divisor][0],
                    #     self.cache[divisor][1], sym, sym * self.cache[divisor][0]))
                    result += rot * (self.cache[divisor][0] + self.cache[divisor][1]) + \
                            sym * self.cache[divisor][1]
                if self.is_invalid(digit): return result
                if self.is_rotator(digit): global_rotate = True
            divisor /= 10
        if global_rotate:
            result += self.get_symetrics(N)
        result += self.get_rotators(N)
        # print("N(%d) -> %d" % (N0, result))
        return result

def check_solution():
    s = Solution()

    assert(s.rotatedDigits(1) == 0)
    assert(s.rotatedDigits(2) == 1)
    assert(s.rotatedDigits(3) == 1)
    assert(s.rotatedDigits(4) == 1)
    assert(s.rotatedDigits(5) == 2)
    assert(s.rotatedDigits(6) == 3)
    assert(s.rotatedDigits(7) == 3)
    assert(s.rotatedDigits(8) == 3)
    assert(s.rotatedDigits(9) == 4)
    assert(s.rotatedDigits(10) == 4)
    assert(s.rotatedDigits(11) == 4)
    assert(s.rotatedDigits(19) == 8)
    assert(s.rotatedDigits(20) == 9)
    assert(s.rotatedDigits(25) == 12)
    assert(s.rotatedDigits(29) == 15)
    assert(s.rotatedDigits(100) == 40)
    assert(s.rotatedDigits(101) == 40)
    assert(s.rotatedDigits(199) == 80)
    assert(s.rotatedDigits(200) == 81)
    assert(s.rotatedDigits(201) == 82)
    assert(s.rotatedDigits(250) == 102)
    assert(s.rotatedDigits(299) == 129)
    assert(s.rotatedDigits(300) == 129)
    assert(s.rotatedDigits(320) == 129)
    assert(s.rotatedDigits(390) == 129)
    assert(s.rotatedDigits(399) == 129)
    assert(s.rotatedDigits(799) == 227)
    assert(s.rotatedDigits(800) == 227)
    assert(s.rotatedDigits(1799) == 543)
    assert(s.rotatedDigits(2999) == 975)
    assert(s.rotatedDigits(3999) == 975)
    assert(s.rotatedDigits(4999) == 975)

    print("All tests passed successfully!!")

check_solution()
