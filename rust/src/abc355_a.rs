#![allow(unused_imports, dead_code, non_snake_case)]
use std::cmp::*;
use std::collections::*;
use proconio::{input, marker::{Chars, Bytes, Usize1}};


const INF: usize = 1000000007;

fn main() {
    input! {
        mut a: usize,
        mut b: usize,
    }
    let mut bools: [bool; 3] = [true, true, true];
    a -= 1;
    b -= 1;
    bools[a] = false;
    bools[b] = false;
    for (i, boolv) in bools.iter().enumerate() {
        if *(boolv) {
            println!("{}", i + 1);
        }
    }
}
