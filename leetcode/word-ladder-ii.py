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
	def node2str(self, node):
		return "map[%s]: %d, %s, paths %s" % (node[1], node[0], [n[1] for n in node[2]], node[3])

	def nodes2str(self, nodes):
		s = "["
		for node in nodes:
			s += "%s, " % node[1]
		return s + "]"

	def map2str(self, map):
		s = ""
		for k in map.keys():
			s += "\n\t" + self.node2str(map[k])
		return s

	def dist1(self, w0, w1):
		delta = 0
		idx = 0
		for c0 in w0:
			c1 = w1[idx]
			if c0 != c1:
				delta += 1
				#print("%s vs %s delta %d at %c(vs %c)" % (w0, w1, delta, c0, c1))
				if delta > 1: return False
			idx += 1
		return True

	def findLadders(self, beginWord: str, endWord: str, wordList: List[str]) -> List[List[str]]:
		map = dict();
		found = False
		for w in wordList:
			if not found and w == endWord: found = True
			map[w] = [-1, w, [], []]
		if not found: return []
		# set the beginwork distance
		map[beginWord] = [0, beginWord, [], [[beginWord]]]
		#print("map: %s" % self.map2str(map))
		idx = 0
		allkeys = list(map.keys())
		for w0 in allkeys:
			vrtx0 = map[w0]
			idx += 1
			for w1 in allkeys[idx:]:
				if self.dist1(w0, w1):
					#print("Check %s with %s succeeded" % (w0, w1))
					vrtx1 = map[w1]
					vrtx0[2].append(vrtx1)
					vrtx1[2].append(vrtx0)
				#else: print("Check %s with %s failed" % (w0, w1))
		stack = set()
		for vertex in map[beginWord][2]:
			stack.add(vertex[1])
			vertex[3].append([beginWord, vertex[1]])
		distance = 1
		done = False
		#print("map2: %s" % self.map2str(map))
		print_debug("stack is first: %s" % stack)
		while not done and len(stack) > 0:
			next_stack = set()
			for word in stack:
				node = map[word]
				if node[0] == -1:
					print_debug("Looking for neighbors of %s" % node[1])
					for next_vertex in node[2]:
						if next_vertex[0] == -1:
							next_stack.add(next_vertex[1])
							cur_len = len(node[3][-1])
							next_len = len(next_vertex[3][-1]) if len(next_vertex[3]) > 0 else 0
							if next_len == 0 or next_len == cur_len + 1:
								print_debug("Distance %d: Adding %s's paths (%s) to %s (distance %d - %s)" %
									(distance, node[1], node[3], next_vertex[1], next_vertex[0], next_vertex[3]))
								for path in node[3]:
									p = path.copy()
									p.append(next_vertex[1])
									next_vertex[3].append(p)
							elif next_len > cur_len + 1:
								print_debug("Distance %d: Not adding %s's paths (%s) to %s (%s)" %
									(distance, node[1], node[3], next_vertex[1], next_vertex[3]))
								next_vertex[3].clear()
								for path in node[3]:
									p = path.copy()
									p.append(next_vertex[1])
									next_vertex[3].append(p)
					print_debug("next vertex is now %s" % (self.node2str(next_vertex)))
					if next_vertex[1] == endWord:
						#print("endWord %s found" % self.node2str(node))
						done = True
					node[0] = distance
			if done: break
			stack.clear()
			(stack, next_stack) = (next_stack, stack)
			print_debug("stack is done, now, it is %s" % stack)
			distance += 1
		print_debug("map3: %s" % self.map2str(map))
		print_debug("Distance from %s to %s: %d" % (beginWord, endWord, distance))
		return map[endWord][3]

	def findLadders_fast(self, beginWord: str, endWord: str, wordList: List[str]) -> List[List[str]]:
		s = set(wordList)
		if endWord not in s:
			return []

		wlen = len(beginWord)
		# directed_neighbors is the map of neighbors discovered during the
		# exploration of the map, they are in the direction end -> begin
		directed_neighbors = defaultdict(set)
		towards_end = True
		tovisit, tovisit_otherdir = set([beginWord]), set([endWord])

		while tovisit and tovisit_otherdir:
			if len(tovisit) > len(tovisit_otherdir):
				# Always visit in the direction with the least nodes to visit
				tovisit, tovisit_otherdir = tovisit_otherdir, tovisit
				towards_end = not towards_end

			# Remove the list we are visiting from the total list since any
			# path leading to an already explored node would be longer
			s -= tovisit
			next_tovisit = set()

			# Do the exploration
			for w in tovisit:
				# First, connect w to all its direct neighbors
				for idx in range(wlen):
					p0, p1 = w[:idx], w[idx+1:]
					c0 = w[idx]
					for c in string.ascii_lowercase:
						if c == c0: continue
						neighbor = p0 + c + p1
						if neighbor in s:
							next_tovisit.add(neighbor)
							if towards_end:
								directed_neighbors[neighbor].add(w)
							else:
								directed_neighbors[w].add(neighbor)
			tovisit = next_tovisit

			if tovisit_otherdir.intersection(next_tovisit):
				# found a shortest path since tovisit_otherdir and next_tovisit
				# have at least a common node
				res = [[endWord]]
				while res[0][0] != beginWord:
					# r0 = list()
					# for path in res:
					# 	for neighbor in directed_neighbors[path[0]]:
					# 		r0.append([neighbor] + path)
					# res = r0
					res = [[neighbor] + path for path in res for neighbor in directed_neighbors[path[0]]]
				return res
		return []

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
		begin_word = test['in']['begin_word']
		end_word = test['in']['end_word']
		dictionnary = test['in']['dictionnary']
		expected = test['expected']
		result = s.findLadders_fast(begin_word, end_word, dictionnary)
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
