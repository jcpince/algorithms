#! /usr/bin/python3

from collections import Counter
from typing import List
import argparse
import json

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
    def findRepeatedDnaSequences(self, s: str) -> List[str]:   
        seen = set()
        ans = set()
        for start in range(len(s) - 10 + 1):
            tmp = s[start:start + 10]
            if tmp in seen:
                ans.add(tmp)
            seen.add(tmp)
        return list(ans)

# class Solution:
#     def findRepeatedDnaSequences(self, s: str) -> List[str]:
#         size = len(s)
#         if size < 11:
#             return []
#         counter = Counter()
#         ans = list()

#         for i in range(0, size-9):
#             candidate = s[i:i+10]
#             print(candidate)
#             counter[candidate] += 1

#         for (seq, count) in counter.most_common():
#             if count == 1:
#                 break
#             ans.append(seq)
#         # print(counter)    
#         return ans
    
    def findRepeatedDnaSequences_naive(self, s: str) -> List[str]:
        size = len(s)
        if size < 11:
            return []
        visited = set()
        ans = list()
        for i in range(0, size-10):
            candidate = s[i:i+10]
            if candidate in visited:
                continue
            visited.add(candidate)
            j = i + 1
            while j < size - 9:
                subs = s[j:j+10]
                if subs == candidate:
                    ans.append(candidate)
                    break
                j += 1                
        return ans

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
        ind = test['in']
        expected = test['expected']
        result = s.findRepeatedDnaSequences(ind)
        if cmp_unordered_lists(result, expected):
            print("Test %s succeeded!" % test)
        else:
            print("Test %s failed: returned %s!" % (test, result))
            failures += 1
        #del s

    if failures > 0:
        print("%d tests failed over a total of %d tests" % (failures, len(tests)))
    else:
        print("All %d tests passed" % len(tests))
