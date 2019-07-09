/*
https://leetcode.com/problems/word-pattern

290. Word Pattern
Easy

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a
non-empty word in str.

Example 1:

Input: pattern = "abba", str = "dog cat cat dog"
Output: true

Example 2:

Input:pattern = "abba", str = "dog cat cat fish"
Output: false

Example 3:

Input: pattern = "aaaa", str = "dog cat cat dog"
Output: false

Example 4:

Input: pattern = "abba", str = "dog dog dog dog"
Output: false

Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters that may
be separated by a single space.

*/

class Solution {
public:
    bool wordPattern(string pattern, string str) {
        map<char, string> char2word;
        map<string, char> word2char;
        char *s = (char *)str.c_str(), *word;
        const char *p = pattern.c_str();

        word = strtok (s, " ");
        while(word and *p) {
            string w(word);
            map<char, string>::iterator it = char2word.find(*p);
            if (it == char2word.end()) {
                // Didn't find it, make sure the word is not know either
                if (word2char.find(w) != word2char.end()) return false;
                char2word[*p] = w;
                word2char[w] = *p;
            } else {
                // Found the letter, make sure the word is the same
                if (it->second != w) return false;
                map<string, char>::iterator it2 = word2char.find(w);
                if (it2 == word2char.end()) return false;
                if (it2->second != *p) return false;
            }
            p++;
            word = strtok (NULL, " ");
        }
        return (word == NULL and *p == 0);
    }
};
