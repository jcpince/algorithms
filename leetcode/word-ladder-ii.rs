extern crate json;

use std::collections::HashMap;
use std::collections::HashSet;
/*use std::cell::RefCell;
use std::fmt;*/
use std::mem;

use algo_tools;

/*struct Vertex<'a> {
	word:		String,
	distance:	RefCell<i32>,
	neighbors:	RefCell<Vec<&'a Vertex<'a>>>,
}

impl<'a> Vertex<'a> {
	pub fn new(word: &String) -> Vertex {
		Vertex {
			word : word.clone(),
			distance : RefCell::new(-1),
			neighbors : RefCell::new(Vec::new())
		}
	}
	pub fn newd(word: &String, distance: i32) -> Vertex {
		Vertex {
			word : word.clone(),
			distance: RefCell::new(distance),
			neighbors : RefCell::new(Vec::new())
		}
	}
}

impl<'a> fmt::Debug for Vertex<'a> {
	fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
		write!(f, "({}, {}, [", self.word, self.distance.borrow())?;
		for neighbor in self.neighbors.borrow().iter() {
			write!(f, "{}, ", neighbor.word) ?;
		}
		write!(f, "]")
	}
}

impl<'a> fmt::Display for Vertex<'a> {
	fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
		write!(f, "{:?}", self)
	}
}*/

struct Solution;

impl<'a> Solution {
	/*fn dist1(w0: &String, w1: &String) -> bool {
		let w0_iter = w0.chars();
		let mut w1_iter = w1.chars();
		let mut delta = 0;
		for c0 in w0_iter {
			// No risk here to unwrap because lengths are checked equal
			let c1 = w1_iter.next().unwrap();
			if c0 != c1 {
				delta += 1;
				if delta > 1 {
					return false;
				}
			}
		}
		true
	}

	fn build_map(map: &'a HashMap<&'a String, Vertex<'a>>) {

		let mut idx = 0;
		for (w0, v0) in map.iter() {
			for (w1, v1) in map.iter().skip(idx+1) {
				//println!("w0: {}, skip {} => w1 {}, v1 {:?}", &w0, idx+1, &w1, &v1);
				if Solution::dist1(w0, w1) {
					v0.neighbors.borrow_mut().push(&v1);
					v1.neighbors.borrow_mut().push(&v0);
				}
			}
			idx += 1;
		}
	}

	pub fn find_ladders_slow(begin_word: String, end_word: String, word_list: Vec<String>) ->
				Vec<Vec<String>> {

		let mut res : Vec<Vec<String>> = Vec::new();
		let base_len = begin_word.len();
		if base_len != end_word.len() {
			return res
		}

		println!("new test (begin_word: {}, end_word: {}, word_list: {:?}",
			&begin_word, &end_word, &word_list);

		let mut map: HashMap<&String, Vertex> = HashMap::new();
		let mut found = false;
		for word in &word_list {
			if base_len != word.len() {
				return res
			}
			if !found && word == &end_word { found = true; }
			map.insert(&word, Vertex::new(&word));
		}
		if !found { return res; }

		map.remove(&begin_word);
		map.insert(&begin_word, Vertex::newd(&begin_word, 0));

		println!("Unbuilt map {:#?}", &map);
		Solution::build_map(&map);
		println!("Built map {:#?}", &map);

		let mut nodes = &mut map[&begin_word].neighbors.borrow_mut().clone();
		let mut next_nodes = &mut Vec::new();
		let mut distance = 0;
		while !nodes.is_empty() {
			distance += 1;
			for node in nodes.iter() {
				println!("Check {} at distance {}", node, distance);
				// check all the nodes at this distance
				if *node.distance.borrow() == -1 {
					for next_node in node.neighbors.borrow_mut().iter() {
						next_nodes.push(*next_node);
					}
				}
				println!("Update distance to {} to {}", node, distance);
				*node.distance.borrow_mut() = distance;
			}
			nodes.clear();
			mem::swap(&mut nodes, &mut next_nodes);
			let end_distance : i32 = *map[&end_word].distance.borrow();
			if end_distance != -1 {
				break;
			}
		}
		println!("Final map {:#?}", &map);
		println!("Distance from {} to {}: {}", &begin_word, &end_word, distance);

		//let r0 : Vec<String> = ["hello".to_string(), "hollo".to_string(), "wollo".to_string(), "worlo".to_string(), "world".to_string()].to_vec();
		//res.push(r0);

		res
	}

	fn test() {
		let a: HashSet<_> = [1, 2, 3].iter().cloned().collect();
		let b: HashSet<_> = [4, 2, 3, 4].iter().cloned().collect();

		// Can be seen as `a - b`.
		for x in a.difference(&b) {
		    println!("{}", x); // Print 1
		}

		let diff: HashSet<_> = a.difference(&b).collect();
		assert_eq!(diff, [1].iter().collect());

		// Note that difference is not symmetric,
		// and `b - a` means something else:
		let diff: HashSet<_> = b.difference(&a).collect();
		assert_eq!(diff, [4].iter().collect());
	}

	pub fn find_ladders_dbg(begin_word: String, end_word: String, word_list: Vec<String>) ->
				Vec<Vec<String>> {

		let mut res : Vec<Vec<String>> = Vec::new();
		let base_len = begin_word.len();
		if base_len != end_word.len() {
			return res
		}
		let mut s: HashSet<&String> = word_list.iter().collect();
		if !s.contains(&end_word) {
			return res;
		}
		let mut idx2w: HashMap<i32, &String> = HashMap::new();
		let mut w2idx: HashMap<&String, i32> = HashMap::new();
		for (idx, w) in word_list.iter().enumerate() {
			idx2w.insert(idx as i32, w);
			w2idx.insert(&w, idx as i32);
		}
		if !s.contains(&begin_word) {
			idx2w.insert(-1, &begin_word);
			w2idx.insert(&begin_word, -1);
		}

		let mut directed_neighbors: HashMap<i32, Vec<i32>> = HashMap::new();
		let mut towards_end = true;
		let (mut tovisit, mut tovisit_otherdir) = (HashSet::new(), HashSet::new());
		tovisit.insert(w2idx[&begin_word]);
		tovisit_otherdir.insert(w2idx[&end_word]);

		println!("new test (begin_word: {}, end_word: {}, word_list: {:?}",
			&begin_word, &end_word, &word_list);
		println!("w2idx: {:?}, idx2w: {:?}", &w2idx, &idx2w);
		println!("tovisit: {:?}, tovisit_otherdir: {:?}", &tovisit, &tovisit_otherdir);

		while !tovisit.is_empty() && !tovisit_otherdir.is_empty() {
			if tovisit.len() > tovisit_otherdir.len() {
				// Always visit in the direction with the least nodes to visit
				println!("swap tovisit: {:?} and tovisit_otherdir: {:?}", &tovisit, &tovisit_otherdir);
				mem::swap(&mut tovisit, &mut tovisit_otherdir);
				println!("swapped tovisit: {:?} and tovisit_otherdir: {:?}", &tovisit, &tovisit_otherdir);
				towards_end = !towards_end;
			}

			for widx in tovisit.iter() {
				s.remove(idx2w[widx]);
			}
			println!("s - tovisit: {:?}", &s);

			let mut next_tovisit : HashSet<i32> = HashSet::new();

			for widx in tovisit.iter() {
				let w = idx2w[widx];
				for idx in 0..base_len {
					//let c0 = b'a' + &neighborb[idx];
					let mut neighborb = w.clone().into_bytes();
					for i in 0..26 {
						let c = b'a' + i;
						//if c == c0 { continue; }
						neighborb[idx] = c;
						let neighbor = String::from_utf8(neighborb.clone()).unwrap();
						//println!("checks {} is in s {:?}", neighbor, s);
						if s.contains(&neighbor) {
							let nidx = w2idx[&neighbor];
							println!("adds {} to next_tovisit", nidx);
							next_tovisit.insert(nidx);
							if towards_end {
								if ! directed_neighbors.contains_key(&nidx) {
									directed_neighbors.insert(nidx, Vec::new());
								}
								directed_neighbors.get_mut(&nidx).unwrap().push(*widx);
							}
							else {
								if ! directed_neighbors.contains_key(&widx) {
									directed_neighbors.insert(*widx, Vec::new());
								}
								directed_neighbors.get_mut(&widx).unwrap().push(nidx);
							}
							println!("directed_neighbors arc added");
						}
					}
				}
			}
			tovisit.clear();
			mem::swap(&mut tovisit, &mut next_tovisit);
			println!("tovisit is now {:?}", &tovisit);
			if ! tovisit_otherdir.is_disjoint(&tovisit) {
				println!("Exploration done: directed_neighbors {:?}", &directed_neighbors);
				res.push([end_word].to_vec());
				while res[0].last().unwrap() != &begin_word {
					let mut r0 : Vec<Vec<String>> = Vec::new();
					for path in res.iter() {
						let pidx = w2idx[&path.last().unwrap()];
						//println!("Look at neighbors of {}: {}", &path.last().unwrap(), pidx);
						if directed_neighbors.contains_key(&pidx) {
							for nidx in directed_neighbors[&pidx].iter() {
								let neighbor = idx2w[&nidx];
								let mut new_path = path.clone();
								new_path.push(neighbor.clone());
								r0.push(new_path);
							}
						}
					}
					mem::swap(&mut res, &mut r0);
				}
				for path in res.iter_mut() {
					path.reverse();
				}
				break;
			}
		}
		res
	}

	pub fn find_ladders_idx(begin_word: String, end_word: String, word_list: Vec<String>) ->
				Vec<Vec<String>> {

		let mut res : Vec<Vec<String>> = Vec::new();
		let base_len = begin_word.len();
		if base_len != end_word.len() {
			return res
		}
		let mut s: HashSet<&String> = word_list.iter().collect();
		if !s.contains(&end_word) {
			return res;
		}
		let mut idx2w: HashMap<i32, &String> = HashMap::new();
		let mut w2idx: HashMap<&String, i32> = HashMap::new();
		for (idx, w) in word_list.iter().enumerate() {
			idx2w.insert(idx as i32, w);
			w2idx.insert(&w, idx as i32);
		}
		if !s.contains(&begin_word) {
			idx2w.insert(-1, &begin_word);
			w2idx.insert(&begin_word, -1);
		}

		let mut directed_neighbors: HashMap<i32, Vec<i32>> = HashMap::new();
		let mut towards_end = true;
		let (mut tovisit, mut tovisit_otherdir) = (HashSet::new(), HashSet::new());
		tovisit.insert(w2idx[&begin_word]);
		tovisit_otherdir.insert(w2idx[&end_word]);

		while !tovisit.is_empty() && !tovisit_otherdir.is_empty() {
			if tovisit.len() > tovisit_otherdir.len() {
				// Always visit in the direction with the least nodes to visit
				mem::swap(&mut tovisit, &mut tovisit_otherdir);
				towards_end = !towards_end;
			}

			for widx in tovisit.iter() {
				s.remove(idx2w[widx]);
			}

			let mut next_tovisit : HashSet<i32> = HashSet::new();

			for widx in tovisit.iter() {
				let w = idx2w[widx];
				for idx in 0..base_len {
					let mut neighborb = w.clone().into_bytes();
					for i in 0..26 {
						let c = b'a' + i;
						neighborb[idx] = c;
						let neighbor = String::from_utf8(neighborb.clone()).unwrap();
						if s.contains(&neighbor) {
							let nidx = w2idx[&neighbor];
							next_tovisit.insert(nidx);
							if towards_end {
								if ! directed_neighbors.contains_key(&nidx) {
									directed_neighbors.insert(nidx, Vec::new());
								}
								directed_neighbors.get_mut(&nidx).unwrap().push(*widx);
							}
							else {
								if ! directed_neighbors.contains_key(&widx) {
									directed_neighbors.insert(*widx, Vec::new());
								}
								directed_neighbors.get_mut(&widx).unwrap().push(nidx);
							}
						}
					}
				}
			}
			tovisit.clear();
			mem::swap(&mut tovisit, &mut next_tovisit);
			if ! tovisit_otherdir.is_disjoint(&tovisit) {
				res.push([end_word].to_vec());
				while res[0].last().unwrap() != &begin_word {
					let mut r0 : Vec<Vec<String>> = Vec::new();
					for path in res.iter() {
						let pidx = w2idx[&path.last().unwrap()];
						if directed_neighbors.contains_key(&pidx) {
							for nidx in directed_neighbors[&pidx].iter() {
								let neighbor = idx2w[&nidx];
								let mut new_path = path.clone();
								new_path.push(neighbor.clone());
								r0.push(new_path);
							}
						}
					}
					mem::swap(&mut res, &mut r0);
				}
				for path in res.iter_mut() {
					path.reverse();
				}
				break;
			}
		}
		res
	}*/

	pub fn find_ladders(begin_word: String, end_word: String, word_list: Vec<String>) ->
				Vec<Vec<String>> {

		let mut res : Vec<Vec<String>> = Vec::new();
		let base_len = begin_word.len();
		if base_len != end_word.len() {
			return res
		}
		let mut s: HashSet<&String> = word_list.iter().collect();
		if !s.contains(&end_word) {
			return res;
		}

		let mut directed_neighbors: HashMap<&String, Vec<&String>> = HashMap::new();
		let mut towards_end = true;
		let (mut tovisit, mut tovisit_otherdir) = (HashSet::new(), HashSet::new());
		tovisit.insert(&begin_word);
		tovisit_otherdir.insert(&end_word);

		while !tovisit.is_empty() && !tovisit_otherdir.is_empty() {
			if tovisit.len() > tovisit_otherdir.len() {
				// Always visit in the direction with the least nodes to visit
				mem::swap(&mut tovisit, &mut tovisit_otherdir);
				towards_end = !towards_end;
			}

			for w in tovisit.iter() {
				s.remove(w);
			}

			let mut next_tovisit : HashSet<&String> = HashSet::new();

			for w in tovisit.iter() {
				for idx in 0..base_len {
					let mut neighborb = (*w).clone().into_bytes();
					for i in 0..26 {
						let c = b'a' + i;
						neighborb[idx] = c;
						let key = s.get(&String::from_utf8(neighborb.clone()).unwrap());
						if let Some(neighbor) = key {
							next_tovisit.insert(neighbor);
							if towards_end {
								directed_neighbors.entry(neighbor).or_insert(Vec::new()).push(w);
							}
							else {
								directed_neighbors.entry(w).or_insert(Vec::new()).push(neighbor);
							}
						}
					}
				}
			}
			tovisit.clear();
			mem::swap(&mut tovisit, &mut next_tovisit);

			if ! tovisit_otherdir.is_disjoint(&tovisit) {
				res.push([end_word.clone()].to_vec());
				while res[0].last().unwrap() != &begin_word {
					let mut r0 : Vec<Vec<String>> = Vec::new();
					res.retain(|path| { directed_neighbors.contains_key(path.last().unwrap()) });
					for path in res.iter() {
						let w = path.last().unwrap();
						for neighbor in directed_neighbors[w].iter() {
							let mut new_path = path.clone();
							new_path.push((*neighbor).clone());
							r0.push(new_path);
						}
					}
					mem::swap(&mut res, &mut r0);
				}
				for path in res.iter_mut() {
					path.reverse();
				}
				break;
			}
		}
		res
	}
}

fn compare_vectors(v0: &Vec<Vec<String>>, v1: &Vec<Vec<String>>) -> bool {
	if v0.len() != v1.len() { return false; }
	let mut found = vec!(0; v0.len());
	for v in v0.iter() {
		for (i, w) in v1.iter().enumerate() {
			if found[i] > 0 { continue; }
			if w == v {
				found[i] = 1;
				break;
			}
		}
	}
	found.iter().sum::<u32>() == v0.len() as u32
}

fn run_test_case(test_case: &json::JsonValue) -> i32 {

	let begin_word = &test_case["in"]["begin_word"];
	let end_word = &test_case["in"]["end_word"];
	let dictionnary = &test_case["in"]["dictionnary"];
	let expected = &test_case["expected"];

	let mut word_list = Vec::new();
	for word in dictionnary.members() {
		word_list.push(word.as_str().unwrap().to_string());
	}

	let mut exp = Vec::new();
	for solution in expected.members() {
		let mut s = Vec::new();
		for word in solution.members() {
			s.push(word.as_str().unwrap().to_string());
		}
		exp.push(s);
	}

	let result = Solution::find_ladders(begin_word.to_string(), end_word.to_string(), word_list);

	if compare_vectors(&result, &exp) {
		return 0;
	}

	println!("result.len {}, expected.len {}\n", result.len(), expected.len());

	println!("find_ladders({}, {}, {}) returned {:?} but expected {:?}\n",
		begin_word, end_word, dictionnary, result, expected);
	1
}

fn main() {
	let (tests, test_idx) = algo_tools::load_json_tests();
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
