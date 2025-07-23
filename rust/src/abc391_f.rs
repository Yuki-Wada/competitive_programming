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
        mut K: usize,
        mut As: [i64; N],
        mut Bs: [i64; N],
        mut Cs: [i64; N],
    }

    As.sort();
    As.reverse();
    Bs.sort();
    Bs.reverse();
    Cs.sort();
    Cs.reverse();

    let calc = |a: i64, b: i64, c: i64| a * b + b * c + c * a;
    let mut bin_heap: BinaryHeap<(i64, usize, usize, usize)> = BinaryHeap::new();
    let mut added: HashSet<(usize, usize, usize)> = HashSet::new();
    bin_heap.push((calc(As[0], Bs[0], Cs[0]), 0, 0, 0));
    added.insert((0, 0, 0));

    while !bin_heap.is_empty() {
        let (res, ia, ib, ic) = bin_heap.pop().unwrap();
        K = K - 1;
        if K == 0 {
            println!("{}", res);
            break;
        }
        if ia + 1 < N && !added.contains(&(ia + 1, ib, ic)) {
            bin_heap.push((calc(As[ia + 1], Bs[ib], Cs[ic]), ia + 1, ib, ic));
            added.insert((ia + 1, ib, ic));
        }
        if ib + 1 < N && !added.contains(&(ia, ib + 1, ic)) {
            bin_heap.push((calc(As[ia], Bs[ib + 1], Cs[ic]), ia, ib + 1, ic));
            added.insert((ia, ib + 1, ic));
        }
        if ic + 1 < N && !added.contains(&(ia, ib, ic + 1)) {
            bin_heap.push((calc(As[ia], Bs[ib], Cs[ic + 1]), ia, ib, ic + 1));
            added.insert((ia, ib, ic + 1));
        }
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
