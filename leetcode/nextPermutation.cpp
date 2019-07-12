class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if (nums.size() < 2) return;

        int pivot = nums.size()-1;
        while ((pivot > 0) and (nums[pivot-1] >= nums[pivot])) pivot--;

        if (pivot == 0) {
            //printf("In reverse order, next is in order\n");
            sort(nums.begin(), nums.end());
            return;
        }
        // swap pivot and min_post_pivot and sort the rest
        pivot--;
        int pivot_value = nums[pivot], min_post_pivot = INT_MAX, post_pivot_index = -1;
        int idx = pivot + 1;
        while (idx < nums.size()) {
            if (nums[idx] < min_post_pivot and nums[idx] > pivot_value) {
                min_post_pivot = nums[idx];
                post_pivot_index = idx;
            }
            idx++;
        }

        //printf("pivot %d, min_post_pivot(%d at index %d)\n", pivot, min_post_pivot, post_pivot_index);
        if (post_pivot_index < 0) return;

        int tmp = nums[pivot];
        nums[pivot] = min_post_pivot;
        nums[post_pivot_index] = tmp;
        sort(nums.begin()+pivot+1, nums.end());

        //printf("pivot %d, min_post_pivot(%d at index %d)\n", pivot, min_post_pivot, post_pivot_index);
    }
};
