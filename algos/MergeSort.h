#ifndef __MERGESORT__
#define __MERGESORT__

/*
 * See https://www.geeksforgeeks.org/quick-sort/ for the qs_partition2 algo\
 */

#include <bits/stdc++.h>
//#include <TestsHelper.h>

using namespace std;

template <class T>
T ms_mergeSort(const T &arr, const size_t start_idx, const size_t end_idx) {

    //debug_print("%s(%s, %ld, %ld) ", __func__, array2str(arr).c_str(), start_idx, end_idx);
    T result(end_idx - start_idx + 1);
    if (end_idx == start_idx) {
        result[0] = arr[start_idx];
        //debug_print("returns %s\n", array2str(result).c_str());
        return result;
    }

    T arr_lo, arr_hi;
    size_t half_size = (end_idx - start_idx) / 2;
    arr_lo = ms_mergeSort(arr, start_idx, start_idx + half_size);
    arr_hi = ms_mergeSort(arr, start_idx + half_size + 1, end_idx);

    /* merge arr_lo and arr_hi */
    size_t idx_lo = 0, idx_hi = 0, result_idx = 0;
    for (; (idx_lo < arr_lo.size()) and (idx_hi < arr_hi.size()) ; ) {
        if (arr_lo[idx_lo] < arr_hi[idx_hi]) {
            result[result_idx++] = arr_lo[idx_lo];
            idx_lo++;
        } else {
            result[result_idx++] = arr_hi[idx_hi];
            idx_hi++;
        }
    }
    /* Copy the last elements if any */
    for (; idx_lo < arr_lo.size() ; idx_lo++) result[result_idx++] = arr_lo[idx_lo];
    for (; idx_hi < arr_hi.size() ; idx_hi++) result[result_idx++] = arr_hi[idx_hi];

    //debug_print("returns %s\n", array2str(result).c_str());
    return result;
}

template <class T>
T inline mergeSort(const T &arr) {
    if (arr.size() < 2) return arr;

    return ms_mergeSort(arr, 0, arr.size()-1);
}

#endif /* __MERGESORT__ */
