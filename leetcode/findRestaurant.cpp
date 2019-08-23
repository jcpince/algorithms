class Solution {
    void commonBest(vector<string>& small_list, vector<string>& large_list, vector<string> &result) {
        int best_sum = (int)small_list.size() + (int)large_list.size() + 1;
        int small_idx = 0;
        vector<string>::iterator best_large_it = large_list.end();
        for (string restau1 : small_list) {
            vector<string>::iterator it = find(large_list.begin(), best_large_it, restau1);
            if (it < best_large_it) {
                int large_idx = distance(large_list.begin(), it);
                if ((small_idx + large_idx) == best_sum)
                    result.push_back(restau1);
                else if ((small_idx + large_idx) < best_sum) {
                    result.clear();
                    result.push_back(restau1);
                    best_sum = small_idx + large_idx;
                }
            }
            small_idx++;
        }
    }
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        vector<string> ans;
        if (list1.size() < list2.size()) commonBest(list1, list2, ans);
        else commonBest(list2, list1, ans);
        return ans;
    }
};
