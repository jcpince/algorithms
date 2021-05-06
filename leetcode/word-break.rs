/*
135. Candy
Hard

Share
There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.


Example 1:
Input: ratings = [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

Example 2:
Input: ratings = [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
The third child gets 1 candy because it satisfies the above two conditions.

Constraints:

n == ratings.length
1 <= n <= 2 * 104
0 <= ratings[i] <= 2 * 104
*/
extern crate json;

use algo_tools::load_json_tests;

struct Solution;

/*
struct _Solution;
use std::collections::HashSet;

impl _Solution {
    fn can_compose(s : &str, s0: &str, dictionnary: &HashSet<&str>) -> bool {
        if s != s0 {
            if dictionnary.contains(s) { return true; }
        }
        for l in 1..s.len() {
            if dictionnary.contains(&s[..l]) && Self::can_compose(&s[l..], s0, dictionnary) {
                return true;
            }
        }
        return false;
    }
    fn filters_dictionnary<'a>(dictionnary: &'a HashSet<&'a str>) -> HashSet<&'a str> {
        let mut filtered = HashSet::new();
        for word in dictionnary.iter() {
            if ! Self::can_compose(word, word, dictionnary) {
                filtered.insert(*word);
            }
        }
        filtered
    }
    fn is_breakable(s : &str, dictionnary: &HashSet<&str>) -> bool {

        //println!("Check {}", s);
        if dictionnary.contains(s) { return true; }
        for l in 0..s.len() {
            if dictionnary.contains(&s[..l]) && Self::is_breakable(&s[l..], dictionnary) {
                return true;
            }
        }
        return false;
    }
    pub fn word_break(s: String, word_dict: Vec<String>) -> bool {
        let dictionnary: HashSet<&str> = word_dict.iter().map(|word| &word[..]).collect();
        //println!("Original dictionnary {:?}:", &dictionnary);
        let dictionnary = Self::filters_dictionnary(&dictionnary);
        //println!("filtered_dictionnary: {:?}", dictionnary);
        Self::is_breakable(&s, &dictionnary)
    }
}*/

impl Solution {
    pub fn word_break(s: String, word_dict: Vec<String>) -> bool {
        let n = s.len();
        // dp[i+1] is true if the word s can be breaked up to index i
        let mut dp = vec![false; n+1];
        dp[0] = true;
        for i in 1..n+1 {
            for w in word_dict.iter() {
                let wlen = w.len();
                // dp[i] is true if there is a word in the dictionnary if len wlen matching the
                // slice[i-wlen..i] and if dp[i-wlen] is true as well
                if wlen <= i && s[(i-wlen)..i] == w[..] && dp[i-wlen] {
                    dp[i] = true;
                    break;
                }
            }
        }
        *dp.last().unwrap()
    }
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let s : String = test_case["in"]["s"].to_string();
    let word_dict : Vec<String> = test_case["in"]["word_dict"].members().map(|w| w.to_string()).collect();
	let expected = test_case["expected"].as_bool().unwrap();

	let result = Solution::word_break(s, word_dict.to_vec());

	if result == expected {
		return 0;
	}

	println!("word_break({:?}) returned {} but expected {}\n",
		word_dict, result, expected);
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
