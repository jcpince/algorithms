extern crate json;

use std::collections::HashMap;

use algo_tools::load_json_tests;

struct Solution;

impl Solution {
    fn gcd(a: i32, b: i32) -> i32 {
        match b {
            0 => a,
            _ => Solution::gcd(b, a % b)
        }
    }
    fn slope(mut dx : i32, mut dy : i32) -> (i32, i32) {
        if dx < 0 {
            dx = -dx;
            dy = -dy;
        } else if dx == 0 {
            if dy < 0 {
                dy = -dy;
            }
        }
        let gcd = Solution::gcd(dx, dy);
        (dy / gcd, dx / gcd)
    }
    pub fn max_points(points: Vec<Vec<i32>>) -> i32 {
        let l : usize = points.len();
        if l < 3 {
            return l as i32;
        }
        let mut ret = 2;
        for (idx, p0) in points[0..l-1].iter().enumerate() {
            if ret >= l - idx {
                break
            }
            let mut frequency: HashMap<(i32, i32), u32> = HashMap::new();
            for p1 in points[idx+1..l].iter() {
                let slope = Solution::slope(p0[0] - p1[0], p0[1] - p1[1]);
                *frequency.entry(slope).or_insert(1) += 1;
                ret = std::cmp::max(ret, frequency[&slope] as usize);
                // println!("p0{:?}, p1{:?} => slope {:?}", p0, p1, slope);
            }
            // println!("freq: {:?}", frequency);
        }
        ret as i32
    }
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let _i = &test_case["in"];
	let expected = test_case["expected"].as_i32().unwrap();
    let mut i = Vec::new();

	for jpoint in _i.members() {
        let mut point = Vec::new();
        for coord in jpoint.members() {
		    point.push(coord.as_i32().unwrap());
        }
        i.push(point);
	}

	let result = Solution::max_points(i.clone());

	if result == expected {
		return 0;
	}

	println!("max_points({:?}) returned {:?} but expected {:?}\n",
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