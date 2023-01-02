#! /usr/bin/python3

from collections import defaultdict, deque
from typing import List
import argparse
import json
import string

debug_tool = False

def print_debug(message):
    global debug_tool
    if not debug_tool:
        return
    print("Debug [InitiatorHelper]: %s" % (message))

def print_log(message, logfile):
    print(message, file=logfile)

def print_info(message):
    print("Info [InitiatorHelper]: %s" % (message))

def print_error(message):
    print("Error [InitiatorHelper]: %s" % (message))

def print_fatal(message):
    print("\n\nFATAL [InitiatorHelper]: %s" % (message))

class Solution:
    def find_reduce(self, numbers, needle, left, right) -> (int, int):
        while left < right:
            middle = left + (right - left) // 2
            if numbers[middle] < needle:
                left = middle + 1
            elif numbers[middle] > needle:
                right = middle - 1
            else:
                return (middle, right)
        if numbers[left] != needle:
            left = -1
        return (left, right)
        
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        idx0 = 0
        num0 = numbers[idx0] + 1
        end = len(numbers) - 1
        while True:
            num0 = numbers[idx0]
            (idx1, end) = self.find_reduce(numbers, target - num0, idx0+1, end)
            if idx1 != -1:
                return [idx0 + 1, idx1 + 1]
            while num0 == numbers[idx0]:
                idx0 += 1

def cmp_unordered_lists(l0, l1):
    if len(l0) != len(l1):
        return False
    for e in l0:
        try:
            idx = l1.index(e)
            del l1[idx]
        except ValueError:
            return False
    return len(l1) == 0

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    parser.add_argument("-j", "--json-file", required=True, help="json test file",
                type=str) # argparse.FileType('r'))
    parser.add_argument("-i", "--test-index", help="index of the test to run",
                type=int, default=-1)
    args = parser.parse_args()
    print(args.json_file)
    if args.json_file.endswith(".py.unittests.json"):
        args.json_file = args.json_file.replace(".py.unittests.json", ".unittests.json")
        print("replaced:", args.json_file)
    spec = None
    with open(args.json_file, "r") as f:
        spec = json.load(f)
    tests = spec["tests"]
    if args.test_index != -1:
        if args.test_index < len(tests):
            tests = [ tests[args.test_index] ]
        else:
            print_fatal("Wrong test index %d: only %d tests available" %
                (args.test_index, len(tests)))
            exit(-1)

    failures = 0
    s = Solution()
    for test in tests:
        print_debug("Test to run: %s" % test)
        numbers = test['in']
        target = test['target']
        expected = test['expected']
        result = s.twoSum(numbers, target)
        if result == expected:
            print("Test %s succeeded!" % test)
        else:
            print("Test %s failed: returned %s!" % (test, result))
            failures += 1
        #del s

    if failures > 0:
        print("%d tests failed over a total of %d tests" % (failures, len(tests)))
    else:
        print("All %d tests passed" % len(tests))
