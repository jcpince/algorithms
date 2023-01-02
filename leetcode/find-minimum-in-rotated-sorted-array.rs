extern crate json;

use algo_tools::load_json_tests;

struct Solution;

impl Solution {
    pub fn find_min(nums: Vec<i32>) -> i32 {
        let len = nums.len();
        if len < 2 {
            return nums[0];
        }
        let mut left = 0;
        let mut right = len - 1;
        let mut idx = right / 2;
        let mut idx_1 = usize::min(idx.wrapping_sub(1), len - 1);
        while nums[idx] > nums[idx_1] {
            if nums[left] < nums[right] {
				// non rotated segment, returns nums[left]
				return nums[left];
            }
            else {
				// segment rotated, goes left iff
				// nums[left] > nums[idx] && nums[idx_1] < nums[idx]
				// nums[idx_1] < nums[idx] is already checked in the while loop...
				if nums[left] > nums[idx] {
					right = idx;
				} else {
					left = idx;
				}
            }
            idx = usize::min(left + usize::min(right - left, 2) / 2, len - 1);
            idx_1 = usize::min(idx.wrapping_sub(1), len - 1);
			if left + 1 == right && nums[right] < nums[idx] {
				return nums[right];
			}
            // println!("left {}, idx {}, right {}", left, idx, right);
        }
        // println!("returns {}", nums[idx]);
        nums[idx]
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
