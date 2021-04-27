// Definition for a binary tree node.
use std::mem;
use std::rc::Rc;
use std::cell::RefCell;
use std::collections::VecDeque;

#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode {
	pub val: i32,
	pub left: Option<Rc<RefCell<TreeNode>>>,
	pub right: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
	#[inline]
	pub fn new(val: i32) -> Self {
		TreeNode {
			val,
			left: None,
			right: None
		}
	}
}

pub fn vector2tree(v: &Vec<i32>, tree: &mut Vec<Rc<RefCell<TreeNode>>>) -> Option<Rc<RefCell<TreeNode>>> {
	//println!("tree[0] is {:?}\n", tree[0]);
	if v.len() < 1 { return None; }
	let mut idx : usize = 0;
	let mut node : Rc<RefCell<TreeNode>> = Rc::clone(&tree[idx]);
	node.borrow_mut().val = v[idx];
	idx += 1;

	let mut vnodes : VecDeque<Rc<RefCell<TreeNode>>> = VecDeque::new();
	vnodes.push_back(node);

	while idx < v.len()  {
		node = vnodes.pop_front().unwrap();
		if v[idx] != -1 {
			tree[idx].borrow_mut().val = v[idx];
			node.borrow_mut().left = Some(Rc::clone(&tree[idx]));
			vnodes.push_back(Rc::clone(&tree[idx]));
			//println!("node.val({}) has a left child with value {}", node.borrow().val, tree[idx].borrow().val);
		} //else { println!("node.val({}) has no left child", node.borrow().val); }
		idx += 1;
		if idx < v.len() && v[idx] != -1 {
			tree[idx].borrow_mut().val = v[idx];
			node.borrow_mut().right = Some(Rc::clone(&tree[idx]));
			vnodes.push_back(Rc::clone(&tree[idx]));
			//println!("node.val({}) has a right child with value {}", node.borrow().val, tree[idx].borrow().val);
		} //else { println!("node.val({}) has no right child", node.borrow().val); }
		idx += 1;
	}
	Some(tree[0].clone())
}

pub fn tree2vector(root : Rc<RefCell<TreeNode>>, v: &mut Vec<i32>) {

	let mut layer : Vec<Option<Rc<RefCell<TreeNode>>>> = Vec::new();
	let mut nextlayer : Vec<Option<Rc<RefCell<TreeNode>>>> = Vec::new();
	layer.push(Some(root));
	let (mut nodecount, mut next_nodecount) = (0, 0);

	while ! layer.is_empty()  {
		let node = layer.pop().unwrap();

		if node.is_none() {
				if nodecount > 0 || next_nodecount != 0 {
						v.push(-1);
				}
		}
		else {
				let n = node.unwrap();
				v.push(n.borrow().val);
				if !n.borrow_mut().left.is_none() { next_nodecount += 1; }
				if !n.borrow_mut().right.is_none() { next_nodecount += 1; }
				nextlayer.push(n.borrow().left.clone());
				nextlayer.push(n.borrow().right.clone());
				nodecount -= 1;
		}

		if layer.is_empty() {
				/* swap the queues */
				mem::swap(&mut layer, &mut nextlayer);
				if next_nodecount > 0 {
					nodecount = next_nodecount;
				}
				next_nodecount = 0;
		}
	}
}
