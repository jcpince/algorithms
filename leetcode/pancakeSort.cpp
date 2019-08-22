class Solution {
    void reverse(vector<int>& A, int k) {
        size_t l = 0, r = (size_t)k;
        while (l < r) {
            int t = A[l];
            A[l] = A[r];
            A[r] = t;
            l++;
            r--;
        }
    }
    size_t maxIdx(vector<int>& A, int k) {
        int mx = A[0];
        size_t max_idx = 0;
        for (size_t off = 0 ; off <= (size_t)k ; off++) {
            if (A[off] > mx) {
                mx = A[off];
                max_idx = off;
            }
        }
        return max_idx;
    }
public:
    vector<int> pancakeSort(vector<int>& A) {
        if (A.size() < 2) return {};

        vector<int> ans;
        size_t k = A.size()-1;
        while (k > 0) {
            size_t max_idx = maxIdx(A, k);
            if (max_idx < k) {
                reverse(A, max_idx);
                reverse(A, k);
                if (max_idx)
                    ans.push_back(max_idx+1);
                ans.push_back(k+1);
            }
            k--;
        }
        int a0 = A[0];
        for (int a : A) {
            assert(a >= a0);
        }
        return ans;
    }
};
