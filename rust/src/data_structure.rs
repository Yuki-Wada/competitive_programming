use std::cmp::*;
use std::collections::*;

struct UnionFind {
    n: usize,
    size: Vec<i32>,
}

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

    pub fn apply(&mut self, l: usize, r: usize, value: M) {
        assert!(l < r && r <= self.size);
        self.apply_internal(l, r, value, 0, 0, self.size);
    }

    pub fn set(&mut self, mut index: usize, value: I) {
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
        self.query_internal(l, r, 0, 0, self.size)
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

    fn apply_internal(&mut self, l: usize, r: usize, value: M, k: usize, nl: usize, nr: usize) {
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
        self.apply_internal(l, r, value, 2 * k + 1, nl, mid);
        self.apply_internal(l, r, value, 2 * k + 2, mid, nr);
        self.data[k] = (self.op_ii)(self.data[2 * k + 1], self.data[2 * k + 2]);
    }

    fn query_internal(&mut self, l: usize, r: usize, k: usize, nl: usize, nr: usize) -> I {
        self.propagate(k);
        if r <= nl || nr <= l {
            return self.id_ii;
        }
        if l <= nl && nr <= r {
            return self.data[k];
        }
        let mid = (nl + nr) / 2;
        let left = self.query_internal(l, r, 2 * k + 1, nl, mid);
        let right = self.query_internal(l, r, 2 * k + 2, mid, nr);
        (self.op_ii)(left, right)
    }
}
