extern crate json;

use algo_tools::load_json_tests;
use algo_tools::treenode::{TreeNode,vector2tree};
use std::rc::Rc;
use std::cell::RefCell;
use std::iter;

type Tree = Option<Rc<RefCell<TreeNode>>>;

struct Solution;

impl Solution {
	fn dfs(root: &Tree, branch_sum: i32, tree_sum: i32) -> i32 {
		let mut ts = tree_sum;
		if let Some(root) = root {
			let bs = branch_sum * 10 + root.borrow().val;
			//println!("Visiting {}, branch_sum is {}", root.borrow().val, bs);
			if root.borrow().left.is_none() && root.borrow().right.is_none() {
				// root is a leaf
				ts += bs;
			} else {
				ts = Self::dfs(&root.borrow().left, bs, ts);
				ts = Self::dfs(&root.borrow().right, bs, ts);
			}
		}
		ts
	}
	pub fn sum_numbers(root: Tree) -> i32 {
		Self::dfs(&root, 0, 0)
	}
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let _nums = &test_case["in"];
	let expected = test_case["expected"].as_i32().unwrap();

	let mut nums = Vec::new();
	for num in _nums.members() {
		nums.push(num.as_i32().unwrap());
	}
	//let mut tree : Vec<Rc<RefCell<TreeNode>>> = vec!(Rc::new(RefCell::new(TreeNode::new(0))); nums.len());
	let mut tree: Vec<_> = iter::repeat_with(|| Rc::new(RefCell::new(TreeNode::new(0))))
		.take(nums.len())
		.collect();

	let root = vector2tree(&nums, &mut tree);

	let result = Solution::sum_numbers(root);

	if result == expected {
		return 0;
	}

	println!("sum_numbers({:?}) returned {} but expected {}\n",
		tree[0], result, expected);
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

/*impl Solution {
    pub fn sum_numbers(root: Tree) -> i32 {
        fn traverse(root: &Tree, sum: i32) -> i32 {
            root.as_ref().map(|node| {
                let node = node.borrow();
                let next = sum * 10 + node.val;
                if node.left.is_none() & node.right.is_none() {
                    return next;
                }
                traverse(&node.left, next) + traverse(&node.right, next)
            }).unwrap_or(0)
        }
        traverse(&root, 0)
    }
}*/
