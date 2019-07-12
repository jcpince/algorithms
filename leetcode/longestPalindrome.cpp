/*
5. Longest Palindromic Substring
Medium

Given a string s, find the longest palindromic substring in s.
You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

Example 2:

Input: "cbbd"
Output: "bb"
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

#ifdef DEBUG
const bool continue_on_failure = false;
#endif

class Solution {
    bool isPalindrome(int dir, string &s, int start_idx, int end_idx)
    {
        bool result;
        int half_len = (end_idx + 1 - start_idx) / 2;
        debug_print("isPalindrome%d(%s, %d, %d) -> %s returns ", dir, s.c_str(),
            start_idx, end_idx, s.substr(start_idx, end_idx - start_idx + 1).c_str());
        for (int idx = 0 ; idx < half_len ; idx++)
            if (s[start_idx + idx] != s[end_idx - idx]) goto failed;

        debug_print("true\n");
        return true;
failed:
        debug_print("false\n");
        return false;
    }
    string findLongestPalindrome(string &s, int size) {
        if (size <= 1) return s.substr(0, 1);

        int start_idx0 = 0, end_idx0 = size - 1;
        int start_idx1 = s.length() - size, end_idx1 = s.length() - 1;
        debug_print("findLongestPalindrome(%s, %d)\n", s.c_str(),size);
        debug_print("idx0 is initially (%d, %d), idx1 is (%d, %d)\n", start_idx0, end_idx0, start_idx1, end_idx1);
        do
        {
            if (end_idx0 < s.length())
                if (isPalindrome(0, s, start_idx0, end_idx0)) return s.substr(start_idx0, end_idx0-start_idx0+1);

            if (start_idx0 >= start_idx1) break; /* looped over the string */

            if (start_idx1 >= 0)
                if (isPalindrome(1, s, start_idx1, end_idx1)) return s.substr(start_idx1, end_idx1-start_idx1+1);

            start_idx0++;end_idx0++;
            end_idx1--;start_idx1--;
            debug_print("idx0 is now (%d, %d), idx1 is (%d, %d)\n", start_idx0, end_idx0, start_idx1, end_idx1);
        } while ((end_idx0 < s.length()) || (start_idx1 >= 0) && (start_idx0 < start_idx1));

        return findLongestPalindrome(s, size - 1);
    }

    uint64_t longest_size = 0;
    string longest;

    void findLongestPalindromeFast(string &s, int middle_idx, int even) {

        debug_print("findLongestPalindromeFast(%s, %d, %d)\n", s.c_str(), middle_idx, even);

        int offset = 1 - even, s_length = s.length();

        while (((middle_idx - offset) > 0) && ((middle_idx + even + offset) < s_length) &&
                    s[middle_idx - offset] == s[middle_idx + even + offset])
            offset++;

        if (s[middle_idx - offset] != s[middle_idx + even + offset]) offset--;

        debug_print("findLongestPalindromeFast(%s, %d, %d) offset is %d\n", s.c_str(), middle_idx, even, offset);
        int current_longest_size = (offset * 2 + 1 + even);
        if (current_longest_size > longest_size)
        {
            longest_size = current_longest_size;
            debug_print("findLongestPalindromeFast(%s, %d, %d) update with (%d, %ld) => %s\n",
                s.c_str(), middle_idx, even, middle_idx - offset, longest_size,
                s.substr(middle_idx - offset, longest_size).c_str());
            longest = s.substr(middle_idx - offset, longest_size);
        }
    }

    uint64_t longest_start;
    string *ref;
    int s_length;
    const char *c_str;
    const char *start;
    const char *end;
    void findLongestPalindromeFast2(int middle_idx, int even) {


        const char *left = &c_str[middle_idx - 1 + even];
        const char *right = &c_str[middle_idx + 1];
        debug_print("findLongestPalindromeFast2(%s, %d, %d) starts with (%ld, %ld)\n", c_str,
            middle_idx, even, (uint64_t)(left - c_str), (uint64_t)(right - c_str));

        if (*left != *right) return;

        while ((left > start) && (right < end) && (*left == *right))
        {
            debug_print("left, right is (%c, %c), continue\n", *left, *right);
            *left--;
            *right++;
        }

        debug_print("left, right is (%ld, %ld)\n", (uint64_t)(left - c_str), (uint64_t)(right - c_str));

        if (*left != *right)
        {
            /* Rewind one byte if not matching */
            left++;
            right--;
            debug_print("Rewinded left and right, left is now %c and right is %c\n", *left, *right);
        }

        uint64_t current_longest_size = (uint64_t)right - (uint64_t)left + 1;
        debug_print("findLongestPalindromeFast2(%s, %d, %d) current_longest_size is %lu (%ld, %ld)\n",
            c_str, middle_idx, even, current_longest_size, (uint64_t)(left - c_str), (uint64_t)(right - c_str));
        if (current_longest_size > longest_size)
        {
            longest_size = current_longest_size;
            longest_start = (uint64_t)left - (uint64_t)start;
            debug_print("findLongestPalindromeFast2(%s, %d, %d) update with (%ld, %ld) => %s\n",
                c_str, middle_idx, even, longest_start, longest_size,
                ref->substr(longest_start, longest_size).c_str());
            dev_assert(isPalindrome(0, *ref, (int)longest_start, (int)(longest_start + longest_size - 1)));
        }
    }
public:
    string longestPalindrome(string &s) {
        if (s.length() <= 1) return s;
        return findLongestPalindrome(s, s.length());
    }
    string longestPalindromeFast(string &s) {
        if (s.length() <= 1) return s;
        longest_size = 1;
        longest = s.substr(0, longest_size);
        int max_size = s.length();

        for (int even = 0 ; even <= 1 ; even++)
            for (int idx = 1 - even ; idx < s.length() ; idx++)
            {
                if (longest_size == max_size) return longest;
                if (idx < (longest_size / 2)) continue;
                if (idx > (max_size - longest_size / 2)) break;
                findLongestPalindromeFast(s, idx, even);
            }
        return longest;
    }
    string longestPalindromeFast2(string &s) {
        s_length = s.length();
        if (s_length <= 1) return s;

        longest_start = 0;
        longest_size = 1;
        ref = &s;
        c_str = s.c_str();
        start = c_str;
        end = &c_str[s_length - 1];

        for (int even = 0 ; even <= 1 ; even++)
            for (int idx = 1 - even ; idx < s_length ; idx++)
            {
                if (longest_size == s_length) return s.substr(longest_start, longest_size);
                if (idx < (longest_size / 2)) continue;
                if (idx > (s_length - longest_size / 2)) break;
                findLongestPalindromeFast2(idx, even);
            }
        return s.substr(longest_start, longest_size);
    }
};

int check_solution(Solution &s, string &str, vector<string> &expected_vector)
{
    string result = s.longestPalindromeFast2(str);
    for (auto expected : expected_vector)
        if (result == expected) return 0;

    printf("longestPalindrome(%s) returned %s\n", str.c_str(), result.c_str());
    assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv)
{
    Solution s;
    int errors = 0, tests_count = 0;
    string str;
    vector<string> expected_vector;

    str = "nums"; expected_vector = {"n"}; errors += check_solution(s, str, expected_vector); tests_count++;
    str = "n"; expected_vector = {"n"}; errors += check_solution(s, str, expected_vector); tests_count++;
    str = "babad"; expected_vector = {"bab", "aba"}; errors += check_solution(s, str, expected_vector); tests_count++;
    str = "cbbd"; expected_vector = {"bb"}; errors += check_solution(s, str, expected_vector); tests_count++;
    str = "bb"; expected_vector = {"bb"}; errors += check_solution(s, str, expected_vector); tests_count++;
    str = "bababbabab"; expected_vector = {str}; errors += check_solution(s, str, expected_vector); tests_count++;
    str = "abcdefghijklmno"; expected_vector = {"a"}; errors += check_solution(s, str, expected_vector); tests_count++;
    str = "eeabcdcbaffeffef"; expected_vector = {"abcdcba"}; errors += check_solution(s, str, expected_vector); tests_count++;

    /* Perfs test */
    for (int i = 0 ; i < 400 ; i++)
    {
        str = "baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab";
        expected_vector = {str}; errors += check_solution(s, str, expected_vector); tests_count++;
        str = "baaaaaaaaaaaaaaaaaaaaccaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaccaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaccaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaccaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaccaaaaaab";
        expected_vector = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaccaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaccaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
        errors += check_solution(s, str, expected_vector); tests_count++;
    }

    if (errors == 0)
        cout << "All tests succeeded!!!" << endl;
    else
        cout << errors << " tests failed over a total of " << tests_count << endl;
    return 0;
}
