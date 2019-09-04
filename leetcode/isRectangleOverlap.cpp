class Solution {
    bool common_range(int x0, int x1, int x2, int x3) {
        if (x0 > x1) swap(x0, x1);
        if (x2 > x3) swap(x2, x3);
        return ((x1 > x2) and (x3 > x0)) or ((x3 > x0) and (x1 > x2));
    }
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        int x1_0 = rec1[0], y1_0 = rec1[1], x1_1 = rec1[2], y1_1 = rec1[3];
        int x2_0 = rec2[0], y2_0 = rec2[1], x2_1 = rec2[2], y2_1 = rec2[3];

        if (!common_range(x1_0, x1_1, x2_0, x2_1)) return false;
        return common_range(y1_0, y1_1, y2_0, y2_1);
    }
};
