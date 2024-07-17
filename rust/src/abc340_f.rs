#![allow(unused_imports, dead_code, non_snake_case)]
use ac_library::ModInt998244353 as Mint;
use proconio::{
    input,
    marker::{Bytes, Chars, Usize1},
};
use std::cmp::*;
use std::collections::*;

const INF: usize = 1000000007;

pub fn get_gcd(mut a: i64, mut b: i64) -> i64 {
    while b != 0 {
        a %= b;
        std::mem::swap(&mut a, &mut b);
    }
    a
}

fn compute_bezout(a: i64, b: i64) -> (i64, i64) {
    if b == 0 {
        return (1, 0);
    }
    if a % b == 0_i64 {
        return (0, 1);
    }

    let r = a % b;
    let q = a / b;
    let (px, py) = compute_bezout(b, r);
    let (cx, cy) = (py, px - q * py);

    let x = ((cx % b) + b) % b;
    let y = ((cy % a) + a) % a - a;
    (x, y)
}

fn main() {
    input! {
        mut X: i64,
        mut Y: i64,
    }
    let abs_X = X.abs();
    let abs_Y = Y.abs();

    let gcd = get_gcd(abs_X, abs_Y);
    if gcd > 2 {
        println!("-1");
        return;
    }

    let (mut b, mut a) = compute_bezout(abs_X, abs_Y);
    b = -b;
    a *= if X >= 0 { 1 } else { -1 };
    b *= if Y >= 0 { 1 } else { -1 };
    a *= 2 / gcd;
    b *= 2 / gcd;

    println!("{} {}", a, b);
}
