extern crate json;

use algo_tools;

struct Solution;

impl Solution {
    pub fn longest_consecutive(mut nums: Vec<i32>) -> i32 {
        if nums.len() < 2 { return nums.len() as i32; }
        nums.sort_unstable();
        let (mut longest, mut cur_len, mut n0) = (1, 0, nums[0] - 1);
        for n in nums.iter() {
            if n0 + cur_len != *n {
                if n0 + 1 + cur_len == *n {
                    cur_len += 1;
                    if cur_len > longest {
                        longest = cur_len;
                    }
                } else { cur_len = 1; n0 = *n-1; }
            }
        }
        longest
    }
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let _nums = &test_case["in"];
	let expected = test_case["expected"].as_i32().unwrap();

	let mut nums = Vec::new();
	for num in _nums.members() {
		nums.push(num.as_i32().unwrap());
	}

	let result = Solution::longest_consecutive(nums);

	if result == expected {
		return 0;
	}

	println!("longest_consecutive({:?}) returned {} but expected {}\n",
		_nums, result, expected);
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
