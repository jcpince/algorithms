#ifndef __TESTSHELPER__
#define __TESTSHELPER__

#include <vector>
#include <string>

using namespace std;

#ifdef DEBUG
#include <cstdio>
#include <cassert>

#define vectorat(v, idx) v.at(idx)
#define debug_print printf
#define dev_assert assert
#else
#define vectorat(v, idx) v[idx]
#define debug_print(...)
#define dev_assert(...)
#endif

#ifdef COUNT_ITERATIONS
uint64_t iterations_count = 0;
#define reset_iteration() do {iterations_count = 0;} while(0)
#define update_iterations() do {iterations_count++;} while(0)
#define get_iterations_count() iterations_count
#define print_iterations_count() printf("%ld iterations\n", iterations_count);
#else
#define reset_iteration()
#define update_iterations()
#define get_iterations_count()
#define print_iterations_count()
#endif

#define UNUSED(x) (void)(x)

template <class T>
bool check_result(const vector<T> &result, const vector<T> &expected)
{
    if (result.size() != expected.size()) return false;
    size_t idx = 0;
    for (T v : expected)
    {
        if (result.at(idx++) != v) return false;
    }
    return true;
}

template <class T>
bool check_result(const vector<vector<T>> &result, const vector<vector<T>> &expected)
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
                if (vectorat(e, idx) != vectorat(v, idx)) break;
            }
            if (idx == e.size()) { found = true; break; }
        }
        if (!found) return false;
    }
    return true;
}

string array2str(const vector<string> &arr)
{
    string s = "[";
    for (string i : arr)
        s += i + ", ";
    if (s.length() > 2) s.erase(s.length()-2,2);
    return s + "]";
}

template <class T>
string array2str(const vector<T> &arr)
{
    string s = "[";
    for (T i : arr)
        s += to_string(i) + ", ";
    if (s.length() > 2) s.erase(s.length()-2,2);
    return s + "]";
}

template <class T>
string array2str(const vector<vector<T>> &varr)
{
    string s = "[";
    for (vector<T> v : varr)
        s += array2str(v) + ", ";
    if (s.length() > 2) s.erase(s.length()-2,2);
    return s + "]";
}

/* binary search / dichotomy */
template <class T>
int find_element(vector<T> array, T value, int start, int end, int &below_idx, int &above_idx)
{
#ifdef DEBUG
    string sin = array2str(array);
    debug_print("find_element(%s, %d, %d, %d) ", sin.c_str(), value, start, end);
#endif

    if (value > vectorat(array, end)) {
        below_idx = end;
        above_idx = -1;
        return -1;
    }
    if (value < vectorat(array, start)) {
        below_idx = -1;
        above_idx = start;
        return -1;
    }

    int middle = start + (end - start + 1) / 2;
    while ((middle <= end) && (middle >= start))
    {
        update_iterations();
        T m = vectorat(array, middle);
        debug_print("v(%d), m(%d), sme(%d, %d, %d)\n", value, m, start, middle, end);
        if (m == value) {
            below_idx = middle, above_idx = middle;
            while (below_idx > start && (vectorat(array, --below_idx) > value)) update_iterations();
            while (above_idx < end && (vectorat(array, ++above_idx) < value)) update_iterations();
            if ((below_idx == start) and (vectorat(array, below_idx) >= value)) below_idx = -1;
            if ((above_idx == end) and (vectorat(array, above_idx) <= value)) above_idx = -1;
            debug_print(" ====> returns %d, %d, %d\n", middle, below_idx, above_idx);
            dev_assert(((below_idx != -1) and (vectorat(array, below_idx) < value)) or
                ((below_idx == -1) and (vectorat(array, start) >= value)));
            dev_assert(((above_idx != -1) and (vectorat(array, above_idx) > value)) or
                ((above_idx == -1) and (vectorat(array, end) <= value)));
            return middle;
        }
        if (value < m)
        {
            above_idx = middle;
            if (end == middle) end = middle-1;
            else end = middle;
        }
        else
        {
            below_idx = middle;
            if (start == middle) start = middle+1;
            else start = middle;
        }
        middle = start + (end - start + 1) / 2;
    }
    if ((below_idx == start) and (vectorat(array, below_idx) >= value)) below_idx = -1;
    if ((above_idx == end) and (vectorat(array, above_idx) <= value)) above_idx = -1;
    dev_assert(((below_idx != -1) and (vectorat(array, below_idx) < value)) or
        ((below_idx == -1) and (vectorat(array, start) >= value)));
    dev_assert(((above_idx != -1) and (vectorat(array, above_idx) > value)) or
        ((above_idx == -1) and (vectorat(array, end) <= value)));
    debug_print(" ===> returns -1, %d, %d\n", below_idx, above_idx);
    return -1;
}

template <class T>
int find_element_or_below(vector<T> array, T value, int start, int end, int &below_idx)
{
#ifdef DEBUG
    string sin = array2str(array);
    debug_print("find_element_or_below(%s, %d, %d, %d) ", sin.c_str(), value, start, end);
#endif

    if (value > vectorat(array, end)) {
        below_idx = end;
        return -1;
    }
    if (value < vectorat(array, start)) {
        below_idx = -1;
        return -1;
    }

    int middle = start + (end - start + 1) / 2;
    while ((middle <= end) && (middle >= start))
    {
        update_iterations();
        T m = vectorat(array, middle);
        debug_print("v(%d), m(%d), sme(%d, %d, %d)\n", value, m, start, middle, end);
        if (m == value) {
            debug_print(" ====> returns %d\n", middle);
            return middle;
        }
        if (value < m)
        {
            if (end == middle) end = middle-1;
            else end = middle;
        }
        else
        {
            below_idx = middle;
            if (start == middle) start = middle+1;
            else start = middle;
        }
        middle = start + (end - start + 1) / 2;
    }
    if ((below_idx == start) and (vectorat(array, below_idx) >= value)) below_idx = -1;
    dev_assert(((below_idx != -1) and (vectorat(array, below_idx) < value)) or
        ((below_idx == -1) and (vectorat(array, start) >= value)));
    debug_print(" ===> returns -1, %d\n", below_idx);
    return -1;
}

template <class T>
int findSorted(vector<T> array, T value, int start, int end)
{
    int middle;
    if(start == end) return (array[start] == value ? start : -1);

    while(start < end)
    {
        middle = (start + end) / 2;
        if(array[middle] == value) return middle;
        else if (array[middle] > value) end = middle - 1;
        else start = middle + 1;
    }
    return -1;
}

template <class T>
int findSorted2(vector<T> array, T value, int start, int end)
{
#ifdef DEBUG
    string sin = array2str(array);
    debug_print("find_element(%s, %d, %d, %d) ", sin.c_str(), value, start, end);
#endif

    if (value > vectorat(array, end)) {
        return -1;
    }
    if (value < vectorat(array, start)) {
        return -1;
    }

    int middle = start + (end - start + 1) / 2;
    while ((middle <= end) && (middle >= start))
    {
        update_iterations();
        T m = vectorat(array, middle);
        debug_print("v(%d), m(%d), sme(%d, %d, %d)\n", value, m, start, middle, end);
        if (m == value) {
            debug_print(" ====> returns %d, %d, %d\n", middle);
            return middle;
        }
        if (value < m)
        {
            if (end == middle) end = middle-1;
            else end = middle;
        }
        else
        {
            if (start == middle) start = middle+1;
            else start = middle;
        }
        middle = start + (end - start + 1) / 2;
    }
    debug_print(" ===> returns -1, %d, %d\n");
    return -1;
}

#endif /* __TESTSHELPER__ */
