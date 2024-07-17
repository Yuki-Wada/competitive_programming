use std::cmp::*;
use std::collections::*;

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
