/*
775. Global and Local Inversions
Medium

We have some permutation A of [0, 1, ..., N - 1], where N is the length of A.

The number of (global) inversions is the number of i < j with 0 <= i < j < N and A[i] > A[j].

The number of local inversions is the number of i with 0 <= i < N and A[i] > A[i+1].

Return true if and only if the number of global inversions is equal to the number of local inversions.

Example 1:

Input: A = [1,0,2]
Output: true
Explanation: There is 1 global inversion, and 1 local inversion.

Example 2:

Input: A = [1,2,0]
Output: false
Explanation: There are 2 global inversions, and 1 local inversion.

Note:

    A will be a permutation of [0, 1, ..., A.length - 1].
    A will have length in range [1, 5000].
    The time limit for this problem has been reduced.

Test cases:
[0]
[1,0,2]
[1,2,0]
[0,2,1,4,3]
[2,1,0]
*/

/* Idea: Check that all permutations are local*/
class Solution {
public:
    bool isIdealPermutation(vector<int>& A) {
        vector<int>::iterator it = A.begin();
        int prev = *it++, idx = 1;
        if (prev > 1) return false;
        while (it != A.end()) {
            if (*it > (idx+1)) return false;
            if (*it < (prev-1)) return false;
            prev = *it++;
            idx++;
        }
        return true;
    }
};
