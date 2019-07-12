class Solution {
private:
    int computeSatisifed(vector<int>& customers, vector<int>& grumpy, int &maxcustomers_grumpy) {
        int result = 0;
        const int *c = &customers[0], *g = &grumpy[0];
        for (int idx = 0 ; idx < customers.size() ; idx++) {
            if (*g) maxcustomers_grumpy = max(maxcustomers_grumpy, *c);
            result += *c++ * (*g++ ? 0 : 1);
        }
        return result;
    }
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {

        if (!customers.size()) return 0;

        int maxcustomers_grumpy = 0, origsat = computeSatisifed(customers, grumpy, maxcustomers_grumpy);
        if (X == 1) return origsat + maxcustomers_grumpy;

        int satX = 0, satNotX = 0;
        int *c = &customers[0], *g = &grumpy[0];
        for (int idx = 0 ; idx < X ; idx++) {satX += c[idx]; satNotX += c[idx] * (g[idx] ? 0 : 1);}

        int maxsat = origsat + satX - satNotX;
        //printf("idx[0]: satX(%d), satNotX(%d), origsat(%d), maxsat(%d)\n", satX, satNotX, origsat, maxsat);
        for (int idx = 1 ; idx < customers.size() ; idx++) {
            satX -= c[idx-1];
            satNotX -= c[idx-1] * (g[idx-1]? 0 : 1);
            if ((idx + X -1) < customers.size()) {
                satX += c[idx+X-1];
                satNotX += c[idx+X-1] * (g[idx+X-1]? 0 : 1);
            }
            maxsat = max(maxsat, origsat + satX - satNotX);
            //printf("idx[%d]: satX(%d), satNotX(%d), origsat(%d), maxsat(%d)\n", idx, satX, satNotX, origsat, maxsat);
        }
        return maxsat;
    }
};
