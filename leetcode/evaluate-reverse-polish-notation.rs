extern crate json;

use algo_tools::load_json_tests;

struct Solution;

// impl Solution {
//     pub fn eval_rpn(tokens: Vec<String>) -> i32 {
//         let mut numbers = Vec::new();
//         let mut res = tokens[0].parse::<i32>().unwrap();
//         for token in tokens[1..].iter() {
//             match token.as_str() {
//                 "+" => res += numbers.pop().unwrap(); break,
//                 "-" => res -= numbers.pop().unwrap(),
//                 "*" => res *= numbers.pop().unwrap(),
//                 "/" => res /= numbers.pop().unwrap(),
//                 _ => numbers.push(token.parse::<i32>().unwrap()),
//             };
//         res
//     }
// }

// impl Solution {
//     pub fn eval_rpn(tokens: Vec<String>) -> i32 {
//         let mut numbers = Vec::new();
//         let mut res = None;
//         for token in tokens.iter() {
//             match token.as_str() {
//                 "+" =>
//                 {
//                     let num = numbers.pop().unwrap();
//                     res = match res {
//                         Some(x) => Some(num + x),
//                         None => Some(num + numbers.pop().unwrap())
//                     };
//                 },
//                 "-" =>
//                 {
//                     let num = numbers.pop().unwrap();
//                     res = match res {
//                         Some(x) => Some(num - x),
//                         None => Some(numbers.pop().unwrap() - num)
//                     };
//                 },
//                 "*" =>
//                 {
//                     let num = numbers.pop().unwrap();
//                     res = match res {
//                         Some(x) => Some(num * x),
//                         None => Some(numbers.pop().unwrap() * num)
//                     };
//                 },
//                 "/" =>
//                 {
//                     let num = numbers.pop().unwrap();
//                     res = match res {
//                         Some(x) => Some(num / x),
//                         None => Some(numbers.pop().unwrap() / num)
//                     };
//                 },
//                 _ => numbers.push(token.parse::<i32>().unwrap()),
//             };
//         }
//         res.unwrap()
//     }
// }

impl Solution {
    pub fn eval_rpn(tokens: Vec<String>) -> i32 {
        let mut numbers = Vec::new();
        for token in tokens.iter() {
            match token.as_str() {
                "+" => {
                    let num0 = numbers.pop().unwrap();
                    let num1 = numbers.pop().unwrap();
                    numbers.push(num1 + num0);
                },
                "-" => {
                    let num0 = numbers.pop().unwrap();
                    let num1 = numbers.pop().unwrap();
                    numbers.push(num1 - num0);
                },
                "*" => {
                    let num0 = numbers.pop().unwrap();
                    let num1 = numbers.pop().unwrap();
                    numbers.push(num1 * num0);
                },
                "/" => {
                    let num0 = numbers.pop().unwrap();
                    let num1 = numbers.pop().unwrap();
                    numbers.push(num1 / num0);
                },
                _ => numbers.push(token.parse::<i32>().unwrap()),
            };
        }
        numbers.pop().unwrap()
    }
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let _i = &test_case["in"];
	let expected = test_case["expected"].as_i32().unwrap();
    let mut i = Vec::new();

	for jop in _i.members() {
        i.push(jop.to_string());
	}

	let result = Solution::eval_rpn(i.clone());

	if result == expected {
		return 0;
	}

	println!("eval_rpn({:?}) returned {:?} but expected {:?}\n",
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