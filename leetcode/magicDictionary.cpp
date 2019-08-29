/* https://leetcode.com/problems/implement-magic-dictionary/
676. Implement Magic Dictionary
Medium

Implement a magic directory with buildDict, and search methods.

For the method buildDict, you'll be given a list of non-repetitive words to build a dictionary.

For the method search, you'll be given a word, and judge whether if you modify exactly one character into another character in this word, the modified word is in the dictionary you just built.

Example 1:

Input: buildDict(["hello", "leetcode"]), Output: Null
Input: search("hello"), Output: False
Input: search("hhllo"), Output: True
Input: search("hell"), Output: False
Input: search("leetcoded"), Output: False

Note:

    You may assume that all the inputs are consist of lowercase letters a-z.
    For contest purpose, the test data is rather small by now. You could think about highly efficient algorithm after the contest.
    Please remember to RESET your class variables declared in class MagicDictionary, as static/class variables are persisted across multiple test cases. Please see here for more details.
*/

class MagicDictionary {
    // The following map is keyed by the number of letters in the words of the vector
    // The vector contains a pair with the sum of all letters and the word
    // So that a quick first compare can be checking that the sums will be matching +- (z-a)
    // And then, the second match will consit in check the 1 letter change
    map<int, vector<pair<int, string>> *> mdict;

    int inline compute_word_sum(const string &word) {
        const char *s = word.c_str();
        int sum = 0;
        while (*s) sum += *s++;
        return sum;
    }

    bool check_vector(const string &word, const vector<pair<int, string>> *words) {
        int word_sum = compute_word_sum(word);
        for (pair p : *words) {
            int wsum = p.first;
            if (abs(wsum - word_sum) <= 26) {
                // It has the same number of caracters and the total sums diff is ok, let's check thoroughly
                const char *s1 = word.c_str(), *s2 = p.second.c_str();
                int diff = 0;
                while (diff < 2 && *s1) {
                    if (*s1++ != *s2++) diff++;
                }
                if (diff == 1) return true;
            }
        }
        return false;
    }

public:
    /** Initialize your data structure here. */
    MagicDictionary() {

    }
    ~MagicDictionary() {

    }

    /** Build a dictionary through a list of words */
    void buildDict(vector<string> dict) {
        for (string word : dict) {
            int sum = compute_word_sum(word);
            map<int, vector<pair<int, string>> *>::iterator it = mdict.find(word.length());
            if (it == mdict.end()) {
                // new vector
                vector<pair<int, string>> *v = new vector<pair<int, string>>();
                v->push_back(make_pair(sum, word));
                mdict[word.length()] = v;
            } else {
                // append to the existing vector
                mdict[word.length()]->push_back(make_pair(sum, word));
            }
        }
    }

    /** Returns if there is any word in the trie that equals to the given word after modifying exactly one character */
    bool search(const string &word) {
        if (word.length() == 0) return false;

        map<int, vector<pair<int, string>> *>::iterator it = mdict.find(word.length());
        if (it == mdict.end()) return false;
        vector<pair<int, string>> *words = it->second;
        return check_vector(word, words);
    }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dict);
 * bool param_2 = obj->search(word);
 */
