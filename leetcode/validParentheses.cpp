/*
20. Valid Parentheses
Easy

Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

    Open brackets must be closed by the same type of brackets.
    Open brackets must be closed in the correct order.

Note that an empty string is also considered valid.

Example 1:

Input: "()"
Output: true

Example 2:

Input: "()[]{}"
Output: true

Example 3:

Input: "(]"
Output: false

Example 4:

Input: "([)]"
Output: false

Example 5:

Input: "{[]}"
Output: true

*/

#include <iostream>
#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        if (s.size() == 0) return true;
        if (s.size() % 2) return false;
        const char *str = s.c_str();
        int depth = 0;
        char stack[s.size() / 2 + 1];
        //stack[0] = '.';
        //printf("Check %s\n", str);
        do
        {
            //printf("Check %c, depth is %d, stack[depth-1] is %c\n", *str, depth, stack[depth-1]);
            switch(*str)
            {
                case ')':
                    if (!depth || (stack[--depth] != '(')) return false;
                    break;
                case ']':
                    if (!depth || (stack[--depth] != '[')) return false;
                    break;
                case '}':
                    if (!depth || (stack[--depth] != '{')) return false;
                    break;
                default:
                    assert(depth < (s.size() / 2 + 1));
                    stack[depth++] = *str;
            }
        } while (*(++str));
        //printf("last depth is %d\n", depth);
        return depth == 0;
    }
};

int main(int argc, char **argv)
{
    Solution s;
    assert(s.isValid("()") == true);
    assert(s.isValid("()[]{}") == true);
    assert(s.isValid("(]") == false);
    assert(s.isValid("([)]") == false);
    assert(s.isValid("{[]}") == true);
    assert(s.isValid(")(") == false);
    assert(s.isValid("((") == false);

    cout << "All tests succeeded" << endl;
    return 0;
}
