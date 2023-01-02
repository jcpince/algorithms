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
    print("Debug: %s" % (message))

def print_info(message):
    print("Info: %s" % (message))

def print_error(message):
    print("Error: %s" % (message))

def print_fatal(message):
    print("\n\nFATAL: %s" % (message))

class Solution:
    def get_daily_gains(self, prices):
        daily_gains = list()
        price0 = prices[0]
        gain = 0
        for price in prices[1:]:
            # print(price0, price, gain)
            if gain > 0 and price < price0:
                daily_gains.append(gain)
                gain = 0
            elif gain < 0 and price > price0:
                if len(daily_gains) > 0:
                    daily_gains.append(gain)
                gain = 0
            gain += price - price0
            price0 = price
        if gain > 0:
            daily_gains.append(gain)
        return daily_gains

    def maxProfit_wrong(self, k: int, prices: List[int]) -> int:
        if k < 1 or len(prices) < 2:
            return 0
        daily_gains = self.get_daily_gains(prices)
        # Consolidate gains
        idx = 0
        while idx + 2 < len(daily_gains):
            gain0 = daily_gains[idx]
            loss = daily_gains[idx + 1]
            gain1 = daily_gains[idx + 2]
            _3days_gain = gain0 + loss + gain1
            if _3days_gain > gain0 and _3days_gain > gain1:
                # merge
                daily_gains[idx] = _3days_gain
                del daily_gains[idx + 2]
                del daily_gains[idx + 1]
                idx = max(0, idx - 2)
            else:
                idx += 2
        print("daily_gains unsorted:", daily_gains)
        daily_gains.sort()
        # print("daily_gains:", daily_gains[::-1])
        ans = 0
        for gain in daily_gains[::-1]:
            if k == 0 or gain < 0: break
            ans += gain
            k -= 1
        return ans

    def recurse(self, daily_gains, k, gain0 = 0):
        if len(daily_gains) < 3 or k == 1:
            # done
            print("recurse(%s, %d, %d) done" % (daily_gains, k, gain0))
            return gain0 + daily_gains[0]
        # Return the max between selling now or selling later
        sell_now = self.recurse(daily_gains[2:], k-1)
        sell_later = self.recurse(daily_gains[2:], k, gain0 + daily_gains[0] + daily_gains[1])
        print("returning max of %d + self.recurse(%s, %d) and self.recurse(%s, %d, %d)" %
            (gain0 + daily_gains[0], daily_gains[2:], k-1, daily_gains[2:], k, gain0 + daily_gains[0] + daily_gains[1]))
        return max(gain0 + daily_gains[0] + sell_now, sell_later)

    def maxProfit(self, k: int, prices: List[int]) -> int:
        if k < 1 or len(prices) < 2:
            return 0
        return self.recurse(self.get_daily_gains(prices), k)

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
        prices = test['prices']
        k = test['k']
        expected = test['expected']
        result = s.maxProfit(k, prices)
        if result == expected:
            print("Test %s succeeded!" % test)
        else:
            print("Test %s failed: returned %s!" % (test, result))
            failures += 1

    if failures > 0:
        print("%d tests failed over a total of %d tests" % (failures, len(tests)))
    else:
        print("All %d tests passed" % len(tests))
