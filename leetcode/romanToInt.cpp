/*
13. Roman to Integer
Easy

Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

For example, two is written as II in Roman numeral, just two one's added together.
Twelve is written as, XII, which is simply X + II.
The number twenty seven is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right.
However, the numeral for four is not IIII. Instead, the number four is written as IV.
Because the one is before the five we subtract it making four. The same principle applies to the
number nine, which is written as IX. There are six instances where subtraction is used:

    I can be placed before V (5) and X (10) to make 4 and 9.
    X can be placed before L (50) and C (100) to make 40 and 90.
    C can be placed before D (500) and M (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

Example 1:

Input: "III"
Output: 3

Example 2:

Input: "IV"
Output: 4

Example 3:

Input: "IX"
Output: 9

Example 4:

Input: "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.

Example 5:

Input: "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.

*/

#include <iostream>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
    static inline int toNumeral(const char c)
    {
        switch (c)
        {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
        }
        return 0;
    }
public:
    int romanToInt(string s) {
        const char *c = s.c_str();
        int roman = 0, tmp = 0;

        while (*c)
        {
            int current = toNumeral(*c);
            switch (current)
            {
                case 1:
                {
                    roman += tmp;
                    tmp = current;
                    break;
                }
                case 5:
                {
                    if (tmp == 1)
                    {
                        roman += 4;
                        tmp = 0;
                    } else
                    {
                        roman += tmp;
                        tmp = current;
                    }
                    break;
                }
                case 10:
                {
                    if (tmp == 1)
                    {
                        roman += 9;
                        tmp = 0;
                    } else
                    {
                        roman += tmp;
                        tmp = current;
                    }
                    break;
                }
                case 50:
                {
                    if (tmp == 10)
                    {
                        roman += 40;
                        tmp = 0;
                    } else
                    {
                        roman += tmp;
                        tmp = current;
                    }
                    break;
                }
                case 100:
                {
                    if (tmp == 10)
                    {
                        roman += 90;
                        tmp = 0;
                    } else
                    {
                        roman += tmp;
                        tmp = current;
                    }
                    break;
                }
                case 500:
                {
                    if (tmp == 100)
                    {
                        roman += 400;
                        tmp = 0;
                    } else
                    {
                        roman += tmp;
                        tmp = current;
                    }
                    break;
                }
                case 1000:
                {
                    if (tmp == 100)
                    {
                        roman += 900;
                        tmp = 0;
                    } else
                    {
                        roman += tmp;
                        tmp = current;
                    }
                    break;
                }
                default:
                    return -1;
            }
            c++;
        }
        printf("roman %d + tmp %d\n", roman, tmp);
        return roman + tmp;
    }
};

int main(int argc, char **argv)
{
    Solution s;

    assert(s.romanToInt("III") == 3);
    assert(s.romanToInt("IV") == 4);
    assert(s.romanToInt("IX") == 9);
    assert(s.romanToInt("LVIII") == 58);
    assert(s.romanToInt("MCMXCIV") == 1994);
    assert(s.romanToInt("MDCCCLXXXIV") == 1884);

    cout << "All tests succeeded" << endl;
    return 0;
}
