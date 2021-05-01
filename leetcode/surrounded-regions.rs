/* 130. Surrounded Regions
Medium

Given an m x n matrix board containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.



Example 1:

Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
Explanation: Surrounded regions should not be on the border, which means that any 'O' on the border of the board are not flipped to 'X'. Any 'O' that is not on the border and it is not connected to an 'O' on the border will be flipped to 'X'. Two cells are connected if they are adjacent cells connected horizontally or vertically.

Example 2:

Input: board = [["X"]]
Output: [["X"]]



Constraints:

	m == board.length
	n == board[i].length
	1 <= m, n <= 200
	board[i][j] is 'X' or 'O'.
*/
extern crate json;

use algo_tools::load_json_tests;

struct Solution;

impl Solution {
	fn explore(board: &mut Vec<Vec<char>>, i : usize, j : usize, m : usize, n : usize) {
		//println!("Exploring board[{}][{}]", i, j);
		board[i][j] = 'M';

		if i+1 < m && board[i+1][j] == 'O' {
			Self::explore(board, i+1, j, m, n);
		}
		if j+1 < n && board[i][j+1] == 'O' {
			Self::explore(board, i, j+1, m, n);
		}
		if i > 0 && board[i-1][j] == 'O' {
			Self::explore(board, i-1, j, m, n);
		}
		if j > 0 && board[i][j-1] == 'O' {
			Self::explore(board, i, j-1, m, n);
		}
	}
	pub fn solve(board: &mut Vec<Vec<char>>) {
		let m = board.len();
		let n = board[0].len();
		for i in 0..m {
			if board[i][0] == 'O' {
				Self::explore(board, i, 0, m, n);
			}
			if board[i][n-1] == 'O' {
				Self::explore(board, i, n-1, m, n);
			}
		}
		for j in 0..n {
			if board[0][j] == 'O' {
				Self::explore(board, 0, j, m, n);
			}
			if board[m-1][j] == 'O' {
				Self::explore(board, m-1, j, m, n);
			}
		}

		// now, transform all the M in O and the O in X
		for i in 0..m {
			for j in 0..n {
				match board[i][j] {
					'M' => board[i][j] = 'O',
					'O' => board[i][j] = 'X',
					_ => (),
				}
			}
		}
	}
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let _board = &test_case["in"];
	let _expected = &test_case["expected"];

	let mut board = Vec::new();
	for _line in _board.members() {
		let mut line = Vec::new();
		for _box in _line.members() {
			let v : char = _box.as_str().unwrap().chars().nth(0).unwrap();
			line.push(v);
		}
		board.push(line);
	}
	let board0 = board.clone();

	let mut expected = Vec::new();
	for _line in _expected.members() {
		let mut line = Vec::new();
		for _box in _line.members() {
			let v : char = _box.as_str().unwrap().chars().nth(0).unwrap();
			line.push(v);
		}
		expected.push(line);
	}

	Solution::solve(&mut board);

	if board == expected {
		return 0;
	}

	println!("solve({:?}) returned {:?} but expected {:?}\n",
		board0, board, expected);
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
