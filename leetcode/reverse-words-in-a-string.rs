extern crate json;

use algo_tools::load_json_tests;

struct Solution;

impl Solution {
    /*fn reverse_sentence(s : &mut [u8]) {
		let len = s.len();
        for i in 0..len/2 {
            let tmp = s[i];
            s[i] = s[len - i - 1];
            s[len - i - 1] = tmp;
        }
    }

	fn reverse_word(s : &mut [u8], _start_idx : usize, _end_idx : usize, dest_idx : usize) {
		let len = _end_idx - _start_idx;
		let mut start_idx = _start_idx;
		let mut end_idx = _end_idx;
		if start_idx != dest_idx {
			// different dest, reverse while moving until start is reached
			let mut i = 0;
			while i < len && dest_idx + i < start_idx {
				s[dest_idx + i] = s[end_idx - i - 1];
				i += 1;
			}
			// now, swap what remains
			start_idx = dest_idx + i;
			end_idx = end_idx - i;
		}
		// simply swap the bytes
        Solution::reverse_sentence(& mut s[start_idx..end_idx]);
    }

    unsafe fn reverse_words_o1s(sentence : &mut [u8]) -> usize {
        // Revert all the letters
        Solution::reverse_sentence(sentence);
        // Revert again the letter in each word
		let len = sentence.len();
		let mut start_idx = 0;
		let mut end_idx;
		let mut dest_idx = 0;
        while start_idx < len {
			while start_idx < len && sentence[start_idx] == b' ' {
				start_idx += 1;
			}
			if start_idx == len	{
				break;
			}
			end_idx = start_idx + 1;
			while end_idx < len && sentence[end_idx] != b' ' {
				end_idx += 1;
			}
			Solution::reverse_word(sentence, start_idx, end_idx, dest_idx);
			dest_idx += end_idx - start_idx + 1;
			if dest_idx < len {
				sentence[dest_idx - 1] = b' ';
			}
			start_idx = end_idx + 1;
		}
		dest_idx-1
    }

    pub fn reverse_words(_s: String) -> String {
		let new_size;
        let mut s = _s.clone();
		unsafe {
        	new_size = Solution::reverse_words_o1s(s.as_bytes_mut());
		}
		s[..new_size].to_string()
    }*/

    pub fn reverse_words_fast(s: String) -> String {
		if s.len() < 2 {
			return s;
		}
        let mut reversed = String::new();
		reversed.reserve(s.len());
		let mut start_idx;
		let mut end_idx = s.len();
		let sarray = s.as_bytes();
		loop {
			// seek end of word
			while end_idx > 0 && sarray[end_idx - 1] == b' ' {
				end_idx -= 1;
			}
			if end_idx == 0 {
				break;
			}
			// seek start of word
			start_idx = end_idx - 1;
			while start_idx > 0 && sarray[start_idx - 1] != b' ' {
				start_idx -= 1;
			}
			if reversed.len() > 0 {
				reversed.push(' ');
			}
			// println!("append \"{}\" to \"{}\"", std::str::from_utf8(&sarray[start_idx..end_idx]).unwrap(), reversed);
			reversed.push_str(std::str::from_utf8(&sarray[start_idx..end_idx]).unwrap());
			end_idx = start_idx;
		}
		reversed
    }
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let i = test_case["in"].as_str().unwrap().to_string();
	let expected = test_case["expected"].as_str().unwrap();

	let result = Solution::reverse_words_fast(i.clone());

	if result == expected {
		return 0;
	}

	println!("reverse_words({:?}) returned {:?} but expected {:?}\n",
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