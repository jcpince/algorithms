/*
132. Palindrome Partitioning II
Hard

Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

Example 1:
Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

Example 2:
Input: s = "a"
Output: 0

Example 3:
Input: s = "ab"
Output: 1

Constraints:

	1 <= s.length <= 2000
	s consists of lower-case English letters only.
*/
extern crate json;

//use std::collections::HashSet;
//use std::mem;

use algo_tools::load_json_tests;

struct Solution;
/*struct _Solution0;

#[derive(Debug)]
struct Node {
	idx: usize,
	neighbors_fwd: HashSet<usize>,
	neighbors_bwd: HashSet<usize>,
}

impl Node {
	pub fn new(idx: usize) -> Node {
		Node {
			idx,
			neighbors_fwd : HashSet::new(),
			neighbors_bwd : HashSet::new()
		}
	}
}

impl _Solution0 {

	fn _min_cut_rec(all_pals : &[Vec<&str>], slen : usize) -> i32 {
		let (mut longest_idxes, mut llen) = (Vec::new(), 0);
		for (idx, pals) in all_pals.iter().enumerate() {
			for pal in pals.iter() {
				if idx + pal.len() < slen {
					if pal.len() > llen {
						llen = pal.len();
						longest_idxes.clear();
						longest_idxes.push(idx);
					} else if pal.len() == llen {
						longest_idxes.push(idx);
					}
				} else if pal.len() == slen {
					return 0;
				}
			}
		}
		println!("all_palindromes {:?}: longests {:?}/{}", all_pals, longest_idxes, llen);
		let mut res : i32 = llen as i32 + 1;
		for longest_idx in longest_idxes.iter() {
			let mut tmp : i32 = 0;
			if *longest_idx > 0 {
				tmp += 1 + Self::_min_cut_rec(&all_pals[..*longest_idx], *longest_idx);
			}
			if longest_idx + llen < slen {
				tmp += 1 + Self::_min_cut_rec(&all_pals[*longest_idx+llen..], slen - *longest_idx - llen);
			}
			if res > tmp {
				res = tmp;
			}
		}
		res
	}

	fn _find_all_palindromes(s: &String) -> i32 {

		// searches the string for all palindromes
		let mut all_pals : Vec<Vec<&str>> = Vec::new();
		for _ in 0..s.len() {
			all_pals.push(Vec::new());
		}
		all_pals[0].push(&s[0..1]);

		let bytes = s.as_bytes();
		for index in 1..s.len() {
			all_pals[index].push(&s[index..index+1]);
			let mut off : usize = 0;
			let (mut check_odd, mut check_even) = (true, true);
			while index > off && index + off < s.len() && (check_odd || check_even) {
				let l = index - off - 1;
				let r = index + off + 1;
				if check_odd && r < s.len() {
					if bytes[l] == bytes[r] {
						all_pals[l].push(&s[l..r+1]);
					} else { check_odd = false; }
				}
				if check_even {
					if bytes[l] == bytes[r-1] {
						all_pals[l].push(&s[l..r]);
					} else { check_even = false; }
				}
				off += 1
			}
		}

		//println!("all_palindromes {:?}\n\n", all_pals);
		Self::_min_cut_rec(&all_pals, s.len())
	}

	pub fn _min_cut(s: String) -> i32 {
		Self::_find_all_palindromes(&s)
	}
}
*/

impl Solution {
	/*pub fn _min_cut(s: String) -> i32 {

		// searches the string for all palindromes and build the graph from them
		// A palindrome being an arc between two nodes (each node being a letter)
		let mut nodes: Vec<Node> = (0..s.len()+1)
			.map(| idx | {
				let node = Node::new(idx);
				node
			}).collect();

		//println!("Initial graph {:?}", nodes);

		let bytes = s.as_bytes();
		for index in 0..bytes.len() {
			nodes[index].neighbors_fwd.insert(index+1);
			nodes[index+1].neighbors_bwd.insert(index);
			let mut off : usize = 0;
			let (mut check_odd, mut check_even) = (true, true);
			while index > off && index + off < s.len() && (check_odd || check_even) {
				let l = index - off - 1;
				let r = index + off + 1;
				if check_odd && r < s.len() {
					if bytes[l] == bytes[r] {
						nodes[l].neighbors_fwd.insert(r+1);
						nodes[r+1].neighbors_bwd.insert(l);
					} else { check_odd = false; }
				}
				if check_even {
					if bytes[l] == bytes[r-1] {
						nodes[l].neighbors_fwd.insert(r);
						nodes[r].neighbors_bwd.insert(l);
					} else { check_even = false; }
				}
				off += 1
			}
		}

		//println!("Final graph for {}: {:?}", s, nodes);
		if nodes[0].neighbors_fwd.contains(&bytes.len()) {
			return 0;
		}
		let mut to_visit_curdir : HashSet<usize> = nodes[0].neighbors_fwd.clone();
		let mut to_visit_otherdir : HashSet<usize> = nodes[bytes.len()].neighbors_bwd.clone();
		let mut to_visit_next : HashSet<usize> = HashSet::new();
		let mut cuts = 1;
		let mut pick_fwd : bool = true;
		while to_visit_curdir.is_disjoint(&to_visit_otherdir) {
			if to_visit_curdir.len() > to_visit_otherdir.len() {
				//println!("swapping to_visit_curdir and to_visit_otherdir");
				mem::swap(&mut to_visit_curdir, &mut to_visit_otherdir);
				pick_fwd = !pick_fwd;
			}
			//println!("to_visit_curdir {:?}, to_visit_otherdir {:?}", to_visit_curdir, to_visit_otherdir);
			for neighbor_idx in to_visit_curdir.iter() {
				if pick_fwd {
					to_visit_next.extend(&nodes[*neighbor_idx].neighbors_fwd);
				} else {
					to_visit_next.extend(&nodes[*neighbor_idx].neighbors_bwd);
				}
			}
			to_visit_curdir.clear();
			mem::swap(&mut to_visit_curdir, &mut to_visit_next);
			cuts += 1;
		}
		cuts
	}*/
	pub fn min_cut(s: String) -> i32 {
		if s.len() < 2 { return 0; }

		let bytes = s.as_bytes();
		let slen = s.len();
		let mut min_cuts : Vec<usize> = (0..slen+1).map(|i| i).collect();
		for index in 1..slen {
			let mut off : usize = 0;
			let (mut check_odd, mut check_even) = (true, true);
			while index > off && index + off < slen && (check_odd || check_even) {
				let l = index - off - 1;
				let r = index + off + 1;
				if check_odd && r < slen {
					if bytes[l] == bytes[r] {
						if r - l + 1 == slen { return 0; }
						min_cuts[r+1] = min_cuts[r+1].min(min_cuts[l]+1);
					} else { check_odd = false; }
				}
				if check_even {
					if bytes[l] == bytes[r-1] {
						if r - l == slen { return 0; }
						min_cuts[r] = min_cuts[r].min(min_cuts[l]+1);
					} else { check_even = false; }
				}
				off += 1
			}
		}
		println!("min_cuts: {:?}", min_cuts);
		min_cuts[bytes.len()] as i32
	}
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let s = &test_case["in"];
	let expected = test_case["expected"].as_i32().unwrap();

	let result = Solution::min_cut(s.to_string());

	/*for _ in 0..100 {
		Solution::min_cut(s.to_string());
	}*/

	if result == expected {
		return 0;
	}

	println!("min_cut({:}) returned {:?} but expected {:?}\n",
		s, result, expected);
	1
}

fn main() {
	let (tests, test_idx) = load_json_tests();
	let (mut successes, mut failures) = (0, 0);
	if test_idx >= tests.len() as i32 {
		println!("Wrong index {}, only {} tests available!!", test_idx, tests.len());
		return
	}
	if test_idx != -1 {
		let rc = run_test_case(&tests[test_idx as usize]);
		if rc == 0 { successes += 1; }
		else { failures += 1; }
	} else {
		println!("{} tests specified", tests.len());
		for i in 0..tests.len() {
			let rc = run_test_case(&tests[i]);
			if rc == 0 { successes += 1; }
			else { failures += 1; }
		}
	}

	if failures > 0 {
		println!("{} tests succeeded and {} tests failed!!", successes, failures);
	} else {
		println!("All {} tests succeeded!!", successes);
	}
}
