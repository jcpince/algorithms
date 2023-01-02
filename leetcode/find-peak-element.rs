extern crate json;

use algo_tools::load_json_tests;

struct Solution;

impl Solution {
    pub fn find_peak_element(nums: Vec<i32>) -> i32 {
        let len = nums.len();
        let mut left : usize = 0;
        let mut right : usize = len - 1;

        if (len < 2) || (nums[0] > nums[1]) {
            return 0;
        }
        if nums[right] > nums[right - 1] {
            return right as i32;
        }

        while left < right {
            let middle : usize = left + (right - left) / 2;
            if (middle > 0) && (nums[middle] <= nums[middle - 1]) {
                right = middle - 1;
            } else if (middle < (len - 1)) && (nums[middle] <= nums[middle + 1]) {
                //assert!(left != middle);
                left = middle + 1;
            } else {
                return middle as i32;
            }
        }
        left as i32
    }
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let _i = &test_case["in"];
	let expected = test_case["expected"].as_i32().unwrap();
    let mut i = Vec::new();

	for jop in _i.members() {
        i.push(jop.as_i32().unwrap());
	}

	let result = Solution::find_peak_element(i.clone());

	if result == expected {
		return 0;
	}

	println!("find_peak_element({:?}) returned {:?} but expected {:?}\n",
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
