#![allow(unused_imports, dead_code)]
use std::cmp::*;
use std::collections::*;
use proconio::input;

fn main() {
    let (h, w) = {
        let tmp = readvec::<usize>();
        (tmp[0], tmp[1])
    };

    let q = readln::<usize>();

    let mut is_red = vec![false; h * w];
    let mut uf = UnionFind::new(h * w);
    for _i in 0 .. q {
        let a = readvec::<usize>();
        if a[0] == 1 {
            let r = a[1] - 1;
            let c = a[2] - 1;
            is_red[r * w + c] = true;
            if r > 0 && is_red[(r - 1) * w + c]{
                uf.merge(r * w + c, (r - 1) * w + c);
            }
            if r + 1 < h && is_red[(r + 1) * w + c]{
                uf.merge(r * w + c, (r + 1) * w + c);
            }
            if c > 0 && is_red[r * w + c - 1] {
                uf.merge(r * w + c, r * w + c - 1);
            }
            if c + 1 < w && is_red[r * w + c + 1] {
                uf.merge(r * w + c, r * w + c + 1);
            }
        }
        else {
            let ra = a[1] - 1;
            let ca = a[2] - 1;
            let rb = a[3] - 1;
            let cb = a[4] - 1;
            if uf.is_merged(ra * w + ca, rb * w + cb) && is_red[ra * w + ca] && is_red[rb * w + cb]{
                println!("Yes");
            }
            else {
                println!("No");
            }
        }
    }
}


struct UnionFind {
    n: usize,
    size: Vec<i32>,
}

impl UnionFind {
    fn new(n: usize) -> Self {
        Self {
            n: n,
            size: vec![-1; n],
        }
    }
    fn root(&mut self, x: usize) -> usize {
        if self.size[x] < 0 {
            x
        } else {
            self.size[x] = self.root(self.size[x] as usize) as i32;
            self.size[x] as usize
        }
    }
    fn merge(&mut self, x: usize, y: usize) -> bool {
        let x = self.root(x);
        let y = self.root(y);
        if x == y {
            return false;
        }
        if -self.size[x] < -self.size[y] {
            self.size[y] += self.size[x];
            self.size[x] = y as i32;
        } else {
            self.size[x] += self.size[y];
            self.size[y] = x as i32;
        }
        true
    }
    fn is_merged(&mut self, x: usize, y: usize) -> bool {
        self.root(x) == self.root(y)
    }
    fn is_root(&mut self, x: usize) -> bool {
        x == self.root(x)
    }
    fn size(&mut self, x: usize) -> usize {
        let x = self.root(x);
        -self.size[x] as usize
    }
}

fn readln<T: std::str::FromStr>() -> T {
    let mut tmp = String::new();
    std::io::stdin().read_line(&mut tmp).ok();
    tmp.trim().parse().ok().unwrap()
}
fn readvec<T: std::str::FromStr>() -> Vec<T> {
    readln::<String>()
        .split_whitespace()
        .map(|x| x.parse().ok().unwrap())
        .collect()
}
