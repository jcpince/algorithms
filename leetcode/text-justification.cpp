/*
    68. Text Justification
Hard

Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.

You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.

Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.

For the last line of text, it should be left justified and no extra space is inserted between words.

Note:

A word is defined as a character sequence consisting of non-space characters only.
Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
The input array words contains at least one word.
 

Example 1:

Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
Output:
[
   "This    is    an",
   "example  of text",
   "justification.  "
]
Example 2:

Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
Output:
[
  "What   must   be",
  "acknowledgment  ",
  "shall be        "
]
Explanation: Note that the last line is "shall be    " instead of "shall     be", because the last line must be left-justified instead of fully-justified.
Note that the second line is also left-justified becase it contains only one word.
Example 3:

Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a","computer.","Art","is","everything","else","we","do"], maxWidth = 20
Output:
[
  "Science  is  what we",
  "understand      well",
  "enough to explain to",
  "a  computer.  Art is",
  "everything  else  we",
  "do                  "
]
 

Constraints:

1 <= words.length <= 300
1 <= words[i].length <= 20
words[i] consists of only English letters and symbols.
1 <= maxWidth <= 100
words[i].length <= maxWidth

*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    string inline build_padded_string(vector<string>& words, int idx0, int last_idx, int total_len, int max_len) {
        int nb_words = last_idx - idx0;
        int total_spaces = max_len - total_len;
        if (nb_words == 1) return words[idx0].append(total_spaces,' ');
        //printf("total_spaces is %d\n", total_spaces);
        
        string result;
        for (; idx0 < last_idx - 1 ; idx0++, nb_words--) {
            int current_spaces = total_spaces / (nb_words - 1);
            if (total_spaces > current_spaces * (nb_words - 1))
                current_spaces++;
            result += words[idx0].append(current_spaces, ' ');
            total_spaces -= current_spaces;
        }
        result += words[idx0];
        // printf("total_spaces is %d, result: '%s'\n", total_spaces, result.c_str());
        // assert((int)result.length() == max_len);
        return result;
    }
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        
        int idx0 = 0, accumulated_len = 0, nb_words = 1;
        for (int idx = 0 ; idx < (int)words.size() ; idx++) {
            int len = words[idx].length();
            if (len > maxWidth) return {};
            int total_len = len + accumulated_len + nb_words - 1;
            // printf("total_len %d, nb_words %d\n", total_len, nb_words);
            if (total_len < maxWidth) {
                accumulated_len += len;
                nb_words++;
            }
            else if (total_len == maxWidth) {
                result.push_back(
                    build_padded_string(words, idx0, idx+1, accumulated_len + len, maxWidth));
                idx0 = idx+1;
                accumulated_len = 0;
                nb_words = 1;
            } else {
                result.push_back(
                    build_padded_string(words, idx0, idx, accumulated_len, maxWidth));
                idx0 = idx;
                accumulated_len = len;
                nb_words = 2;
            }
        }
        if (accumulated_len) {
            string last = "";
            for (; idx0 < (int)words.size() - 1 ; idx0++) {
                last += words[idx0] + " ";
            }
            int spaces = maxWidth - last.length() - words[idx0].length();
            // printf("Add the last %d spaces for %s + %s to reach %d len\n",
            //     spaces, last.c_str(), words[idx0].c_str(), maxWidth);
            if (spaces) last += words[idx0].append(spaces, ' ');
            else last += words[idx0];
            result.push_back(last);
        }
        
        return result;
    }
};

int run_test_case(void *__s, TestCase *tc) {
        UNUSED(__s);
        vector<string> words = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["words"];
        int maxWidth = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["maxWidth"];
        vector<string> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution _s;
        vector<string> result = _s.fullJustify(words, maxWidth);

        if (result == expected) return 0;

        printf("fullJustify(%s, %d) returned %s but expected %s\n",
            array2str(words).c_str(), maxWidth, array2str(result).c_str(),
            array2str(expected).c_str());
        assert(continue_on_failure);
        return 1;
}

int main(int argc, char **argv) {
        int tests_ran = 0;
        const char *tc_id = NULL;

        if (argc < 2 || argc > 3)
        {
                cerr << "Usage: " << argv[0] << " <json test file> [test case index or name]" << endl;
                cerr << "Where: [test case index or name] specifies which test to run (all by default)" <<
                endl;
                return -1;
        }

        UnitTests uts(NULL, &run_test_case, argv[1]);

        if (argc == 3) tc_id = argv[2];

        int errors_count = uts.run_test_cases(tc_id, tests_ran);
        if (errors_count == 0)
                cout << "All " << tests_ran << " test(s) succeeded!!!" << endl;
        else
                cout << errors_count << " test(s) failed over a total of "
                        << tests_ran << endl;

        return errors_count;
}