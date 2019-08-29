#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

class Solution {
    static inline int unwind_stack(vector<int>& heights, stack<size_t> &smallers_idx, size_t idx) {

        int smaller_idx = smallers_idx.top();
        smallers_idx.pop();

        // When we compute the width, we take the previous smaller index in case some
        // indices have been removed previously (since they were taller than the one in the stack)
        int width = smallers_idx.empty() ? idx : idx - smallers_idx.top() - 1;
        // printf("Index[%d], width %d: area %d -- %d\n", smaller_idx, width,
        //     heights[smaller_idx] * width, smallers_idx.empty());
        return heights[smaller_idx] * width;
    }
public:
    int largestRectangleArea2(vector<int>& heights) {
        int sz = heights.size();
        vector<int> left(sz, -1);
        vector<int> right(sz, sz);
        stack<int> st;
        for (int i=0; i<sz; ++i) {
            while (!st.empty() && heights[st.top()]>=heights[i]) {
                right[st.top()] = i;
                st.pop();
            }
            if (!st.empty()) left[i] = st.top();
            st.push(i);
        }
        printf("largestRectangleArea(%s), left(%s), right(%s)\n", array2str(heights).c_str(),
            array2str(left).c_str(), array2str(right).c_str());
        int res = 0;
        for (int i=0; i<sz; ++i) {
            res = max(res, (right[i] - left[i] - 1) * heights[i] );
        }
        return res;
    }
    int largestRectangleArea(vector<int>& heights) {
        // Use a stack to store the previous indices of the histogram smaller than the current bar
        stack<size_t> smallers_idx;
        int ans = 0;

        for (size_t idx = 0 ; idx < heights.size() ; idx++) {
            if (smallers_idx.empty() || heights[smallers_idx.top()] <= heights[idx])
                smallers_idx.push(idx);
            else {
                // The current bar is smaller than the last smaller
                // Unwind the stack until we found a bigger one and update the area
                // Note that the stack contains elements that are smaller and smaller, so the area
                // is the width between our current index and the small bar multiplied by the small
                // bar height
                while(!smallers_idx.empty() && heights[smallers_idx.top()] > heights[idx]) {
                    int area = unwind_stack(heights, smallers_idx, idx);
                    if (area > ans) ans = area;
                }
                smallers_idx.push(idx);
            }
        }

        // Now, we're done, simply finish unwinding the stack
        while(!smallers_idx.empty()) {
            int area = unwind_stack(heights, smallers_idx, heights.size());
            if (area > ans) ans = area;
        }

        return ans;
    }
};

int getMaxArea(vector<int>&  hist, int n)
{
    // Create an empty stack. The stack holds indexes
    // of hist[] array. The bars stored in stack are
    // always in increasing order of their heights.
    stack<int> s;

    int max_area = 0; // Initalize max area
    int tp;  // To store top of stack
    int area_with_top; // To store area with top bar
                       // as the smallest bar

    // Run through all bars of given histogram
    int i = 0;
    while (i < n)
    {
        // If this bar is higher than the bar on top
        // stack, push it to stack
        if (s.empty() || hist[s.top()] <= hist[i])
            s.push(i++);

        // If this bar is lower than top of stack,
        // then calculate area of rectangle with stack
        // top as the smallest (or minimum height) bar.
        // 'i' is 'right index' for the top and element
        // before top in stack is 'left index'
        else
        {
            // Get the indices from the stack until hist[s.top()] <= hist[i] or the stack is empty
            tp = s.top();  // store the top index
            s.pop();  // pop the top

            // Calculate the area with hist[tp] stack
            // as smallest bar
            area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1);

            if (s.empty())
                printf("Inner Pop(%d), smallest elem => area is %d\n", tp, area_with_top);
            else printf("Inner Pop(%d), top(%d) => area is %d\n", tp, s.top(), area_with_top);

            // update max area, if needed
            if (max_area < area_with_top)
                max_area = area_with_top;
        }
    }

    // Now pop the remaining bars from stack and calculate
    // area with every popped bar as the smallest bar
    while (s.empty() == false)
    {
        tp = s.top();
        s.pop();
        area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1);

        if (s.empty())
            printf("Pop(%d), smallest elem => area is %d\n", tp, area_with_top);
        else printf("Pop(%d), top(%d) => area is %d\n", tp, s.top(), area_with_top);

        if (max_area < area_with_top)
            max_area = area_with_top;
    }

    return max_area;
}

int run_test_case(void *_s, TestCase *tc) {
    UNUSED(_s);
    vector<int> heights = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
    int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

    Solution s;
    int result = s.largestRectangleArea(heights);
    //int result = getMaxArea(heights, heights.size());

    if (result == expected) return 0;

    printf("largestRectangleArea(%s) returned %d but expected %d\n", array2str(heights).c_str(),
        result, expected);
    assert(continue_on_failure);
    return 1;
}

int main(int argc, char **argv) {
    int tests_ran = 0;
    const char *tc_id = NULL;

    if (argc < 2 || argc > 3)
    {
        cerr << "Usage: " << argv[0] << " <json test file> [test case index or name]" << endl;
        cerr << "Where: [test case index or name] specifies which test to run (all by default)" <<
            endl;
        return -1;
    }

    UnitTests uts(NULL, &run_test_case, argv[1]);

    if (argc == 3) tc_id = argv[2];

    int errors_count = uts.run_test_cases(tc_id, tests_ran);
    if (errors_count == 0)
        cout << "All " << tests_ran << " test(s) succeeded!!!" << endl;
    else
        cout << errors_count << " test(s) failed over a total of " << tests_ran << endl;

    return errors_count;
}
