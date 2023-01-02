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
    def fractionToDecimal_naive(self, numerator: int, denominator: int) -> str:
        if numerator == 0:
            return "0"
        rem_hist = set()
        rem_stack = list()
        ans = "" if numerator * denominator > 0 else "-"
        if numerator  < 0:
            numerator = -numerator
        if denominator  < 0:
            denominator = -denominator
        if numerator < denominator:
            ans += "0."
            remainder = numerator
        else:
            res = numerator // denominator
            ans += "%d" % res
            remainder = numerator % denominator
            if remainder > 0:
                ans += '.'
        
        remainder *= 10
        while remainder:
            if remainder in rem_hist:
                break
            if remainder >= denominator:
                res = remainder // denominator
                #print("remainder %d: adds %d; remainder becomes %d" % (remainder, res, remainder % denominator))
                rem_stack.append((remainder, res))
                rem_hist.add(remainder)
                remainder = remainder % denominator
            else:
                #print("remainder %d: adds 0" % remainder)
                rem_hist.add(remainder)
                rem_stack.append((remainder, 0))
            remainder *= 10

        for rem, res in rem_stack:
            if rem == remainder:
                ans += "("
            ans += str(res)
            #print(rem, res, decimal_part)
        if remainder > 0:
            ans += ")"
        return ans
    def fractionToDecimal(self, numerator: int, denominator: int) -> str:
        if numerator == 0:
            return "0"
        rem_hist = dict()
        ans = "" if numerator * denominator > 0 else "-"
        if numerator  < 0:
            numerator = -numerator
        if denominator  < 0:
            denominator = -denominator

        if numerator < denominator:
            ans += "0."
            remainder = numerator
        else:
            res = numerator // denominator
            ans += "%d" % res
            remainder = numerator % denominator
            if remainder > 0:
                ans += '.'
        
        remainder *= 10
        while remainder:
            if remainder in rem_hist:
                recurr_pos = rem_hist[remainder]
                return ans[:recurr_pos] + '(' + ans[recurr_pos:] + ')'
            rem_hist[remainder] = len(ans)
            if remainder >= denominator:
                ans += str(remainder // denominator)
                remainder = remainder % denominator
            else:
                ans += "0"
            remainder *= 10
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
        result = s.fractionToDecimal(ind[0], ind[1])
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
