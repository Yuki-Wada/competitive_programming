#![allow(unused_imports, dead_code, non_snake_case)]
use ac_library::ModInt998244353 as Mint;
use proconio::{
    input,
    marker::{Bytes, Chars, Usize1},
};
use std::cmp::*;
use std::collections::*;

const INF: usize = 1000000007;

#[allow(clippy::many_single_char_names)]
pub struct SegmentTreeLazy<I, M, FII, FIM, FMM>
where
    I: Copy,
    M: Copy + PartialEq,
    FII: Fn(I, I) -> I + Copy,
    FIM: Fn(I, M) -> I + Copy,
    FMM: Fn(M, M) -> M + Copy,
{
    size: usize,
    data: Vec<I>,
    lazy: Vec<M>,
    op_ii: FII,
    op_im: FIM,
    op_mm: FMM,
    id_ii: I,
    id_mm: M,
}

impl<I, M, FII, FIM, FMM> SegmentTreeLazy<I, M, FII, FIM, FMM>
where
    I: Copy,
    M: Copy + PartialEq,
    FII: Fn(I, I) -> I + Copy,
    FIM: Fn(I, M) -> I + Copy,
    FMM: Fn(M, M) -> M + Copy,
{
    pub fn new(max_size: usize, op_ii: FII, id_ii: I, op_im: FIM, op_mm: FMM, id_mm: M) -> Self {
        let mut size = 1usize;
        while size < max_size {
            size <<= 1;
        }
        Self {
            size,
            data: vec![id_ii; size * 2 - 1],
            lazy: vec![id_mm; size * 2 - 1],
            op_ii,
            op_im,
            op_mm,
            id_ii,
            id_mm,
        }
    }

    pub fn size(&self) -> usize {
        self.size
    }

    pub fn update_range(&mut self, l: usize, r: usize, value: M) {
        assert!(l < r && r <= self.size);
        self.update_range_rec(l, r, value, 0, 0, self.size);
    }

    pub fn update_point(&mut self, mut index: usize, value: I) {
        assert!(index < self.size);
        index += self.size - 1;
        self.data[index] = value;
        while index > 0 {
            index = (index - 1) / 2;
            self.data[index] = (self.op_ii)(self.data[index * 2 + 1], self.data[index * 2 + 2]);
        }
    }

    pub fn query(&mut self, l: usize, r: usize) -> I {
        assert!(l < r && r <= self.size);
        self.query_rec(l, r, 0, 0, self.size)
    }

    fn propagate(&mut self, k: usize) {
        if self.lazy[k] == self.id_mm {
            return;
        }
        if k < self.size - 1 {
            let lc = 2 * k + 1;
            let rc = 2 * k + 2;
            self.lazy[lc] = (self.op_mm)(self.lazy[lc], self.lazy[k]);
            self.lazy[rc] = (self.op_mm)(self.lazy[rc], self.lazy[k]);
        }
        self.data[k] = (self.op_im)(self.data[k], self.lazy[k]);
        self.lazy[k] = self.id_mm;
    }

    fn update_range_rec(&mut self, l: usize, r: usize, value: M, k: usize, nl: usize, nr: usize) {
        self.propagate(k);
        if r <= nl || nr <= l {
            return;
        }
        if l <= nl && nr <= r {
            self.lazy[k] = (self.op_mm)(self.lazy[k], value);
            self.propagate(k);
            return;
        }
        let mid = (nl + nr) / 2;
        self.update_range_rec(l, r, value, 2 * k + 1, nl, mid);
        self.update_range_rec(l, r, value, 2 * k + 2, mid, nr);
        self.data[k] = (self.op_ii)(self.data[2 * k + 1], self.data[2 * k + 2]);
    }

    fn query_rec(&mut self, l: usize, r: usize, k: usize, nl: usize, nr: usize) -> I {
        self.propagate(k);
        if r <= nl || nr <= l {
            return self.id_ii;
        }
        if l <= nl && nr <= r {
            return self.data[k];
        }
        let mid = (nl + nr) / 2;
        let left = self.query_rec(l, r, 2 * k + 1, nl, mid);
        let right = self.query_rec(l, r, 2 * k + 2, mid, nr);
        (self.op_ii)(left, right)
    }
}

fn solve() {
    input! {
        w: usize,
        n: usize,
        mut lrs: [(usize, usize); n],
    }

    // 「区間 max」用のセグ木を用意
    let mut seg = SegmentTreeLazy::new(
        w,
        |a: i64, b: i64| a.max(b), // I × I
        0_i64,                     // 単位元 (I)
        |a: i64, b: i64| a.max(b), // I × M
        |a: i64, b: i64| a.max(b), // M × M
        0_i64,                     // 単位元 (M)
    );

    let mut out = String::with_capacity(n * 20);

    for i in 0..n {
        let (l, r) = lrs[i];

        let current_max = seg.query(l - 1, r);
        let next_val = current_max + 1;
        out.push_str(&(next_val.to_string()));
        out.push('\n');

        seg.update_range(l - 1, r, next_val);
    }

    print!("{}", out);
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
