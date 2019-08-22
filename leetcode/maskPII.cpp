class Solution {
    string mail2mask(string S, size_t atidx) {
        string ans;
        ans.append(1, tolower(S[0]));
        ans.append(5, '*');
        ans.append(1, tolower(S[atidx-1]));
        for ( ; atidx < S.size() ; atidx++)
            ans.append(1, tolower(S[atidx]));
        return ans;
    }
    string number2mask(string S) {
        string only_digits;
        for (size_t off = 0 ; off < S.length() ; off++)
            if (isdigit(S[off])) only_digits.append(1, S[off]);
        string ans;
        if (only_digits.length() > 10) {
            size_t intCode_size = only_digits.length()-10;
            ans = "+";
            ans.append(intCode_size, '*');
            ans.append(1, '-');
        }
        ans += "***-***-";
        ans.append(1, only_digits[only_digits.length()-4]);
        ans.append(1, only_digits[only_digits.length()-3]);
        ans.append(1, only_digits[only_digits.length()-2]);
        ans.append(1, only_digits[only_digits.length()-1]);
        return ans;
    }
public:
    string maskPII(string S) {
        size_t atidx = S.find('@');
        if (atidx != string::npos)
            return mail2mask(S, atidx);
        return number2mask(S);
    }
};
