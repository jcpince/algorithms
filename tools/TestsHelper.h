#ifndef __TESTSHELPER__
#define __TESTSHELPER__

#include <vector>
#include <string>

using namespace std;

#ifdef DEBUG
#include <cstdio>
#include <cassert>

#define vectorat(v, idx) v[idx]
#define debug_print printf
#define dev_assert assert

#else
#define vectorat(v, idx) v.at(idx)
#define debug_print(...)
#define dev_assert(...)
#endif

template <class T>
bool check_result(vector<T> &result, vector<T> &expected)
{
    if (result.size() != expected.size()) return false;
    for (T v : result)
    {
        size_t idx = 0;
        for ( ; idx < expected.size() ; idx++)
            if (expected.at(idx) != v) return false;
    }
    return true;
}

template <class T>
bool check_result(vector<vector<T>> &result, vector<vector<T>> &expected)
{
    if (result.size() != expected.size()) return false;
    for (vector<T> v : result)
    {
        bool found = false;
        for (vector<T> e : expected)
        {
            size_t idx = 0;
            for ( ; idx < e.size() ; idx++)
            {
                if (e.at(idx) != v.at(idx)) break;
            }
            if (idx == e.size()) { found = true; break; }
        }
        if (!found) return false;
    }
    return true;
}

template <class T>
string array2str(vector<T> &arr)
{
    string s = "[";
    for (T i : arr)
        s += to_string(i) + ", ";
    if (s.length() > 2) s.erase(s.length()-2,2);
    return s + "]";
}

template <class T>
string array2str(vector<vector<T>> &varr)
{
    string s = "[";
    for (vector<T> v : varr)
        s += array2str(v) + ", ";
    if (s.length() > 2) s.erase(s.length()-2,2);
    return s + "]";
}

/* binary search / dichotomy */
template <class T>
int find_third(vector<T> nums, T value, int start, int end)
{
#ifdef DEBUG
    string sin = array2str(nums);
    debug_print("find_third(%s, %d, %d, %d)...\n", sin.c_str(), value, start, end);
#endif
    T middle = start + (end - start + 1) / 2;
    while (middle < end)
    {
        debug_print("Value %d, sme(%d, %d, %d)\n", value, start, middle, end);
        if (nums[middle] > value)
            end = middle;
        else
            start = middle;
        if (nums[middle] == value)
            return middle;
        middle = start + (end - start + 1) / 2;
    }
    return -1;
}

#endif /* __TESTSHELPER__ */
