extern crate json;

use algo_tools::load_json_tests;

struct Solution;

impl Solution {
    pub fn find_min(nums: Vec<i32>) -> i32 {
        let mut left : usize = 0;
        let mut right : usize = nums.len() - 1;

        while left < right {
            let middle : usize = left + (right - left) / 2;
            if nums[left] < nums[right] {
                // the whole span is increasing
                break;
            } else if nums[middle] < nums[right] {
                // the right side is bigger, scan the left side
                right = middle
            } else if nums[middle] > nums[right] {
                // right side is smaller, scan it
                left = middle + 1
            } else {
                // right side is equal, simply reduce it
                right -= 1
            }
        }
        nums[left]
    }
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let _i = &test_case["in"];
	let expected = test_case["expected"].as_i32().unwrap();
    let mut i = Vec::new();

	for jop in _i.members() {
        i.push(jop.as_i32().unwrap());
	}

	let result = Solution::find_min(i.clone());

	if result == expected {
		return 0;
	}

	println!("find_min({:?}) returned {:?} but expected {:?}\n",
		i, result, expected);
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
