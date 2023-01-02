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
    def maximumGap(self, nums: List[int]) -> int:
        if len(nums) < 2:
            return 0
        nums.sort()
        n0 = nums[0]
        res = 0
        for num in nums:
            res = max(res, num - n0)
            n0 = num
        return res

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
				type=argparse.FileType('r'))
	parser.add_argument("-i", "--test-index", help="index of the test to run",
				type=int, default=-1)
	args = parser.parse_args()
	spec = json.load(args.json_file)
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
		result = s.maximumGap(ind)
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
