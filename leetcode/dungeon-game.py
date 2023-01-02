#! /usr/bin/python3

from collections import defaultdict, deque
from typing import List
import argparse
import json
import sys

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
    def calculateMinimumHP(self, dungeon: List[List[int]]) -> int:
        n = len(dungeon[0])
        m = len(dungeon)
        minlifemat = list()
        for _ in range(0, m):
            minlifemat.append([0] * n)

        # Initialize the target and borders
        minlifemat[m-1][n-1] = 1 + max(0, -dungeon[m-1][n-1])
        y = n  - 1
        for x in range(m-2, -1, -1):
            # print((x, y))
            minlifemat[x][y] = max(1, minlifemat[x+1][y] - dungeon[x][y])
        x = m  - 1
        for y in range(n-2, -1, -1):
            # print((x, y))
            minlifemat[x][y] = max(1, minlifemat[x][y+1] - dungeon[x][y])

        # Initialize the inners
        for x in range(m-2, -1, -1):
            for y in range(n-2, -1, -1):
                # print((x, y))
                minlifemat[x][y] = max(1,
                    min(minlifemat[x][y+1], minlifemat[x+1][y]) - dungeon[x][y])
        # print(minlifemat)
        return minlifemat[0][0]

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
        dungeon = test['in']
        expected = test['expected']
        result = s.calculateMinimumHP(dungeon)
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
