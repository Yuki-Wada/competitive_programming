#![allow(unused_imports, dead_code, non_snake_case)]
use ac_library::ModInt998244353 as Mint;
use proconio::{
    input,
    marker::{Bytes, Chars, Usize1},
};
use std::cmp::*;
use std::collections::*;

const INF: usize = 1000000007;

fn solve() {
    input! {
        N: usize,
        Q: usize,
        Cs: [i64; N],
    }

    let mut box_indexes: Vec<usize> = (0..N).collect();
    let mut set_sizes = vec![1_i64; N];
    let mut st: BTreeSet<(usize, i64)> = vec![].into_iter().collect();

    for idx in 0..N {
        let C = Cs[idx];
        st.insert((idx, C));
    }

    for _ in 0..Q {
        input! {
            mut a_box: usize,
            mut b_box: usize,
        }
        a_box -= 1;
        b_box -= 1;
        let a_idx = box_indexes[a_box];
        let b_idx = box_indexes[b_box];
        if set_sizes[a_idx] > set_sizes[b_idx] {
            let tmp = box_indexes[a_box];
            box_indexes[a_box] = box_indexes[b_box];
            box_indexes[b_box] = tmp;
        }
        let a_idx = box_indexes[a_box];
        let b_idx = box_indexes[b_box];

        let mut iter = st.range((a_idx, -1)..(a_idx + 1, -1));
        let mut colors: Vec<i64> = vec![];
        loop {
            if let Some((_, C)) = iter.next() {
                colors.push(*C);
                set_sizes[a_idx] -= 1;
            } else {
                break;
            }
        }
        for c in colors {
            st.remove(&(a_idx, c));
            if !st.contains(&(b_idx, c)) {
                st.insert((b_idx, c));
                set_sizes[b_idx] += 1;
            };
        }

        println!("{}", set_sizes[b_idx]);
    }
}

fn main() {
    solve();

    // input! {
    //     t: i64,
    // }
    // for _ in 0..t {
    //     solve();
    // }
}
