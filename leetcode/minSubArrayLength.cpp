class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {

        if (!nums.size()) return 0;
        if (nums.size() < 2) return nums[0] >= s ? 1 : 0;
        if (nums[0] >= s) return 1;

        int left = 0, right = 1, minsize;
        int sum = nums[left] + nums[right];
        minsize = sum < s ? INT_MAX : right - left + 1;

        while (left < nums.size()) {
            if (sum < s) {
                if ((right + 1) == nums.size()) break;
                int r = nums[++right];
                if (r >= s) return 1;
                sum += r;
            } else {
                minsize = min(minsize, right - left + 1);
                sum -= nums[left++];
            }
        }
        if (sum >= s) minsize = min(minsize, right - left + 1);

        return minsize == INT_MAX ? 0 : minsize;
    }
};
