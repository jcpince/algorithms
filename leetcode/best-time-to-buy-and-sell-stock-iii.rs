use std::slice;
use std::cmp;

fn max_subprofit(prices: &[i32]) -> i32 {
	if prices.len() == 0 { return 0 }
	let mut min = prices[0];
	let mut best : i32 = 0;
	for i in 0..prices.len() {
		if prices[i] < min { min = prices[i]; }
		let delta : i32 = prices[i] - min;
		if delta > best {
			best = delta;
		}
	}
	best
}

fn max_profit0(prices: Vec<i32>) -> i32 {
	let mut best = 0;
	for pivot in 0..prices.len() {
		let r1 = &prices[..pivot];
		let r2 = &prices[pivot..];
		let sum = max_subprofit(r1) + max_subprofit(r2);
		//println!("[{}]: {:?} - {} + {:?} - {}", pivot, r1, max_subprofit(r1), r2, max_subprofit(r2));
		if sum > best {
			best = sum;
		}
	}
	best
}

fn max_profit_solution(prices: Vec<i32>) -> i32 {
	let (mut buy_last, mut profit_last) = (i32::MIN, 0);
	let (mut sell1_buy2_diff, mut profit_global) = (i32::MIN, 0);
	println!("price {:?}:", prices);
	for price in &prices {
		buy_last = cmp::max(buy_last, -price);
		profit_last = cmp::max(profit_last, buy_last + price);
		sell1_buy2_diff = cmp::max(sell1_buy2_diff, profit_last - price);
		profit_global = cmp::max(profit_global, sell1_buy2_diff + price);

		println!("price {}: sell1_buy2_diff {}, profit_global {}, buy_last {}, profit_last {}",
					price, sell1_buy2_diff, profit_global, buy_last, profit_last);
	}
	profit_global
}

fn max_profit_dpref(prices: Vec<i32>) -> i32 {
	let n = prices.len();
	if n < 2 { return 0; }

	let mut left = vec!(0; n);
	let mut right = vec!(0; n);
	let (mut lmin, mut rmax) = (prices[0], prices[n-1]);
	for idx in 1..n-1 {
		let lp = prices[idx];
		let rp = prices[n-idx-1];
		if lp < lmin {
			lmin = lp;
			left[idx] = left[idx-1];
		} else {
			left[idx] = cmp::max(left[idx-1], lp - lmin);
		}
		if rp < rmax {
			rmax = rp;
			right[n-idx-1] = right[n-idx];
		} else {
			right[n-idx-1] = cmp::max(right[n-idx], rmax - rp);
		}
	}

	let mut profit : i32 = 0;
	for idx in 0..n {
		profit = cmp::max(profit, left[idx] + right[idx]);
	}
	profit
}

fn max_profit_dp0(prices: Vec<i32>) -> i32 {
	let n = prices.len();
	if n < 2 { return 0; }

	let (mut left, mut right) = (vec!(0; n), vec!(0; n));
	let (mut lmin, mut rmax) = (prices[0], prices[n-1]);
	let (mut lbest, mut rbest) = (0, 0);

	let mut best = 0;
	for i in 1..n {
		let price = prices[i];
		lmin = cmp::min(lmin, price);
		let max_profit = price - lmin;
		lbest = cmp::max(lbest, max_profit);
		left[i] = lbest;

		let price = prices[n-i-1];
		rmax = cmp::max(rmax, price);
		let max_profit = rmax - price;
		rbest = cmp::max(rbest, max_profit);
		right[n - i - 1] = rbest;

		if i >= n - i - 1 {
			best = cmp::max(best, cmp::max(left[n-i-1] + right[n-i-1], left[i] + right[i]));
		}
	}
	//println!("prices {:?}, left {:?}, right {:?}", prices, left, right);
	best
}

fn max_profit_dp(prices: Vec<i32>) -> i32 {
	let n = prices.len();
	if n < 2 { return 0; }

	let mut max_profit = vec!(0; n);
	let (mut lmin, mut rmax) = (prices[0], prices[n-1]);
	let (mut lbest, mut rbest) = (0, 0);

	let mut best = 0;
	for i in 1..n {
		let price = prices[i];
		lmin = cmp::min(lmin, price);
		let profit = price - lmin;
		lbest = cmp::max(lbest, profit);

		let price = prices[n-i-1];
		rmax = cmp::max(rmax, price);
		let profit = rmax - price;
		rbest = cmp::max(rbest, profit);

		max_profit[i] += lbest;
		max_profit[n - i - 1] += rbest;

		if i >= n - i - 1 {
			best = cmp::max(best, cmp::max(max_profit[n-i-1], max_profit[i]));
		}
	}
	//println!("prices {:?}, left {:?}, right {:?}", prices, left, right);
	best
}

# [no_mangle]
pub extern "C" fn max_profit_rs(_prices: *const i32, len: usize) -> i32 {

	let prices = unsafe {
		assert!(!_prices.is_null());
		slice::from_raw_parts(_prices, len)
	};

	max_profit_dp(prices.to_vec())
}
