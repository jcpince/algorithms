extern crate json;

use std::collections::HashMap;
use std::collections::HashSet;
use std::mem;

use algo_tools;

struct Solution;

impl Solution {
	pub fn ladder_length(begin_word: String, end_word: String, word_list: Vec<String>) -> i32 {
		let mut depth : i32 = 0;
		let base_len = begin_word.len();
		if base_len != end_word.len() {
			return depth
		}
		let mut s: HashSet<&String> = word_list.iter().collect();
		if !s.contains(&end_word) {
			return depth;
		}

		let mut directed_neighbors: HashMap<&String, Vec<&String>> = HashMap::new();
		let mut towards_end = true;
		let (mut tovisit, mut tovisit_otherdir) = (HashSet::new(), HashSet::new());
		let mut next_tovisit : HashSet<&String> = HashSet::new();

		tovisit.insert(&begin_word);
		tovisit_otherdir.insert(&end_word);

		while !tovisit.is_empty() && !tovisit_otherdir.is_empty() {
			if tovisit.len() > tovisit_otherdir.len() {
				// Always visit in the direction with the least nodes to visit
				mem::swap(&mut tovisit, &mut tovisit_otherdir);
				towards_end = !towards_end;
			}

			for w in tovisit.iter() {
				s.remove(w);
			}

			for w in tovisit.iter() {
				for idx in 0..base_len {
					let mut neighborb = (*w).clone().into_bytes();
					for i in 0..26 {
						let c = b'a' + i;
						neighborb[idx] = c;
						let key = s.get(&String::from_utf8_lossy(&neighborb).to_string());
						if let Some(neighbor) = key {
							next_tovisit.insert(neighbor);
							if towards_end {
								directed_neighbors.entry(neighbor).or_insert(Vec::new()).push(w);
							}
							else {
								directed_neighbors.entry(w).or_insert(Vec::new()).push(neighbor);
							}
						}
					}
				}
			}
			tovisit.clear();
			mem::swap(&mut tovisit, &mut next_tovisit);

			if ! tovisit_otherdir.is_disjoint(&tovisit) {
				return depth + 2;
			}
			depth += 1;
		}
		0
	}
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let begin_word = &test_case["in"]["begin_word"];
	let end_word = &test_case["in"]["end_word"];
	let dictionnary = &test_case["in"]["dictionnary"];
	let expected = test_case["expected"].as_i32().unwrap();

	let mut word_list = Vec::new();
	for word in dictionnary.members() {
		word_list.push(word.as_str().unwrap().to_string());
	}

	let result = Solution::ladder_length(begin_word.to_string(), end_word.to_string(), word_list);

	if result == expected {
		return 0;
	}

	println!("ladder_length({}, {}, {}) returned {} but expected {}\n",
		begin_word, end_word, dictionnary, result, expected);
	1
}

fn main() {
	let (tests, test_idx) = algo_tools::load_json_tests();
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
