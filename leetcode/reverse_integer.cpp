/*
7. Reverse Integer
Easy

Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321

Example 2:

Input: -123
Output: -321

Example 3:

Input: 120
Output: 21

Note:
Assume we are dealing with an environment which could only store integers within the 32-bit
signed integer range: [−2^31,  2^31 − 1]. For the purpose of this problem, assume that your
function returns 0 when the reversed integer overflows.
*/

#include <iostream>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    int reverse(int _x) {
        if ((_x < INT_MIN) || (_x > INT_MAX)) return 0;

        int negative = (_x > 0) ? 1 : 0;
        long long int result = 0;
        long long int x = negative ? -_x : _x;
        //cout << "_x is " << _x << ", x is " << x << endl;

        while (x)
        {
            unsigned long d = x % 10;
            result = result * 10 + d;
            x /= 10;
        }

        //cout << "Result reverse(" << _x << ") is " << result << endl;
        if ((result < INT_MIN) || (result > INT_MAX)) return 0;
        return negative ? -result : result;
    }
};

int main(int argc, char **argv)
{
    Solution s;

    assert(s.reverse(0) == 0);
    assert(s.reverse(-2147483648) == 0);
    assert(s.reverse(21) == 12);
    assert(s.reverse(-2147483645) == 0);
    assert(s.reverse(-2147483641) == -1463847412);
    assert(s.reverse(1534236469) == 0);

    cout << "All tests succeeded" << endl;
    return 0;
}
