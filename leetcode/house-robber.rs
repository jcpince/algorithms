extern crate json;

use algo_tools::load_json_tests;

struct Solution;

impl Solution {
    // fn rob_recursive(nums: & Vec<i32>, idx : usize, stash : i32) -> i32 {
    //     if idx >= nums.len() {
    //         return stash;
    //     } else if idx + 1 >= nums.len() {
    //         return nums[idx] + stash;
    //     }
    //     std::cmp::max(Solution::rob_recursive(nums, idx+1, stash),
    //         Solution::rob_recursive(nums, idx+2, nums[idx] + stash))
    // }
    pub fn rob(nums: Vec<i32>) -> i32 {
		if nums.len() < 3 {
			if nums.len() == 0 {
				return 0;
			}
			if nums.len() == 1 {
				return nums[0];
			}
			// 2
			if nums[0] > nums[1] {
				return nums[0];
			}
			return nums[1];
		}
        // Solution::rob_recursive(&nums, 0, 0)
		let mut res : i32 = 0;
		let mut skip : bool = false;
		for idx in 0 .. nums.len() - 2 {
			if skip { skip = false; continue; }
			let next : i32 = nums[idx+1];
			let nnext : i32 = nums[idx+2];
			if (nums[idx] + nnext) > next {
				res += nums[idx];
				skip = true;
			}
		}
		if skip || (nums[nums.len()-1] > nums[nums.len()-2]) {
			res += nums[nums.len()-1];
		} else {
			res += nums[nums.len()-2];
		}
		res
    }
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let _i = &test_case["in"];
	let expected = test_case["expected"].as_i32().unwrap();
    let mut nums = Vec::new();

	for jop in _i.members() {
        nums.push(jop.as_i32().unwrap());
	}

    let result = Solution::rob(nums.clone());
    if result != expected {
        println!("rob({:?}) returned {:?} but expected {:?}\n",
            nums, result, expected);
        return 1;
    }
    println!("rob({:?}) succeeded", nums);
    0
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
