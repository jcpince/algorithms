/*
30. Substring with Concatenation of All Words
Hard

You are given a string, s, and a list of words, words, that are all of the same length. Find all starting indices of substring(s) in s that is a concatenation of each word in words exactly once and without any intervening characters.



Example 1:

Input:
  s = "barfoothefoobarman",
  words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.

Example 2:

Input:
  s = "wordgoodgoodgoodbestword",
  words = ["word","good","best","word"]
Output: []

*/

#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

#include "ListNode.h"

using namespace std;

const bool continue_on_failure = true;
#if 0
class Solution {
        int find_next(const char *s, const char *needle, const int offset0) {
                const char *ptr1, *ptr2;
                int offset = offset0;

                while (s[offset]) {
                        /* Search the first letter or the needle */
                        if (s[offset] != *needle)
                                offset++;
                        else {
                                /* found the first letter, check the rest */
                                ptr1 = &s[offset+1];
                                ptr2 = needle+1;
                                // printf("check %s and %s, offset is %d\n", ptr1, ptr2, offset);
                                while (*ptr1 && *ptr2 && *ptr1 == *ptr2) {
                                        ptr1++;
                                        ptr2++;
                                }
                                // printf("got %s and %s, return %d\n",
                                //         ptr1, ptr2, *ptr1 != *ptr2 ? -1 : offset);
                                if (!*ptr2) return offset;
                                offset++;
                        }
                }
                return -1;
        }
public:
        vector<int> findSubstring(string str, vector<string>& words) {
                const char *s = str.c_str();
                const int slen = str.length();
                const unsigned int nb_words = words.size();
                vector<int> result = {};

                if (!slen || !nb_words) return {};

                const int wlen = words[0].length();
                const int total_wlen = wlen * nb_words;
                if (total_wlen > slen) return {};

                sort(words.begin(), words.end());

                for ( unsigned int idx = 0 ; idx < nb_words ; idx++ ) {
                        const char *w = words[idx].c_str();
                        int p0 = 0, p = 0;

                        if (idx && words[idx-1] == words[idx])
                                continue;
                        while (p >= 0) {
                                p = find_next(s, w, p0);
                                if (p < 0 || p + total_wlen > slen)
                                        break;
                                // printf("find_next(%s, %s) returned %d\n", s, w,
                                //         p);
                                vector<string> v;
                                for (unsigned int jdx = 0 ; jdx < nb_words ; jdx++)
                                        v.push_back(str.substr(p + jdx * wlen, wlen));
                                sort(v.begin(), v.end());
                                if (v == words)
                                        result.push_back(p);
                                p0 = p+1;
                        }
                }

                return result;
        }
};
#endif

class Solution {
public:
        vector<int> findSubstring(string str, vector<string>& words) {
                const unsigned int slen = str.length();
                const unsigned int nb_words = words.size();
                vector<int> result = {};

                if (!slen || !nb_words) return {};

                const unsigned int wlen = words[0].length();
                const unsigned int total_wlen = wlen * nb_words;
                if (total_wlen > slen) return {};

                sort(words.begin(), words.end());

                for (unsigned int idx = 0 ; idx < wlen && idx + total_wlen <= slen ; idx++) {
                        vector<string> v;
                        unsigned int jdx = idx;
                        while (jdx <= (slen - wlen)) {
                                v.push_back(str.substr(jdx, wlen));
                                jdx += wlen;
                        }
                        //printf("Got %s\n", array2str(v).c_str());
                        for (jdx = 0 ; jdx <= v.size() - nb_words ; jdx++) {
                                vector<string>::iterator it = v.begin() + jdx;
                                //printf("Extract %d words from %s\n", nb_words, (*it).c_str());
                                vector<string> extract(it, it + nb_words);
                                sort(extract.begin(), extract.end());
                                //printf("Extract %s\n", array2str(extract).c_str());
                                if (extract == words)
                                        result.push_back(idx + jdx * wlen);
                        }
                }
                return result;
        }
};

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);

    vector<string> words = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["words"];
    string s_ = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["s"];
    vector<int> expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    vector<int> result = s.findSubstring(s_, words);

    if (check_result(result, expected)) return 0;

    printf("s.findSubstring(%s, %s) returned %s but expected %s\n", s_.c_str(),
        array2str(words).c_str(), array2str(result).c_str(),
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
        cout << errors_count << " test(s) failed over a total of " << tests_ran << endl;

    return errors_count;
}
