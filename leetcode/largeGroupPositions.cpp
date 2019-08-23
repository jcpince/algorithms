class Solution {
public:
    vector<vector<int>> largeGroupPositions(string S) {
        const char *s = S.c_str();
        int len, start = 0;
        char c0 = *s++;
        vector<vector<int>> ans;
        while (*s) {
            len = 1;
            while (c0 == *s) {len++; s++;}
            if (len > 2) ans.push_back({start, start+len-1});
            if (*s) c0 = *s++;
            start += len;

        }
        return ans;
    }
};
