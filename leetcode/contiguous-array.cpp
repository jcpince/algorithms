#include <bits/stdc++.h>

//#define DEBUG 1
#undef DEBUG

#include <TreeNode.h>
#include <UnitTests.h>
#include <TestsHelper.h>

using namespace std;

const bool continue_on_failure = true;

class Solution {
public:
        int findMaxLength2(vector<int>& nums) {
                int sum = 0, result = 0;
                map<int, uint32_t> intervals;
                map<int, uint32_t>::iterator it = intervals.begin();
                intervals[0] = 0;
                for (unsigned int idx = 1 ; idx < nums.size()+1 ; idx++) {
                        sum += nums[idx-1] ? 1 : -1;
                        if (intervals.find(sum) == intervals.end()) {
                                intervals[sum] = (uint32_t)idx | ((uint32_t)idx << 16);
                                //printf("Half intervals[%d] = 0x%08x\n", sum, intervals[sum]);
                        }
                        else {
                                intervals[sum] = (intervals[sum] & 0xffff) | ((uint32_t)idx << 16);
                                //printf("Complete intervals[%d] = 0x%08x\n", sum, intervals[sum]);
                        }
                }
                for ( it = intervals.begin() ; it != intervals.end() ; it++) {
                        uint32_t low = it->second & 0xffff,
                                high = (it->second >> 16) & 0xffff;
                        // assert(high >= low);
                        // printf("intervals[%d] is %d -- %d\n", it->first, low, high);
                        if (high - low > (uint32_t)result)
                                result = high - low;
                }
                return result;
        }
        int off0 = INT_MAX;
        int inline sum2idx(int &sum) {
                return sum - off0;
        }
        int findMaxLength(vector<int>& nums) {
                int sum = 0, result = 0;
                // The sum can be < 0 if more 0s than ones
                for (int num : nums)
                        off0 = min(off0, (sum += num ? 1 : -1));

                //printf("offset = %d\n", off0);
                //vector<int> sums(nums.size(), -1);
                int sums[nums.size()];
                memset(sums, 0xff, sizeof(sums));
                sum = 0;
                for (int idx = 0 ; idx < (int)nums.size() ; idx++) {
                        sum += nums[idx] ? 1 : -1;
                        // printf("idx %d: sum = %d, sumsidx = %d\n", idx, sum, sum2idx(sum));
                        // assert(sum2idx(sum) >= 0);
                        if (!sum)
                                result = max(result, idx + 1);
                        else if (sums[sum2idx(sum)] < 0) {
                                // printf("Sets sums[%d] = %d\n", sum2idx(sum), idx);
                                sums[sum2idx(sum)] = idx;
                        }
                        else  {
                                // printf("Gets sums[%d] = %d\n", sum2idx(sum), sums[sum2idx(sum)]);
                                // assert(sums[sum2idx(sum)] >= 0);
                                result = max(result, idx - sums[sum2idx(sum)]);
                        }

                }
                return result;
        }
};

/*class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int maxSize = 0, count = 0, size = nums.size(), count0 = 0;

        for(const auto n: nums)
            if(!n) ++count0;

        vector<int> m(size + 1, -2); // Use -2 to mean uninitialized

        m[count0] = -1;
        for(int i = 0; i < size; ++i) {
            count += nums[i] == 0 ? -1 : 1;
            const int d = count0 + count;
            if(m[d] != -2) {
                maxSize = max(maxSize, i - m[d]);
            }
            else m[d] = i;
        }
        return maxSize;
    }
};*/

auto gucciGang = []() {std::ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);return 0;}();

int run_test_case(void *_s, TestCase *tc) {
        UNUSED(_s);
        vector<int> array = tc->test_case[JSON_TEST_CASE_IN_FIELDNAME];
        int expected = tc->test_case[JSON_TEST_CASE_EXPECTED_FIELDNAME];

        Solution s;
        int result = s.findMaxLength(array);

        if (result == expected) return 0;

        printf("findMaxLength(%s) returned %d but expected %d\n",
        array2str(array).c_str(), result, expected);
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
