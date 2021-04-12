extern crate json;

use std::collections::HashMap;

use algo_tools;

struct Solution;

impl Solution {
	pub fn find_ladders(begin_word: String, end_word: String, word_list: Vec<String>) -> Vec<Vec<String>> {
		let mut res : Vec<Vec<String>> = Vec::new();

		println!("new test (begin_word: {}, end_word: {}, word_list: {:?}",
			&begin_word, &end_word, &word_list);
		let r0 : Vec<String> = ["hello".to_string(), "hollo".to_string(), "wollo".to_string(), "worlo".to_string(), "world".to_string()].to_vec();

		res.push(r0);
		/*let mut m = HashMap::new();
		for (k, v) in word_list {
			m.entry(k).or_insert_with(Vec::new).push(v)
		}*/

		res
	}
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let begin_word = &test_case["in"]["begin_word"];
	let end_word = &test_case["in"]["end_word"];
	let dictionnary = &test_case["in"]["dictionnary"];
	let expected = &test_case["expected"];

	let mut word_list = Vec::new();
	for word in dictionnary.members() {
		word_list.push(word.as_str().unwrap().to_string());
	}

	let mut exp = Vec::new();
	for solution in expected.members() {
		let mut s = Vec::new();
		for word in solution.members() {
			s.push(word.as_str().unwrap().to_string());
		}
		exp.push(s);
	}

	let result = Solution::find_ladders(begin_word.to_string(), end_word.to_string(), word_list);

	if result == exp {
		return 0;
	}

	println!("find_ladders({}, {}, {}) returned {:?} but expected {:?}\n",
		begin_word, end_word, dictionnary, result, expected);
	1
}

fn main() {
	let (tests, test_idx) = algo_tools::load_json_tests();
	let (mut successes, mut failures) = (0, 0);
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
