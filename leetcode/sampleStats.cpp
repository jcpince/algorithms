/*
1093. Statistics from a Large Sample
Medium

We sampled integers between 0 and 255, and stored the results in an array count:  count[k] is the
number of integers we sampled equal to k.

Return the minimum, maximum, mean, median, and mode of the sample respectively, as an array of
floating point numbers.  The mode is guaranteed to be unique.

(Recall that the median of a sample is:

    The middle element, if the elements of the sample were sorted and the number of elements is odd;
    The average of the middle two elements, if the elements of the sample were sorted and the number
    of elements is even.)



Example 1:

Input: count = [0,1,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0]
Output: [1.00000,3.00000,2.37500,2.50000,3.00000]

Example 2:

Input: count = [0,4,3,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
Output: [1.00000,4.00000,2.18182,2.00000,1.00000]



Constraints:

    count.length == 256
    1 <= sum(count) <= 10^9
    The mode of the sample that count represents is unique.
    Answers within 10^-5 of the true value will be accepted as correct.
*/

#define STATS_MIN       0
#define STATS_MAX       1
#define STATS_MEAN      2
#define STATS_MEDIAN    3
#define STATS_MODE      4

class Solution {
public:
    vector<double> sampleStats(vector<int>& count) {
        vector<double> stats(5, 0.0);
        stats[STATS_MIN] = -1.0;

        uint64_t sum = 0;
        int k_max = -1, mode = -1, num_elements = 0, med0_idx = -1, med0_offset = -1;
        for (int k = 0 ; k < count.size() ; k++) {
            int k_number = count[k];
            if (!k_number) continue;
            if (stats[STATS_MIN] < 0.0) stats[STATS_MIN] = k;
            stats[STATS_MAX] = k;
            if (k_number > k_max) {
                k_max = k_number;
                mode = k;
            }
            sum += k_number * k;
            if (med0_idx == -1) {
                med0_idx = k;
                med0_offset = k_number / 2;
            }
            else {
                int move = med0_offset + (num_elements + k_number) / 2 - num_elements / 2;
                while (move > count[med0_idx])
                    move -= count[med0_idx++];
                med0_offset = move;
            }
            num_elements += k_number;
        }
        stats[STATS_MEAN] = (double)sum / num_elements;
        if ((num_elements & 0x1) || ((med0_offset+1) < count[med0_idx])) {
            stats[STATS_MEDIAN] = med0_idx;
        } else {
            int med1_idx = med0_idx+1;
            while(!count[med1_idx]) med1_idx++;
            stats[STATS_MEDIAN] = (double)med0_idx + (double)(med1_idx - med0_idx) / 2.0;
        }
        stats[STATS_MODE] = mode;
        return stats;
    }
};
