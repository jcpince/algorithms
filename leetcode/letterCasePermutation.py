#! /usr/bin/python3

# 784. Letter Case Permutation
# Easy
#
# Given a string S, we can transform every letter individually to be lowercase or uppercase to create another string.  Return a list of all possible strings we could create.
#
# Examples:
# Input: S = "a1b2"
# Output: ["a1b2", "a1B2", "A1b2", "A1B2"]
#
# Input: S = "3z4"
# Output: ["3z4", "3Z4"]
#
# Input: S = "12345"
# Output: ["12345"]
#
# Note:
#
#     S will be a string with length between 1 and 12.
#     S will consist only of letters or digits.



from typing import List

class Solution:
    def letterCasePermutation(self, S: str, prefix: List[str] = "") -> List[str]:
        if S == None:
            return []
        c = S[0]
        if len(S) == 1 and c.isalpha():
            if c.islower():
                return [prefix + c, prefix + c.upper()]
            else:
                return [prefix + c.lower(), prefix + c]

        if S.isdecimal():
            return [prefix + S]

        if c.isalpha():
            if c.islower():
                return self.letterCasePermutation(S[1:], prefix+c) + \
                    self.letterCasePermutation(S[1:], prefix + c.upper())
            else:
                return self.letterCasePermutation(S[1:], prefix+c.lower()) + \
                    self.letterCasePermutation(S[1:], prefix + c)

        return self.letterCasePermutation(S[1:], prefix + c)

    def letterCasePermutation(self, S: str) -> List[str]:
        if S == None:
            return []

        if S.isdecimal():
            return [S]

        results = [S]
        for idx, c in enumerate(S):
            nb_prev_results = len(results)
            for jdx in range(nb_prev_results):
                result = results[jdx]
                if c.islower():
                    results.append(result[0:idx]+c.upper()+result[idx+1:])
                elif c.isupper():
                    results.append(result[0:idx]+c.lower()+result[idx+1:])
        return results

    def countPermutations(self, S: str) -> int:
        count = 0
        for l in S:
            if l.isalpha():
                count += 1
        return 2 ** count

def check_solution():
    s = Solution()
    text = "a1b2"
    result = s.letterCasePermutation(text)
    assert(len(result) == s.countPermutations(text))

    text = "3z4"
    result = s.letterCasePermutation(text)
    assert(len(result) == s.countPermutations(text))

    text = "12345"
    result = s.letterCasePermutation(text)
    assert(len(result) == s.countPermutations(text))

    text = "1e2r5t3y6uargskj665"
    result = s.letterCasePermutation(text)
    assert(len(result) == s.countPermutations(text))

    print("All tests passed successfully!!")

check_solution()
