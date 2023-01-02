extern crate json;

use algo_tools::load_json_tests;

struct Solution;

impl Solution {

    pub fn maximum_gap(mut nums: Vec<i32>) -> i32 {
        if nums.len() < 2 {
            return 0;
        }
        nums.sort();
        let mut n0 = nums[0];
        let mut res = 0;
        for n in nums[1..].iter() {
            res = res.max(n - n0);
            n0 = *n;
        }
        res
    }
    pub fn _maximum_gap(nums: Vec<i32>) -> i32 {
        // println!("\n\nmaximum_gap({:?})", nums);
        if nums.len() < 2 {
            return 0;
        }
        let (min, max) = nums.iter()
            .skip(1)
            .fold((nums[0], nums[0]), |(min, max), val| {
                (min.min(*val), max.max(*val))
            });
        // println!("min {}, max {}", min, max);
        let num_buckets = (max - min) as usize / nums.len() + 1;
        let mut buckets: Vec<Option<[i32; 2]>> = vec![None; nums.len()];
        for num in &nums {
            let bucket = (*num - min) as usize / num_buckets;
            buckets[bucket] = Some(match buckets[bucket] {
                None => [*num, *num],
                Some(a) => [a[0].min(*num), a[1].max(*num)],
            });
        }
        // println!("buckets {:?}", buckets);
        let mut max_diff = 0;
        let vals: Vec<i32> = buckets.into_iter().filter_map(|o| o).flatten().collect();

        // println!("vals {:?}", vals);
        for i in 1..vals.len() {
            max_diff = max_diff.max(vals[i] - vals[i - 1]);
        }
        // println!("returns {}", max_diff);
        max_diff
    }
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let _i = &test_case["in"];
	let expected = test_case["expected"].as_i32().unwrap();
    let mut i = Vec::new();

	for jop in _i.members() {
        i.push(jop.as_i32().unwrap());
	}

    for _ in 0..10000 {
        let result = Solution::maximum_gap(i.clone());
        if result != expected {
            println!("maximum_gap({:?}) returned {:?} but expected {:?}\n",
		        i, result, expected);
            return 1;
        }
        //println!("maximum_gap({:?}) succeeded", i);
    }
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
