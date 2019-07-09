class Solution {
private:
    size_t find_smallest_abs(const vector<int>& A) {

        // only one element, return index 0
        if (A.size() == 1) return 0;

        // At least 2 elements but all the same sign, return 0 if A0 is >0 and size-1 otherwise
        if (A[0] * A[A.size() - 1] >= 0) return A[0] >= 0 ? 0 : A.size() - 1;

        // At least 2 elements but check if the head or tail is the return value
        if (A[0] * A[1] <= 0) return 0;
        if (A[A.size() - 1] * A[A.size() - 2] <= 0) return A.size() - 2;

        size_t middle, start = 0, end = A.size()-1;

        while(start < end)
        {
            middle = (start + end) / 2;
            if(A[middle] * A[middle+1] <= 0) return middle;
            else if (A[middle] > 0) end = middle;
            else start = middle;
        }
        return middle;
    }
public:
    vector<int> sortedSquares(vector<int>& A) {
        if (!A.size()) return {};

        vector<int> squares;
        size_t smallest_abs_index = find_smallest_abs(A);
        int left = smallest_abs_index, right = smallest_abs_index+1;
        while (left >= 0 and right < A.size()) {
            if (abs(A[left]) < abs(A[right])) {
                squares.push_back(A[left] * A[left]);
                left--;
            } else {
                squares.push_back(A[right] * A[right]);
                right++;
            }
        }
        if (left >= 0) while(left >= 0) {squares.push_back(A[left] * A[left]);left--;}
        if (right < A.size()) while(right < A.size()) {squares.push_back(A[right] * A[right]);right++;}


        return squares;
    }
};
