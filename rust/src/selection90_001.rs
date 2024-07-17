#![allow(unused_imports, dead_code)]
use std::cmp::*;
use std::collections::*;
use proconio::input;


fn main() {
    input! {
        n: i64,
        l: i64,
        k: i64,
        mut a: [i64; n],
    }

    a.push(l);
    let mut low = 1;
    let mut high = 1000000001;
    let mut mid = (low + high) / 2;
    while high - low >= 2 {
        let mut prev = 0;
        let mut block_count = 0;
        for i in 0..=n as usize {
            if a[i] - prev >= mid {
                prev = a[i];
                block_count += 1;
            }
        }
        if block_count >= k + 1 {
            low = mid
        } else {
            high = mid;
        }
        mid = (low + high) / 2
    }

    println!("{}", low);
}
