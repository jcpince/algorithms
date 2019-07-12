/*
8. String to Integer (atoi)
Medium

Implement atoi which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

Note:

    Only the space character ' ' is considered as whitespace character.
    Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.

Example 1:

Input: "42"
Output: 42

Example 2:

Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.

Example 3:

Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.

Example 4:

Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical
             digit or a +/- sign. Therefore no valid conversion could be performed.

Example 5:

Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <cassert>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

//#define DEBUG 1
#undef DEBUG
#ifdef DEBUG
#define debug_print printf
#define dev_assert assert
#else
#define debug_print(...)
#define dev_assert(...)
#endif

#ifdef DEBUG
const bool continue_on_failure = false;
#endif

class Solution {
public:
    int myAtoi(string str) {
        const char *c_str = str.c_str();
        /* skips the leading whitespaces */
        while (*c_str == ' ') c_str++;

        /* adjust the sign */
        int64_t sign = 1;
        if (*c_str == '-')
        {
            debug_print("%s is < 0\n", c_str);
            sign = -1;
            c_str++;
        }
        else if (*c_str == '+') c_str++;

        /* Return 0 if the first char is not within 0-9 */
        if (*c_str < '0' || *c_str > '9')
        {
            debug_print("%s is invalid\n", c_str);
            return 0;
        }
        debug_print("%s is correct\n", c_str);

        int mult = 1;
        int64_t result = 0;
        while ((*c_str >= '0') && (*c_str <= '9'))
        {
            int digit = *c_str - '0';
            result = result * 10 + sign * digit;
            debug_print("digit %d, result becomes %ld\n", digit, result);
            if (result >= INT_MAX) return INT_MAX;
            if (result <= INT_MIN) return INT_MIN;
            c_str++;
        }
        return (int)result;
    }
};

int check_solution(Solution &s, string str, int expected)
{
    debug_print("Calling myAtoi(%s)\n", str.c_str());
    int result = s.myAtoi(str);
    bool succeeded = (expected == result);
    if (succeeded)
        return 0;

    printf("myAtoi(%s) return %d but expected %d\n", str.c_str(), result, expected);
    assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv)
{
    Solution s;
    int errors = 0, tests_count = 0;

    errors += check_solution(s, "42", 42); tests_count++;
    errors += check_solution(s, "-42", -42); tests_count++;
    errors += check_solution(s, "4193 with words", 4193); tests_count++;
    errors += check_solution(s, "words and 987", 0); tests_count++;
    errors += check_solution(s, "-91283472332", -2147483648); tests_count++;
    errors += check_solution(s, "-+1", 0); tests_count++;

    if (errors == 0)
        cout << "All tests succeeded!!!" << endl;
    else
        cout << errors << " tests failed over a total of " << tests_count << endl;
    return 0;
}
