use std::ffi::CStr;
use std::os::raw::c_char;

pub fn num_distinct(s: String, t: String) -> i32 {

    let slen = s.len();
    let tlen = t.len();
    if slen < tlen {
        return 0
    }
    if slen == tlen {
        if s == t { return 1 }
        else { return 0 }
    }
    if tlen == 0 { return 1 }

    let _s: &[u8] = s.as_bytes();
    let _t: &[u8] = t.as_bytes();
    let mut dp : Vec<i128> = vec![1; slen+1];
    for i in 1..tlen+1 {
        let mut dp0 = dp[0];
        dp[0] = 0;
        for j in 1..slen+1 {
            let _dp0 = dp[j];
            dp[j] = dp[j-1];
            if _s[j-1] == _t[i-1] {
                // caps the sum to avoid integer overflows
                dp[j] += dp0 & 0xffffffff;
            }
            dp0 = _dp0;
        }
    }
    dp[slen] as i32
}

# [no_mangle]
pub extern "C" fn num_distinct_rs(_s: *const c_char, _t: *const c_char) -> i32 {

    let s_str = unsafe { CStr::from_ptr(_s) };
    let t_str = unsafe { CStr::from_ptr(_t) };

    return num_distinct(
        s_str.to_str().unwrap().to_owned(),
        t_str.to_str().unwrap().to_owned())
}
