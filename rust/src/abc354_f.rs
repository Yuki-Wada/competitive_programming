#![allow(unused_imports, dead_code, non_snake_case)]
use ac_library::ModInt998244353 as Mint;
use proconio::{
    input,
    marker::{Bytes, Chars, Usize1},
};
use std::cmp::*;
use std::collections::*;

const INF: usize = 1000000007;

struct SegmentTree<T, F>
where
    T: Clone + Copy,
    F: Fn(&T, &T) -> T,
{
    tree: Vec<T>,
    opr: F,
    id: T,
    size: usize,
}

impl<T, F> std::fmt::Display for SegmentTree<T, F>
where
    T: Clone + Copy + std::fmt::Debug,
    F: Fn(&T, &T) -> T,
{
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "{:?}", self.tree)
    }
}
impl<T, F> SegmentTree<T, F>
where
    T: Clone + Copy,
    F: Fn(&T, &T) -> T,
{
    fn new(n: usize, opr: F, id: T) -> SegmentTree<T, F> {
        let mut size = 1;
        while size < n {
            size *= 2;
        }
        SegmentTree {
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

fn agg(a: &i64, b: &i64) -> i64 {
    max(*a, *b)
}

fn compress_coordinates(As: &Vec<i64>) -> (Vec<usize>, Vec<i64>) {
    let mut items = vec![(0_i64, 0_usize); As.len()];
    for idx in 0..As.len() {
        items[idx] = (As[idx], idx);
    }
    items.sort();

    let mut compressed_coords = vec![0_usize; As.len()];
    let mut compression_table = vec![];

    let mut value: Option<(i64, usize)> = None;

    for (a, idx) in items {
        if value.is_none() {
            compression_table.push(a);
            let compression_count = 0_usize;
            value = Some((a, compression_count));
            compressed_coords[idx] = compression_count;
        } else {
            let (prev_a, mut compression_count) = value.unwrap();
            if prev_a != a {
                compression_count += 1;
                compression_table.push(a);
                value = Some((a, compression_count));
            }
            compressed_coords[idx] = compression_count;
        }
    }
    (compressed_coords, compression_table)
}

fn solve() {
    input! {
        N: usize,
        As: [i64; N],
    }

    let (compressed_coords, _) = compress_coordinates(&As);
    let mut forward_seg = SegmentTree::new(N + 1, agg, 0_i64);
    let mut prev_lengths: Vec<(usize, i64)> = vec![];

    for i in 0..N {
        let coord = compressed_coords[i];

        let updated = forward_seg.query(0, coord) + 1;
        let prev_length = forward_seg.query(coord, coord + 1);
        forward_seg.update(coord, updated);
        prev_lengths.push((coord, prev_length));
    }

    let max_len = forward_seg.query(0, N + 1);
    let mut res: Vec<usize> = vec![];
    let mut backward_seg = SegmentTree::new(N + 1, agg, 0_i64);
    for i in 0..N {
        let coord = compressed_coords[N - 1 - i];
        let updated = backward_seg.query(coord + 1, N + 1) + 1;
        backward_seg.update(coord, updated);

        let val = forward_seg.query(coord, coord + 1) + backward_seg.query(coord, coord + 1) - 1;
        if val == max_len {
            res.push(N - i);
        }

        let (prev_coord, prev_length) = *prev_lengths.last().unwrap();
        prev_lengths.pop();
        forward_seg.update(prev_coord, prev_length);
    }

    res.reverse();
    println!("{}", res.len());
    for v in res {
        print!("{} ", v);
    }
    println!()
}

fn main() {
    // solve();
    input! {
        t: i64,
    }
    for _ in 0..t {
        solve();
    }
}
