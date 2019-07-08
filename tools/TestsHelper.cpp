#include <TestsHelper.h>

string array2str(const vector<string> &arr) {
    string s = "[";
    for (string i : arr)
        s += i + ", ";
    if (s.length() > 2) s.erase(s.length()-2,2);
    return s + "]";
}
