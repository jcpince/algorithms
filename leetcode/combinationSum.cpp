/*
Given a set of candidate numbers (candidates) (without duplicates) and a target number (target),
find all unique combinations in candidates where the candidate numbers sums to target.

The same repeated number may be chosen from candidates unlimited number of times.

Note:

All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.

Example 1:

Input: candidates = [2,3,6,7], target = 7,
A solution set is:
[
[7],
[2,2,3]
]

Example 2:

Input: candidates = [2,3,5], target = 8,
A solution set is:
[
[2,2,2,2],
[2,3,3],
[3,5]
]

*/
class Solution {
        void rec(vector<int>& candidates, int target, vector<vector<int>> &results, int idx = 0,
                vector<int> current = {}, int sum = 0) {

                if (sum == target) {
                        results.push_back(current);
                        return;
                }

                if (idx >= candidates.size()) return;

                if (sum + candidates[idx] > target) return;

                // Skip the current
                rec(candidates, target, results, idx+1, current, sum);

                // Add the current up to n times
                while ((sum + candidates[idx]) <= target) {
                        sum += candidates[idx];
                        current.push_back(candidates[idx]);
                        rec(candidates, target, results, idx+1, current, sum);
                }
        }
        void recurse(vector<int>& candidates, int target, int idx,
                vector<vector<int>> &result, vector<int> base) {

                int candidate = candidates[idx];
                if (candidate > target) {
                        return;
                }
                if (candidate == target) {
                        base.push_back({target});
                        result.push_back(base);
                        return;
                }

                int mult = target / candidate;
                if (target % candidate == 0) {
                        for (int i = 0 ; i < mult ; i++)
                        base.push_back(candidate);
                        result.push_back(base);
                        for (int i = 0 ; i < mult ; i++)
                        base.pop_back();
                        mult-=2;
                }
                while(mult >= 0 && idx+1 < candidates.size()) {
                        for (int i = 0 ; i < mult ; i++)
                        base.push_back(candidate);
                        recurse(candidates, target-(candidate * mult), idx+1, result, base);
                        for (int i = 0 ; i < mult ; i++)
                        base.pop_back();
                        mult--;
                }
        }
public:
        vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
                if (candidates.size() == 0) return {{}};
                sort(candidates.begin(), candidates.end());
                vector<vector<int>> results;
                rec(candidates, target, results);
                return results;
        }
        vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
                sort(candidates.begin(), candidates.end());
                vector<vector<int>> result;
                recurse(candidates, target, 0, result, {});
                return result;
        }
};
