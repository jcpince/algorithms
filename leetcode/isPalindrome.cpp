/*
9. Palindrome Number
Easy

Determine whether an integer is a palindrome. An integer is a palindrome when it reads the same backward as forward.

Example 1:

Input: 121
Output: true

Example 2:

Input: -121
Output: false
Explanation: From left to right, it reads -121. From right to left, it becomes 121-. Therefore it is not a palindrome.

Example 3:

Input: 10
Output: false
Explanation: Reads 01 from right to left. Therefore it is not a palindrome.

Follow up:

Coud you solve it without converting the integer to a string?
*/

#include <iostream>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if ((x < 0) || (x > INT_MAX)) return false;

        int result = 0, orig = x;
        //cout << "x is " << x << endl;

        while (x)
        {
            unsigned long d = x % 10;
            if (__builtin_mul_overflow(result, 10, &result)) return false;
            result += d;
            x /= 10;
        }

        //cout << "Result reverse(" << orig << ") is " << result << endl;
        return result == orig;
    }
};

int main(int argc, char **argv)
{
    Solution s;

    assert(s.isPalindrome(0) == true);
    assert(s.isPalindrome(-0) == true);
    assert(s.isPalindrome(-2147483648) == false);
    assert(s.isPalindrome(21) == false);
    assert(s.isPalindrome(212) == true);
    assert(s.isPalindrome(1234554321) == true);
    assert(s.isPalindrome(2147483647) == false);

    cout << "All tests succeeded" << endl;
    return 0;
}
