#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = false;

static const auto _=[](){
        ios::sync_with_stdio(false);
        cin.tie(nullptr);cout.tie(nullptr);
        return 0;
}();

class Solution {
        int inline interval_sum(const vector<int>& left_sums, int left, int right) {
                return left_sums[right+1] - left_sums[left];
        }
public:
        int subarraySum2(const vector<int>& nums, int k) {
                vector<int> left_sums(nums.size()+1, 0);
                int idx = 0, prev_sum = 0;
                for (int num : nums) {
                        //printf("Set left_sum[%d] = %d\n", idx, prev_sum);
                        left_sums[idx++] = prev_sum;
                        prev_sum += num;
                }
                //printf("Set left_sum[%d] = %d\n", idx, prev_sum);
                left_sums[idx] = prev_sum;

                int left = 0, right, result = 0;
                while (left < (int)nums.size())
                {
                        if (nums[left] == k) result++;
                        for (right = left+1 ; right < (int)nums.size() ; right++) {
                                //printf("Interval %d, %d = %d\n", left, right, interval_sum(left_sums, left, right));
                                if (interval_sum(left_sums, left, right) == k)
                                result++;
                        }
                        left++;
                }
                return result;
        }
    int inline find_rightsum(const int *left_sums, const int &target, const int &from, const int &size) {
        for (int idx = from ; idx < size ; idx++)
            if (left_sums[idx] == target) return idx;
        return -1;
    }
    int subarraySum(const vector<int>& nums, int k) {
        int size = nums.size();
        int *left_sums = (int *)calloc(size+1, sizeof(int));
        int idx = 0, prev_sum = 0;
        for (int num : nums) {
            //printf("Set left_sum[%d] = %d\n", idx, prev_sum);
            left_sums[idx++] = prev_sum;
            prev_sum += num;
        }
        //printf("Set left_sum[%d] = %d\n", idx, prev_sum);
        left_sums[idx] = prev_sum;

        int left = 0, right, result = 0;
        while (left < size)
        {
            //if (nums[left] == k) result++;
            int delta = left_sums[left] + k;
            //if (!delta) result++;
            right = left;
            //printf("look for %d in left_sum from index %d\n", delta, right);
            while ((right = find_rightsum(left_sums, delta, right+1, size + 1)) > 0)
                result++;
            left++;
        }

        free(left_sums);
        return result;
    }
};

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<int> nums = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["nums"];
        int k = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME]["k"];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        int result = s.subarraySum(nums, k);

        if (result == expected) return 0;

        printf("subarraySum(%s, %d) returned %d but expected %d\n",
                array2str(nums).c_str(), k, result, expected);
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
