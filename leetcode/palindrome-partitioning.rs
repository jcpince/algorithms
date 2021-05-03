/*
131. Palindrome Partitioning
Medium

Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

A palindrome string is a string that reads the same backward as forward.

Example 1:
Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Example 2:
Input: s = "a"
Output: [["a"]]

Constraints:
	1 <= s.length <= 16
	s contains only lowercase English letters.
*/
extern crate json;

use algo_tools::load_json_tests;

struct Solution;

impl Solution {
	fn comb_rec(all_pals : &[Vec<&str>], slen : usize, base : &mut Vec<Vec<String>>) {

		assert!(base.len() == 1);
		if all_pals[0].len() == 1 {
			base[0].push(all_pals[0][0].to_string());
			let plen = all_pals[0][0].len();
			if plen < slen {
				Self::comb_rec(&all_pals[plen..], slen - plen, base);
			}
		} else {
			for pal in all_pals[0].iter() {
				let mut new_base = vec!(base[0].clone(); 1);
				new_base[0].push(pal.to_string());
				if pal.len() < slen {
					Self::comb_rec(&all_pals[pal.len()..], slen - pal.len(), &mut new_base);
				}
				base.append(&mut new_base);
			}
			base.remove(0);
		}
	}
	fn combine_all_palindromes(all_pals : &Vec<Vec<&str>>, slen : usize) -> Vec<Vec<String>> {

		// pals are the palindromes starting at index idx, they need to be combined with all the
		// palindromes further in the string
		let mut res: Vec<Vec<String>> = Vec::new();
		for pal in all_pals[0].iter() {
			//println!("pal: {:?}", pal);
			let mut subres = vec!(vec!(String::from(*pal); 1); 1);
			if pal.len() < slen {
				Self::comb_rec(&all_pals[pal.len()..], slen - pal.len(), &mut subres);
			}
			res.append(&mut subres);
		}
		res
	}

	fn find_all_palindromes(s: &String)  -> Vec<Vec<String>> {

		// searches the string for all palindromes
		let mut all_pals : Vec<Vec<&str>> = Vec::new();
		for _ in 0..s.len() {
			all_pals.push(Vec::new());
		}
		all_pals[0].push(&s[0..1]);

		for index in 1..s.len() {
			all_pals[index].push(&s[index..index+1]);
			let mut off : usize = 0;
			let (mut check_odd, mut check_even) = (true, true);
			while index > off && index + off < s.len() && (check_odd || check_even) {
				let l = index - off - 1;
				let r = index + off + 1;
				if check_odd && r < s.len() {
					if s.chars().nth(l) == s.chars().nth(r) {
						all_pals[l].push(&s[l..r+1]);
					} else { check_odd = false; }
				}
				if check_even {
					if s.chars().nth(l) == s.chars().nth(r-1) {
						all_pals[l].push(&s[l..r]);
					} else { check_even = false; }
				}
				off += 1
			}
		}

		//println!("all_palindromes {:?}\n\n", all_pals);
		Self::combine_all_palindromes(&all_pals, s.len())
	}

	fn _print_all_palindromes(s: &String) {
		// searches the string for all palindromes
		println!("Check1 s[0] = {} : palindrome!", s.chars().nth(0).unwrap());
		for index in 1..s.len() {
			println!("Check1 s[{}] = {} : palindrome!", index, s.chars().nth(index).unwrap());
			println!("Index {}", index);
			let mut off : usize = 0;
			let (mut check_odd, mut check_even) = (true, true);
			while index > off && index + off < s.len() && (check_odd || check_even) {
				let l = index - off - 1;
				let r = index + off + 1;
				if check_odd && r < s.len() {
					if s.chars().nth(l) == s.chars().nth(r) {
						println!("Check1 s[{}..{}] = {} : palindrome!", l, r, s[l..r+1].to_string());
					} else { check_odd = false; }
				}
				if check_even {
					if s.chars().nth(l) == s.chars().nth(r-1) {
						println!("Check2 s[{}..{}] = {} : palindrome!", l, r-1, s[l..r].to_string());
					} else { check_even = false; }
				}
				off += 1
			}
		}
	}

	pub fn partition(s: String) -> Vec<Vec<String>> {
		//Self::_print_all_palindromes(&s);
		Self::find_all_palindromes(&s)
	}
}

fn compare_unordered(res : &Vec<Vec<String>>, exp : &Vec<Vec<String>>) -> bool {
	if res.len() != exp.len() { return false; }
	let mut comp = vec!(0; res.len());
	for s in res.iter() {
		for (idx, e) in exp.iter().enumerate() {
			if comp[idx] == 0 && e == s {
				comp[idx] = 1;
				break;
			}
		}
	}
	comp.iter().sum::<usize>() == res.len()
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let s = &test_case["in"];
	let _expected = &test_case["expected"];

	let mut expected = Vec::new();
	for _seq in _expected.members() {
		let mut seq = Vec::new();
		for w in _seq.members() {
			seq.push(w.to_string());
		}
		expected.push(seq);
	}

	let result = Solution::partition(s.to_string());

	if compare_unordered(&result, &expected) {
		return 0;
	}

	println!("partition({:}) returned {:?} but expected {:?}\n",
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
