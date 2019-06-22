#! /usr/bin/python3

# 781. Rabbits in Forest
# Medium
#
# In a forest, each rabbit has some color. Some subset of rabbits (possibly all of them) tell you how many other rabbits have the same color as them. Those answers are placed in an array.
#
# Return the minimum number of rabbits that could be in the forest.
#
# Examples:
# Input: answers = [1, 1, 2]
# Output: 5
# Explanation:
# The two rabbits that answered "1" could both be the same color, say red.
# The rabbit than answered "2" can't be red or the answers would be inconsistent.
# Say the rabbit that answered "2" was blue.
# Then there should be 2 other blue rabbits in the forest that didn't answer into the array.
# The smallest possible number of rabbits in the forest is therefore 5: 3 that answered plus 2 that didn't.
#
# Input: answers = [10, 10, 10]
# Output: 11
#
# Input: answers = []
# Output: 0
#
# Note:
#
#     answers will have length at most 1000.
#     Each answers[i] will be an integer in the range [0, 999].



import array

class Solution:
    def numRabbits(self, answers: list) -> int:
        groups = dict()
        for g in answers:
            if (g+1) in groups.keys():
                groups[g+1] += 1
            else:
                groups[g+1] = 1
        #print(groups)
        num_rabbits = 0
        for r in groups.keys():
            n = groups[r]
            if n == 1:
                # Unique groups
                num_rabbits += r
            else:
                # Multiple groups
                num_rabbits += r * int(n / r)
                if n % r != 0:
                    num_rabbits += r
        return num_rabbits

    def numRabbits(self, answers: list) -> int:
        groups = array.array('H', [0]*1000)
        for g in answers:
            groups[g+1] += 1
        num_rabbits = 0
        r = 0
        for n in groups:
            if n == 0:
                r += 1
                continue
            if n == 1:
                # Unique groups
                num_rabbits += r
            else:
                # Multiple groups
                num_rabbits += r * int(n / r)
                if n % r != 0:
                    num_rabbits += r
            r += 1
        return num_rabbits

def check_solution():
    s = Solution()
    answers = [1, 1, 2]
    result = s.numRabbits(answers)
    assert(result == 5)

    answers = []
    result = s.numRabbits(answers)
    assert(result == 0)

    answers = [10, 10, 10]
    result = s.numRabbits(answers)
    assert(result == 11)

    answers = [2, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4]
    result = s.numRabbits(answers)
    assert(result == 17)

    print("All tests passed successfully!!")

check_solution()
