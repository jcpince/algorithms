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

use std::cell::RefCell;

use algo_tools::load_json_tests;

struct Solution;

impl Solution {
    pub fn _candy(ratings: Vec<i32>) -> i32 {
        let mut parts = ratings.clone();
        let (mut rating0, mut part0) = (ratings[0]-1, 0);

        for r in 0..ratings.len() {
            if ratings[r] < rating0 {
                //println!("ratings[{}]({}) < rating0({}) and part0 is {}", r, ratings[r], rating0, part0);
                parts[r] = 1;
                for i in (0..r).rev() {
                    if ratings[i] > ratings[i+1] && parts[i] <= parts[i+1] {
                        //println!("Add a candy to child {} to compensate", i);
                        parts[i] = parts[i+1] + 1;
                    } else { break; }
                }
            } else {
                parts[r] = 1;
                if ratings[r] > rating0 { parts[r] += part0; }
            }
            part0 = parts[r];
            rating0 = ratings[r];
        }
        parts.iter().sum()
    }
    pub fn candy(ratings: Vec<i32>) -> i32 {
        // 2 pass implementation
        let mut candies = vec![1; ratings.len()];

        for r in 1..ratings.len() {
            if ratings[r] > ratings[r-1] {
                candies[r] = candies[r-1] + 1;
            }
        }
        let mut sum = *candies.last().unwrap();
        for r in (0..ratings.len()-1).rev() {
            if ratings[r+1] < ratings[r] {
                candies[r] = candies[r].max(candies[r+1]+1);
            }
            sum += candies[r];
        }
        sum
    }
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let _ratings = &test_case["in"];
	let expected = test_case["expected"].as_i32().unwrap();

    let ratings : RefCell<Vec<i32>> = RefCell::new(_ratings.members().map(|rating| rating.as_i32().unwrap()).collect());

	let result = Solution::candy(ratings.borrow().to_vec());

	if result == expected {
		return 0;
	}

	println!("candy({:?}) returned {:?} but expected {:?}\n",
		ratings.borrow(), result, expected);
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
