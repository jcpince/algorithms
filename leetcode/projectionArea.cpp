class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int xyarea = 0, yzarea = 0, zxarea = 0;

        int ymax = (int)grid.size();
        if (!ymax) return 0;

        int xmax = (int)grid[0].size();
        vector<int> maxzxs(xmax, 0);
        for (int x = 0 ; x < xmax ; x++) {
            int maxyz = 0;
            for (int y = 0 ; y < xmax ; y++) {
                int height = grid[x][y];
                if (!height) continue;
                xyarea++;
                if (height > maxyz)
                    maxyz = height;
                if (height > maxzxs[y])
                    maxzxs[y] = height;
            }
            yzarea += maxyz;
        }
        zxarea = accumulate(maxzxs.begin(), maxzxs.end(), 0);
        return xyarea + yzarea + zxarea;
    }
};
