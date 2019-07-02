#ifndef __QUICKSORT__
#define __QUICKSORT__

/*
 * See https://www.geeksforgeeks.org/quick-sort/ for the qs_partition2 algo\
 */

#include <bits/stdc++.h>

using namespace std;

template <class T> void inline swapT(T &e1, T &e2) {
    T tmp = e2;
    e2 = e1;
    e1 = tmp;
}

template <class T>
size_t inline qs_partition2(vector<T> &arr, size_t start_idx, size_t end_idx) {

    T pivot_value = arr[end_idx];
    size_t last_smaller = start_idx - 1;
    for (size_t current_idx = start_idx ; current_idx < end_idx ; current_idx++ ) {
        if (arr[current_idx] <= pivot_value) {
            last_smaller++;
            if (current_idx != last_smaller)
                swapT(arr[current_idx], arr[last_smaller]);
        }
    }
    if (++last_smaller != end_idx)
        swapT(arr[end_idx], arr[last_smaller]);
    return last_smaller;
}

template <class T>
size_t inline qs_partition(T &arr, size_t start_idx, size_t end_idx) {
    size_t pivot_idx = end_idx;
    auto pivot_value = arr[pivot_idx];

    size_t current_idx = start_idx;
    while (current_idx < end_idx) {
        if (arr[current_idx] > pivot_value) {

            /* Don't swap with a value > pivot_value */
            while((current_idx < end_idx) and (arr[end_idx] > pivot_value)) end_idx--;
            if (current_idx == end_idx) break;

            swapT(arr[current_idx], arr[end_idx]);
        }
        current_idx++;
    }
    if ((current_idx != pivot_idx) and (arr[pivot_idx] < arr[current_idx]))
        swapT(arr[pivot_idx], arr[current_idx]);
    return current_idx;
}

template <class T>
void qs_quickSort(T &arr, size_t start_idx, size_t end_idx) {

    size_t pivot_index = qs_partition(arr, start_idx, end_idx);
    if (pivot_index > 1) qs_quickSort(arr, 0, pivot_index-1);
    if (pivot_index < end_idx) qs_quickSort(arr, pivot_index+1, end_idx);
}

template <class T>
void inline quickSort(T &arr, size_t arr_size) {
    if (arr_size < 2) return;

    qs_quickSort(arr, 0, arr_size-1);
}

template <class T>
void inline quickSort(T &arr) {
    if (arr.size() < 2) return;

    qs_quickSort(arr, 0, arr.size()-1);
}

#endif /* __QUICKSORT__ */
