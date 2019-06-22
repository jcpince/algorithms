/*
29. Divide Two Integers
Medium

Given two integers dividend and divisor, divide two integers without using multiplication,
division and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero.

Example 1:

Input: dividend = 10, divisor = 3
Output: 3

Example 2:

Input: dividend = 7, divisor = -3
Output: -2

Note:

    Both dividend and divisor will be 32-bit signed integers.
    The divisor will never be 0.
    Assume we are dealing with an environment which could only store integers within the 32-bit
    signed integer range: [−2^31,  2^31 − 1]. For the purpose of this problem, assume that your
    function returns 2^31 − 1 when the division result overflows.
*/

#include <iostream>
#include <cassert>
#include <cstring>
#include <utility>
#include <climits>
#include <vector>

using namespace std;

class Solution {
public:
    int divide(int _dividend, int _divisor) {
        bool is_negative = (_dividend < 0) ^ (_divisor < 0);
        unsigned long long dividend =  _dividend < 0 ? -(long long)_dividend : _dividend;
        unsigned long long divisor =  _divisor < 0 ? -(long long)_divisor : _divisor;
        //printf("%s(%d(%llu), %d(%llu))\n", __func__, _dividend, dividend, _divisor, divisor);

        if (dividend < divisor) return 0;
        if (divisor == 1)
        {
            //printf("returns signed %llu\n", dividend);
            if (!is_negative && (_dividend <= INT_MIN)) return -1;
            //printf("returns +- %llu\n", dividend);
            return is_negative ? -dividend : dividend;
        }
        if (dividend == divisor) return is_negative ? -1 : 1;

        long long quotient = 0;
        unsigned long long pow2_res = divisor, order = 1, result = 0;
        /* Find the max power of two < dividend */
        while ((pow2_res + pow2_res) <= dividend)
        {
            pow2_res <<= 1;
            order <<= 1;
        }
        //printf("\tpow2_res is %lld, order is %lld\n", pow2_res, order);

        do
        {
            if ((result + pow2_res) <= dividend)
            {
                result += pow2_res;
                quotient += order;
            }
            pow2_res >>= 1;
            order >>= 1;
        } while (pow2_res >= divisor);

        int r = _dividend / _divisor;
        quotient = is_negative ? -quotient : quotient;
        //printf("\tquotient is %lld, r is %d, INT_MIN is %d, INT_MAX is %d\n", quotient, r, INT_MIN, INT_MAX);
        if ((quotient < (long long)INT_MIN) || (quotient > (long long)INT_MAX)) return -1;
        //assert(r == quotient);
        //printf("returns %d\n", (int)quotient);
        return (int)quotient;
    }
};

int main(int argc, char **argv)
{
    Solution s;

    assert(s.divide(10, 9) == 1);
    assert(s.divide(10, 5) == 2);
    assert(s.divide(10, 3) == 3);
    assert(s.divide(14, 3) == 4);
    assert(s.divide(15, 3) == 5);
    assert(s.divide(16, 3) == 5);
    assert(s.divide(7, -3) == -2);
    assert(s.divide((2<<29), -1) == -(2<<29));
    assert(s.divide(-2147483648, -1) == -1);
    assert(s.divide(-2147483648, 1) == -2147483648);

    cout << "All tests succeeded" << endl;
    return 0;
}
