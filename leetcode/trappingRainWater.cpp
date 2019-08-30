/* https://leetcode.com/problems/trapping-rain-water/
42. Trapping Rain Water
Hard

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.


The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcos for contributing this image!

Example:

Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
*/

/*class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() < 2)
            return 0;
        vector<int> bm{height.back()};
        for (int i = height.size() - 2; i > 1; --i)
            if (height[i] >= bm.back())
                bm.push_back(height[i]);
        //for (int num: bm)
        //    cout << num << ' ';
        int tot = 0;
        int fm = height[0];
        for (int i = 1; i < height.size() - 1; ++i){
            //cout << bm.size();
            tot += max(0, min(fm, bm.back()) - height[i]);
            fm = max(fm, height[i]);
            if (i > 1 && height[i] == bm.back())
                bm.pop_back();
        }
        return tot;
    }
};*/

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() < 3) return 0;

        vector<int> maxright(height.size());
        maxright[height.size()-1] = height.back();
        for (int idx = height.size()-2 ; idx >= 0 ; idx--)
            maxright[idx] = max(maxright[idx+1], height[idx]);

        int total_units = 0, maxleft = height[0];
        for (int idx = 1 ; idx < height.size() ; idx++) {
            int h = height[idx];
            int water_height = min(maxleft, maxright[idx]);
            if (height[idx] > maxleft) maxleft = height[idx];
            if (water_height > h) total_units += water_height - h;
        }
        return total_units;
    }
};
