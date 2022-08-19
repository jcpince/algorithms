extern crate json;

use algo_tools::load_json_tests;

struct Solution;

struct SolutionHelper {
    res : i32,
    current : i32,
    prod_neg : i32,
    idx : usize,
    first_neg_idx : usize,
}

impl SolutionHelper {
    pub fn new() -> SolutionHelper {
        SolutionHelper {
            res : 0,
            current : 0,
            prod_neg : 1,
            idx : 0,
            first_neg_idx : 0
        }
    }

    fn seek_next_nonzero(self : & mut SolutionHelper, nums : & Vec<i32>) {
        while self.idx < nums.len() {
            self.current = nums[self.idx];
            self.idx += 1;
            if self.current == 0 {
                continue;
            }
            if self.current < 0 {
                self.first_neg_idx = self.idx - 1;
                self.prod_neg = self.current;
            }
            break;
        }
    }

    fn update_current_max_prod(self : & mut SolutionHelper) {
        if self.current < 0 && self.idx != (self.first_neg_idx + 1) {
            self.current /= self.prod_neg;
        }
    }

    pub fn max_product(self : & mut SolutionHelper, nums : Vec<i32>) -> i32 {
        if nums.len() < 2 {
            return nums[0];
        }
        // seek the first non zero number
        self.seek_next_nonzero(&nums);
        self.res = i32::max(self.current, self.res);

        while self.idx < nums.len() {
            if nums[self.idx] == 0 {
                if self.res < 0 {
                    self.res = 0;
                }
                self.update_current_max_prod();
                self.res = i32::max(self.current, self.res);

                // seek the next non zero number
                self.idx += 1;
                self.prod_neg = 1;
                self.seek_next_nonzero(&nums);
                self.res = i32::max(self.current, self.res);

                if self.current == 0 {
                    return self.res;
                }
                continue;
            }
            self.current *= nums[self.idx];
            if self.prod_neg > 0 {
                self.prod_neg = self.current;
                self.first_neg_idx = self.idx;
            }
            self.res = i32::max(self.current, self.res);
            self.idx += 1;
        }
        self.update_current_max_prod();
        i32::max(self.current, self.res)
    }
}

impl Solution {
    pub fn max_product(nums: Vec<i32>) -> i32 {
        let mut helper : SolutionHelper = SolutionHelper::new();
        helper.max_product(nums)
    }
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let _i = &test_case["in"];
	let expected = test_case["expected"].as_i32().unwrap();
    let mut i = Vec::new();

	for jop in _i.members() {
        i.push(jop.as_i32().unwrap());
	}

	let result = Solution::max_product(i.clone());

	if result == expected {
		return 0;
	}

	println!("max_product({:?}) returned {:?} but expected {:?}\n",
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
