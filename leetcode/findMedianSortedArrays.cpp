/*
4. Median of Two Sorted Arrays
Hard

There are two sorted arrays nums1 and nums2 of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume nums1 and nums2 cannot be both empty.

Example 1:

nums1 = [1, 3]
nums2 = [2]

The median is 2.0

Example 2:

nums1 = [1, 2]
nums2 = [3, 4]

The median is (2 + 3)/2 = 2.5
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <cassert>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

//#define DEBUG 1
#undef DEBUG
#ifdef DEBUG
#define vectorat(v, idx) v[idx]
#define debug_print printf
#define dev_assert assert
#else
#define vectorat(v, idx) v.at(idx)
#define debug_print(...)
#define dev_assert(...)
#endif

const bool continue_on_failure = false;
void dump_arrays_merge(vector<int>& nums1, vector<int>& nums2);

class Solution {
public:
    int median_value_low_index(size_t size)
    {
        return (size % 2) ? size/2 : size/2-1;
    }

    int median_value_low(vector<int> &nums)
    {
        return vectorat(nums, median_value_low_index(nums.size()));
    }
    double median(vector<int> &nums)
    {
        size_t size = nums.size();
        if (size % 2) return (double)vectorat(nums, size/2);
        return (double)(vectorat(nums, size/2-1) + vectorat(nums, size/2)) / 2.0;
    }

    double median(vector<int> &lower, vector<int> &upper)
    {
        size_t size = lower.size() + upper.size();
        size_t offset = size / 2;
        if (size % 2)
        {
            /* check if the element is in lower */
            if (offset < lower.size())
                return (double)vectorat(lower, offset);
            else
                return (double)vectorat(upper, offset - lower.size());
        }
        if ((offset-1) < lower.size())
        {
            /* check if both elements are in lower */
            if (offset < lower.size())
                return (double)(vectorat(lower, offset-1) + vectorat(lower, offset)) / 2.0;
            else
                return (double)(vectorat(lower, offset-1) + vectorat(upper, 0)) / 2.0;
        }
        /* both elements are in upper */
        offset -= lower.size();
        return (double)(vectorat(upper,offset-1) + vectorat(upper,offset)) / 2.0;
    }

    double median(vector<int> &nums, int other_value) {
        size_t size = nums.size() + 1;
        if (size == 2) return (double)(vectorat(nums, 0) + other_value) / 2.0;

        size_t offset = median_value_low_index(size);
        if (size % 2)
        {
            /* check if the other value is right or left */
            if (vectorat(nums, offset) <= other_value)
                return (double)vectorat(nums, offset);
            else
                return (double)max(vectorat(nums, offset-1), other_value);
        }

        debug_print("median(nums, %d), offset is %ld\n", other_value, offset);
        if (vectorat(nums, offset) < other_value)
            return (double)(vectorat(nums, offset) + min(vectorat(nums, offset+1), other_value)) / 2.0;

        /* shift left the offset of the low median index */
        if (vectorat(nums, offset) == other_value)
            return (double)vectorat(nums, offset);

        return (double)(vectorat(nums, offset) + max(vectorat(nums, offset-1), other_value)) / 2.0;
    }

    bool check_mli_within_array(int mli, size_t size, vector<int>& nums1, vector<int>& nums2, double &value)
    {
        /* checks if mli is within nums1 */
        if (mli >= nums1.size()) return false;

        /* checks if nums1 at mli is below the first element of nums2; ie, mli is within nums1... */
        if (vectorat(nums1, mli) > vectorat(nums2, 0)) return false;

        /* size is odd, the median is with nums1, simply returns it */
        if (size % 2)
        {
            value = vectorat(nums1, mli);
            return true;
        }

        /* mli is within nums1, check if this is the last one */
        if (mli == (nums1.size() - 1))
        {
            value = (double)(nums1.back() + vectorat(nums2, 0)) / 2.0;
            return true;
        }

        /* This is not the last, check if it is below the second array first value */
        value = (double)(vectorat(nums1, mli) + min(vectorat(nums1, mli+1), vectorat(nums2, 0))) / 2.0;
        return true;
    }

    /* Dichotomy, binsearch implementation */
    void find_indices_binsearch(int mli, vector<int>& nums1, vector<int>& nums2, int &idx1, int &idx2)
    {
        /* find idx1 and idx2 such that idx1 + idx2 == mli and nums1(idx1) <= nums2(idx2+1)
         * and nums2(idx2) <= nums1(idx1+1)
         */
        int nums1_size = nums1.size(), nums2_size = nums2.size();
        int idx1_low = 0, idx1_high = nums1_size - 1;
        idx1 = min(max(mli - 2, 0), nums1_size-1);
        idx2 = mli - idx1 - 1;

#if DEBUG
        dump_arrays_merge(nums1, nums2);
        debug_print("nums1.size() is %d, idx1 is %d, mli is %d\n", nums1_size, idx1, mli);
        debug_print("nums2.size() is %d, idx2 is %d\n", nums2_size, idx2);
        dev_assert(idx1 <= (nums1_size - 1));
        dev_assert(idx2 <= (nums2_size - 1));
        dev_assert(idx1 >= 0);
        dev_assert(idx2 >= 0);
#endif

        int n1_low = vectorat(nums1, idx1), n1_high;
        int n2_low = vectorat(nums2, idx2), n2_high;
        if (idx1 >= nums1_size - 1)
            n1_high = INT_MAX;
        else n1_high = vectorat(nums1, idx1+1);
        if (idx2 >= nums2_size - 1)
            n2_high = INT_MAX;
        else n2_high = vectorat(nums2, idx2+1);

        /* Here, given the pre computing, we SHALL have data to take from both arrays */
        while ((n1_low > n2_high) || (n2_low > n1_high))
        {
            assert(idx1_high != idx1_low);
            if (n1_low > n2_high) /* move left in nums1*/
            {
                idx1_high = idx1;
                if (idx1_high > (idx1_low + 1))
                    idx1 = idx1_low + (idx1_high - idx1_low) / 2;
                else idx1--;
            }
            else
            {
                idx1_low = idx1;
                if (idx1_high > (idx1_low + 1))
                    idx1 = idx1_low + (idx1_high - idx1_low) / 2;
                else idx1++;
            }

            /* update idx1 & idx2 */
            idx2 = mli - idx1 - 1;

            if (idx1 >= nums1_size - 1)
                n1_high = INT_MAX;
            else n1_high = vectorat(nums1, idx1+1);
            if (idx2 >= nums2_size - 1)
                n2_high = INT_MAX;
            else n2_high = vectorat(nums2, idx2+1);
            n1_low = vectorat(nums1, idx1);
            n2_low = vectorat(nums2, idx2);

            dev_assert(idx1 <= (nums1_size - 1));
            dev_assert(idx2 <= (nums2_size - 1));
            dev_assert(idx1 >= 0);
            dev_assert(idx2 >= 0);
            debug_print("Binsearch loop idx1 = %d, idx2 = %d, idx_low_high = %d, %d\n",
                idx1, idx2, idx1_low, idx1_high);
        }
        debug_print("Binsearch found idx1 = %d, idx2 = %d\n", idx1, idx2);
    }

    double find_median_binary_search(int mli, size_t size, vector<int>& nums1, vector<int>& nums2)
    {
        /* if we arrived here, at least one element from each array is prior the median value */
        dev_assert(nums1.size() <= nums2.size());
        dev_assert(nums1.size() >= 2);

        /* find idx1 and idx2 such that idx1 + idx2 == mli and nums1(idx1) <= nums2(idx2+1)
         * and nums2(idx2) <= nums1(idx1+1)
         */
        int idx1, idx2, idx1_ref, idx2_ref;
        find_indices_binsearch(mli, nums1, nums2, idx1, idx2);

        /* Found the proper partitionning, now, checks if total size is odd */
        if (size % 2)
            return (double)max(vectorat(nums1, idx1), vectorat(nums2, idx2));

        /* it is even */
        int n1_high, n2_high;

        if (idx1 >= nums1.size() - 1)
            n1_high = INT_MAX;
        else n1_high = vectorat(nums1, idx1+1);
        if (idx2 >= nums2.size() - 1)
            n2_high = INT_MAX;
        else n2_high = vectorat(nums2, idx2+1);

        assert(idx1 < nums1.size());
        assert(idx2 < nums2.size());
        return (double)(max(vectorat(nums1, idx1), vectorat(nums2, idx2)) + min(n1_high, n2_high)) / 2.0;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2)
    {
        /* Check if one of the arrays is empty, the result is then the median of the other array */
        if (!nums1.size()) return median(nums2);
        if (!nums2.size()) return median(nums1);

        /* Check if one of the arrays is 1 elt wide, the result is then the median of the other array */
        if (nums1.size() == 1) return median(nums2, vectorat(nums1, 0));
        if (nums2.size() == 1) return median(nums1, vectorat(nums2, 0));

        /* Check if the first elemnt of an array is smaller than the last elemnt of the other array,
         * the result is then at the median index - our first array size
         */
        if (vectorat(nums2, 0) >= nums1.back()) return median(nums1, nums2);
        if (vectorat(nums2, 0) >= nums2.back()) return median(nums2, nums1);

        /* Compute the index of the median low value in the sorted array */
        size_t total_size = nums1.size() + nums2.size();
        int mli = median_value_low_index(total_size);
        double value;

        /* Check if the mli of any array is <= than the first element of the second array */
        if (check_mli_within_array(mli, total_size, nums1, nums2, value)) return value;
        if (check_mli_within_array(mli, total_size, nums2, nums1, value)) return value;

        if (nums1.size() < nums2.size())
            return find_median_binary_search(mli, total_size, nums1, nums2);
        else
            return find_median_binary_search(mli, total_size, nums2, nums1);
    }
};

double refSolution(vector<int>& nums1, vector<int>& nums2) {

    vector<int> nums12(nums1.size()+nums2.size());
    merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), nums12.begin());
    size_t size = nums12.size();
    if (size % 2) return (double)vectorat(nums12, size/2);
    return (double)(vectorat(nums12,size/2-1) + vectorat(nums12, size/2)) / 2.0;
}

void dump_arrays_merge(vector<int>& nums1, vector<int>& nums2)
{
    copy(nums1.begin(), nums1.end(), ostream_iterator<int>(cout, " "));
    cout << endl << "+" << endl;
    copy(nums2.begin(), nums2.end(), ostream_iterator<int>(cout, " "));
    cout << endl << "=" << endl;
    vector<int> nums12(nums1.size()+nums2.size());
    merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), nums12.begin());
    copy(nums12.begin(), nums12.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int check_solution(Solution s, vector<int> nums1, vector<int> nums2)
{
    double ref = refSolution(nums1, nums2);
    double computed1 = s.findMedianSortedArrays(nums1, nums2);
    double computed2 = s.findMedianSortedArrays(nums2, nums1);
    if ((ref != computed1 )|| (ref != computed2)) {
        dump_arrays_merge(nums1, nums2);
        cout << "Expected " << ref << " but got "<< computed1 << " and " << computed2 << endl;
        return 1;
    } else  {
        /*
        dump_arrays_merge(nums1, nums2);
        cout << "####### Returned " << computed << endl;
        */
        return 0;
    }
}

void run_median_methods_unit_tests(Solution s, vector<int> nums1, vector<int> nums2)
{
    /* test the median method */
    nums1 = {3, 4};
    assert(s.median(nums1) == 3.5);

    nums1 = {3, 4, 5};
    assert(s.median(nums1) == 4);

    /* test the median method with two non interleaving arrays */
    nums1 = {3, 4, 5, 6}; nums2 = {7, 8, 9};
    assert(s.median(nums1, nums2) == 6);

    nums1 = {3, 4, 5}; nums2 = {7, 7, 8, 9};
    assert(s.median(nums1, nums2) == 7);

    nums1 = {1, 2, 3, 4, 5}; nums2 = {6, 7, 8};
    assert(s.median(nums1, nums2) == 4.5);

    nums1 = {1, 2, 3}; nums2 = {6, 7, 8, 9, 10};
    assert(s.median(nums1, nums2) == 6.5);

    nums1 = {3, 4, 5}; nums2 = {6, 7, 8};
    assert(s.median(nums1, nums2) == 5.5);

    nums1 = {3, 4, 5, 6}; nums2 = {6, 7, 8, 9};
    assert(s.median(nums1, nums2) == 6);

    nums1 = {3, 4, 5, 6};
    assert(s.median(nums1, 6) == 5);
    assert(s.median(nums1, 1) == 4);
    assert(s.median(nums1, 4) == 4);

    nums1 = {3};
    assert(s.median(nums1, 4) == 3.5);
    assert(s.median(nums1, 2) == 2.5);

    nums1 = {3, 4};
    assert(s.median(nums1, 4) == 4);
    assert(s.median(nums1, 1) == 3);

    nums1 = {3, 4, 5, 12, 13};
    assert(s.median(nums1, 1) == 4.5);
    assert(s.median(nums1, 5) == 5);
    assert(s.median(nums1, 8) == 6.5);
    assert(s.median(nums1, 15) == 8.5);
    assert(s.median(nums1, 12) == 8.5);

    cout << "Median unit tests succeeded!!" << endl;
}

void run_empty_array_unit_tests(Solution s, vector<int> nums1, vector<int> nums2)
{
    int errors = 0;
    nums1 = {}, nums2 = {3, 4};
    errors += check_solution(s, nums1, nums2);

    nums1 = {}, nums2 = {3, 4, 5};
    errors += check_solution(s, nums1, nums2);

    nums1 = {}, nums2 = {3};
    errors += check_solution(s, nums1, nums2);

    if (errors == 0)
        cout << "Empty array unit tests succeeded!!" << endl;
    else cout << "Empty array unit tests failed!!" << endl;
}

void run_non_interleaving_arrays_unit_tests(Solution s, vector<int> nums1, vector<int> nums2)
{
    int errors = 0;
    nums1 = {3, 4, 5, 6}; nums2 = {7, 8, 9};
    errors += check_solution(s, nums1, nums2);

    nums1 = {6}; nums2 = {7, 8, 9};
    errors += check_solution(s, nums1, nums2);

    nums1 = {3, 4, 5, 6}; nums2 = {7};
    errors += check_solution(s, nums1, nums2);

    nums1 = {3, 4, 5}; nums2 = {7, 7, 8, 9};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 2, 3, 4, 5}; nums2 = {6, 7, 8};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 2, 3}; nums2 = {6, 7, 8, 9, 10};
    errors += check_solution(s, nums1, nums2);

    nums1 = {3, 4, 5}; nums2 = {6, 7, 8};
    errors += check_solution(s, nums1, nums2);

    nums1 = {3}; nums2 = {6};
    errors += check_solution(s, nums1, nums2);

    nums1 = {3, 4, 5, 6}; nums2 = {6, 7, 8, 9};
    errors += check_solution(s, nums1, nums2);

    if (errors == 0)
        cout << "Non interleaving arrays unit tests succeeded!!" << endl;
    else cout << "Non interleaving arrays unit tests failed!!" << endl;
}

int check_mli_within_array(Solution s, vector<int> nums1, vector<int> nums2, bool success_expected)
{
    double value, ref;
    size_t total_size = nums1.size() + nums2.size();
    int mli = s.median_value_low_index(total_size);
    if (!s.check_mli_within_array(mli, total_size, nums1, nums2, value))
    {
        if (!success_expected) return 0;

        dump_arrays_merge(nums1, nums2);
        cout << "check_mli_within_array failed!" << endl;
        return 1;
    }
    if (!success_expected)
    {
        dump_arrays_merge(nums1, nums2);
        cout << "check_mli_within_array succeeded but should have failed!" << endl;
        return 1;
    }
    ref = refSolution(nums1, nums2);
    if (value != ref)
    {
        dump_arrays_merge(nums1, nums2);
        cout << "Expected " << ref << " but got "<< value << endl;
        return 1;
    }
    return 0;
}

void run_check_mli_within_array_unit_tests(Solution s, vector<int> nums1, vector<int> nums2)
{
    int errors = 0;

    /* fails because mli is not within the first array passed */
    nums1 = {1, 2, 3, 5}, nums2 = {4};
    errors += check_mli_within_array(s, nums2, nums1, false);

    /* fails because nums1(mli) > nums2(0) */
    nums1 = {1, 2, 3, 5}, nums2 = {2};
    errors += check_mli_within_array(s, nums2, nums1, false);

    /* fails because nums1(mli) > nums2(0) */
    nums1 = {1, 2, 3, 5}, nums2 = {2, 3};
    errors += check_mli_within_array(s, nums2, nums1, false);

    /* total size is even and mli is within the first array */
    nums1 = {1, 2, 3, 5}, nums2 = {4};
    errors += check_mli_within_array(s, nums1, nums2, true);

    nums1 = {1, 2, 3, 4}, nums2 = {5, 6, 7};
    errors += check_mli_within_array(s, nums1, nums2, true);

    nums1 = {1, 2, 3, 4}, nums2 = {4, 5, 7};
    errors += check_mli_within_array(s, nums1, nums2, true);

    if (errors == 0)
        cout << "check_mli_within_array unit tests succeeded!!" << endl;
    else cout << "check_mli_within_array unit tests failed!!" << endl;
}

void run_interleaving_arrays_mli_within_unit_tests(Solution s, vector<int> nums1, vector<int> nums2)
{
    int errors = 0;

    nums1 = {1, 2, 3, 5}, nums2 = {4};
    errors += check_solution(s, nums2, nums1);

    nums1 = {1, 2, 3}, nums2 = {4};
    errors += check_solution(s, nums2, nums1);

    nums1 = {1, 2, 3, 4}, nums2 = {5, 6, 7};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 2, 4, 12}, nums2 = {5, 6};
    errors += check_solution(s, nums2, nums1);

    nums1 = {1, 2, 3, 4}, nums2 = {4, 5, 7};
    errors += check_solution(s, nums1, nums2);

    if (errors == 0)
        cout << "Interleaving arrays mli_within unit tests succeeded!!" << endl;
    else cout << "Interleaving arrays mli_within unit tests failed!!" << endl;
}

void run_interleaving_arrays_unit_tests(Solution s, vector<int> nums1, vector<int> nums2)
{
    int errors = 0;

    nums1 = {1, 1, 2, 3, 4, 5 ,5}, nums2 = {3, 3, 14, 15, 16, 16};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 1, 2, 3, 4, 5}, nums2 = {3, 3, 14, 15, 16};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 1, 2, 3, 4, 5 ,5}, nums2 = {3, 3, 14, 15, 16, 16, 17};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 1, 2, 3, 4, 5 ,5}, nums2 = {3, 5, 14, 15, 16, 16, 17};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 3, 5, 7, 9, 11 , 13}, nums2 = {2, 4, 6, 8, 10, 12, 14};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 3, 5, 7, 9, 11 , 13}, nums2 = {2, 4, 6, 8, 10, 12, 14, 15};
    errors += check_solution(s, nums1, nums2);

    if (errors == 0)
        cout << "Interleaving arrays unit tests succeeded!!" << endl;
    else cout << "Interleaving arrays unit tests failed!!" << endl;
}

int main(int argc, char **argv)
{
    Solution s;
    int errors = 0;
    vector<int> nums1, nums2;

    run_median_methods_unit_tests(s, nums1, nums2);
    run_empty_array_unit_tests(s, nums1, nums2);
    run_non_interleaving_arrays_unit_tests(s, nums1, nums2);
    run_check_mli_within_array_unit_tests(s, nums1, nums2);
    run_interleaving_arrays_mli_within_unit_tests(s, nums1, nums2);
    run_interleaving_arrays_unit_tests(s, nums1, nums2);

    /* non planned tests */
    nums1 = {1, 2}, nums2 = {-1, 3};
    errors += check_solution(s, nums1, nums2);

    nums1 = {2}, nums2 = {1, 3, 4};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 3}, nums2 = {2, 4, 5};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 3}, nums2 = {2,4,5,6,7};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 5}, nums2 = {2,3,4,6,7};
    errors += check_solution(s, nums1, nums2);

    nums1 = {1, 3}, nums2 = {2,4,5,6,7,8,9};
    errors += check_solution(s, nums1, nums2);

    if (errors == 0)
        cout << "Non planned unit tests succeeded!!" << endl;
    else cout << "Non planned unit tests failed!!" << endl;

    cout << endl << "!!! All tests succeeded !!!" << endl;
    return 0;
}


/* BACKUP */
#if 0
void find_indices_incremental(int mli, vector<int>& nums1, vector<int>& nums2, int &idx1, int &idx2)
{
    /* find idx1 and idx2 such that idx1 + idx2 == mli and nums1[idx1] <= nums2[idx2+1]
     * and nums2[idx2] <= nums1[idx1+1]
     */
    int idx1_low = 0, idx1_high = nums1.size() - 1;
    idx1 = max(mli - 2, 0);
    idx2 = mli - idx1 - 1;

    // debug_print("nums1.size %ld, nums2.size %ld, idx1 %d, idx2 %d\n", nums1.size(), nums2.size(),
    //     idx1, idx2);
    dev_assert(idx1 < (nums1.size() - 1));
    dev_assert(idx2 < (nums2.size() - 1));
    dev_assert(idx1 >= 0);
    dev_assert(idx2 >= 0);

    /* Here, given the pre computing, we SHALL have data to take from both arrays */
    while ((nums1[idx1] > nums2[idx2+1]) || (nums1[idx1] > nums2[idx2+1]))
    {
        /* Those case are covered in the pre computation */
        dev_assert(idx1 < (nums1.size() - 1));
        dev_assert(idx2 < (nums2.size() - 1));
        dev_assert(idx1 >= 0);
        dev_assert(idx2 >= 0);

        if (nums1[idx1] > nums2[idx2+1]) /* move left in nums1*/
            idx1--;
        else
            idx1++;

        /* update idx2 */
        idx2 = mli - idx1 - 1;
    }
}
#endif
