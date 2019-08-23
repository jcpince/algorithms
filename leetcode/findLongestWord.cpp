class Solution {
    static inline bool wordin(string &w, string &characters) {
        const char *pw = w.c_str();
        const char *array = characters.c_str();
        while (*pw) {
            while (*array and (*array != *pw)) array++;
            if (*array != *pw) return false;
            pw++;
            array++;
        }
        return true;
    }
public:
    string findLongestWord(string s, vector<string>& d) {
        sort(d.begin(), d.end());
        string ans = "";
        for (string word : d)
        {
            if (word.length() <= ans.length()) continue;
            if (wordin(word, s)) ans = word;
        }
        return ans;
    }
};
