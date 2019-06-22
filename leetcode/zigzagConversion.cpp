/*
6. ZigZag Conversion
Medium

The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R

And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

#define DEBUG 1
#undef DEBUG
#ifdef DEBUG
#define debug_print printf
#define dev_assert assert
#else
#define debug_print(...)
#define dev_assert(...)
#endif

const bool continue_on_failure = true;

class Solution {
public:
    string convert(string s, int numRows) {
        int s_len = s.length();
        if ((numRows == 1) || (s_len <= 2)) return s;
        const char *c_str = s.c_str();

        int cycle_len = (numRows - 1) * 2;

        /* Allocate the result on the stack */
        char result[s_len+1], *r = result;
        result[s_len] = 0;

        /* insert the first row (each char every cycle bytes starting from offset 0) */
        int idx = 0;
        while (idx < s_len)
        {
            *r++ = c_str[idx];
            idx += cycle_len;
        }

        /* fills the intermediate rows */
        for (idx = 1 ; idx < (numRows - 1) ; idx++)
        {
            int first_offset = cycle_len - idx * 2;
            int second_offset = cycle_len - first_offset;
            int current_offset = idx;
            while (current_offset < s_len)
            {
                debug_print("copying char at index %d\n", current_offset);
                *r++ = c_str[current_offset];
                current_offset += first_offset;
                if (current_offset < s_len)
                    *r++ = c_str[current_offset];
                current_offset += second_offset;
            }
        }

        /* insert the last row (each char every cycle bytes starting from numRows - 1)*/
        idx = numRows - 1;
        while (idx < s_len)
        {
            *r++ = c_str[idx];
            idx += cycle_len;
        }

        return string(result);
    }
};

int check_solution(Solution &s, string str, int numRows, string expected)
{
    debug_print("Calling convert(%s, %d)\n", str.c_str(), numRows);
    string result = s.convert(str, numRows);
    bool succeeded = (expected == result);
    if (succeeded)
        return 0;

    printf("convert(%s, %d) return %s but expected %s\n", str.c_str(), numRows, result.c_str(), expected.c_str());
    assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv)
{
    Solution s;
    int errors = 0, tests_count = 0;

    errors += check_solution(s, "123456789abcdef", 1, "123456789abcdef"); tests_count++;
    errors += check_solution(s, "123456789abcdef", 2, "13579bdf2468ace"); tests_count++;
    errors += check_solution(s, "123456789abcdef", 3, "159d2468ace37bf"); tests_count++;
    errors += check_solution(s, "123456789abcdef", 4, "17d268ce359bf4a"); tests_count++;
    errors += check_solution(s, "123456789abcdef", 5, "1928a37bf46ce5d"); tests_count++;
    errors += check_solution(s, "", 1, ""); tests_count++;
    errors += check_solution(s, "a", 1, "a"); tests_count++;
    errors += check_solution(s, "a", 50, "a"); tests_count++;
    errors += check_solution(s, "a", 0, "a"); tests_count++;

    if (errors == 0)
        cout << "All tests succeeded!!!" << endl;
    else
        cout << errors << " tests failed over a total of " << tests_count << endl;
    return 0;
}
