class Solution {
public:
    vector<int> prevPermOpt1(vector<int>& A) {
        if (A.size() == 0) return A;

        int minleft = A.back(), leftidx = A.size()-1;
        for (int idx = A.size()-2 ; idx >= 0 ; idx--) {
            if (A[idx] > minleft) {
                // find the left index
                for (int jdx = idx+1 ; jdx < A.size() ; jdx++) {
                    if ((A[jdx] < A[idx]) and (A[jdx] > minleft)) {
                        minleft = A[jdx];
                        leftidx = jdx;
                    }
                }
                // swap left and idx
                int tmp = A[idx];
                A[idx] = A[leftidx];
                A[leftidx] = tmp;
                break;
            }
            if (A[idx] <= minleft) {
                minleft = A[idx];
                leftidx = idx;
            }
        }
        return A;
    }
};
