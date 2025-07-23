#![allow(unused_imports, dead_code, non_snake_case)]
use ac_library::ModInt998244353 as Mint;
use proconio::{
    input,
    marker::{Bytes, Chars, Usize1},
};
use std::cmp::*;
use std::collections::*;

const INF: usize = 1000000007;

use std::io::{self, Read};

/// Union-Find (Disjoint Set Union) structure
struct UnionFind {
    parent: Vec<usize>,
    rank: Vec<usize>,
    set_size: Vec<usize>,
}

impl UnionFind {
    /// Create a new forest of `n` single-element sets
    fn new(n: usize) -> Self {
        Self {
            parent: (0..n).collect(),
            rank: vec![0; n],
            set_size: vec![1; n],
        }
    }

    /// Find the root of `x` (with path compression)
    fn find(&mut self, x: usize) -> usize {
        if self.parent[x] == x {
            x
        } else {
            let root = self.find(self.parent[x]);
            self.parent[x] = root;
            root
        }
    }

    /// Merge the sets containing `x` and `y`
    fn unite(&mut self, mut x: usize, mut y: usize) {
        x = self.find(x);
        y = self.find(y);
        if x == y {
            return;
        }
        // union by rank
        if self.rank[x] < self.rank[y] {
            std::mem::swap(&mut x, &mut y);
        }
        self.parent[y] = x;
        self.set_size[x] += self.set_size[y];
        if self.rank[x] == self.rank[y] {
            self.rank[x] += 1;
        }
    }

    #[allow(dead_code)]
    /// Size of the set containing `x`
    fn size(&mut self, x: usize) -> usize {
        let root = self.find(x);
        self.set_size[root]
    }
}

fn solve() {
    input! {
        n: usize,
        mut abs: [usize; (n - 1)* 2],
    }

    // Read entire input at once and split by whitespace

    let mut edges: Vec<Vec<usize>> = vec![Vec::new(); n];
    for i in 0..n - 1 {
        let a = abs[i * 2] - 1;
        let b = abs[i * 2 + 1] - 1;
        edges[a].push(b);
        edges[b].push(a);
    }

    let mut uf = UnionFind::new(n);

    // Unite every pair of adjacent degree-3 vertices
    for i in 0..n {
        if edges[i].len() != 3 {
            continue;
        }
        for &j in &edges[i] {
            if edges[j].len() != 3 {
                continue;
            }
            uf.unite(i, j);
        }
    }

    // Count degree-2 neighbours for each component of degree-3 vertices
    let mut comp_counts: Vec<u64> = vec![0; n];
    for i in 0..n {
        if edges[i].len() != 3 {
            continue;
        }
        for &j in &edges[i] {
            if edges[j].len() != 2 {
                continue;
            }
            let idx = uf.find(i);
            comp_counts[idx] += 1;
        }
    }

    // Sum over components: C(cnt, 2)
    let mut res: u64 = 0;
    for cnt in comp_counts {
        res += if cnt > 0 { cnt * (cnt - 1) / 2 } else { 0 };
    }

    println!("{}", res);
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
