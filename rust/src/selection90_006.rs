#![allow(unused_imports, dead_code, non_snake_case)]
use std::cmp::*;
use std::collections::*;
use proconio::{input, marker::{Chars, Bytes, Usize1}};


fn main() {
    input! {
        n: i64,
        k: i64,
        s: Bytes,
    }

    let mut st = SegTree::new(n as usize, op, (100_i64, n + 1));

    for i in 0..n as usize {
        st.update(i, ((s[i] - b'a') as i64, i as i64));
    }

    let mut ans = String::with_capacity(k as usize);
    let mut start = 0;
    let mut end = n - k + 1;
	for _ in 0..k {
		let pair = st.query(start, end as usize);
		start = pair.1 as usize + 1;
        end += 1;
        ans.push((pair.0 as u8 + b'a') as char);
	}

    println!("{}", ans);
}




fn op(a: &(i64, i64), b: &(i64, i64)) -> (i64, i64) {
    std::cmp::min(*a, *b)
}

#[allow(dead_code)]
struct SegTree<T, F>
where
    T: Clone + Copy,
    F: Fn(&T, &T) -> T,
{
    tree: Vec<T>,
    opr: F,
    id: T,
    size: usize,
}
#[allow(dead_code)]
impl<T, F> std::fmt::Display for SegTree<T, F>
where
    T: Clone + Copy + std::fmt::Debug,
    F: Fn(&T, &T) -> T,
{
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "{:?}", self.tree)
    }
}
#[allow(dead_code)]
impl<T, F> SegTree<T, F>
where
    T: Clone + Copy,
    F: Fn(&T, &T) -> T,
{
    fn new(n: usize, opr: F, id: T) -> SegTree<T, F> {
        let mut size = 1;
        while size < n {
            size *= 2;
        }
        SegTree {
            tree: vec![id; size * 2],
            opr,
            id,
            size,
        }
    }
    fn update(&mut self, i: usize, x: T) {
        let mut i = i + self.size - 1;
        self.tree[i] = x;
        while i > 0 {
            i = (i - 1) / 2;
            self.tree[i] = (self.opr)(&self.tree[i * 2 + 1], &self.tree[i * 2 + 2])
        }
    }
    fn query(&self, l: usize, r: usize) -> T {
        let mut l = l + self.size - 1;
        let mut r = r + self.size - 1;
        let mut out = self.id;
        while l < r {
            if l & 1 == 0 {
                out = (self.opr)(&out, &self.tree[l]);
            }
            if r & 1 == 0 {
                out = (self.opr)(&out, &self.tree[r - 1]);
            }
            l = l / 2;
            r = (r - 1) / 2;
        }
        out
    }
}
