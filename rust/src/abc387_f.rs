#![allow(unused_imports, dead_code, non_snake_case)]
use std::cmp::*;
use std::collections::*;
use std::fmt::{Display, Formatter, Result as FmtResult};
use std::io::{self, Read};
use std::ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Sub, SubAssign};

use proconio::{
    input,
    marker::{Bytes, Chars, Usize1},
};

const INF: usize = 1000000007;

#[derive(Clone, Debug)]
pub struct Graph<E: Clone + Default> {
    pub vertex_count: usize,
    pub edges: Vec<(usize, usize, E)>, // (from, to, info)
}

impl<E: Clone + Default> Graph<E> {
    pub fn new(vertex_count: usize) -> Self {
        Self {
            vertex_count,
            edges: Vec::new(),
        }
    }

    pub fn add_edge(&mut self, from: usize, to: usize, info: E) {
        self.edges.push((from, to, info));
    }

    pub fn add_edge_default(&mut self, from: usize, to: usize) {
        self.edges.push((from, to, E::default()));
    }

    fn adjacency(&self) -> Vec<Vec<usize>> {
        let mut g = vec![Vec::new(); self.vertex_count];
        for &(from, to, _) in &self.edges {
            g[from].push(to);
        }
        g
    }

    fn rev_adjacency(&self) -> Vec<Vec<usize>> {
        let mut g = vec![Vec::new(); self.vertex_count];
        for &(from, to, _) in &self.edges {
            g[to].push(from);
        }
        g
    }
}

/// Kosaraju（2 回 DFS）で強連結成分分解
/// 戻り値: `comp[v] = component id`（0,1,2,...）
pub fn get_scc<E: Clone + Default>(g: &Graph<E>) -> Vec<usize> {
    let n = g.vertex_count;
    let adj = g.adjacency();
    let rev = g.rev_adjacency();

    // 1st pass: トポロジカル順（終了時刻順）
    let mut visited = vec![false; n];
    let mut order = Vec::<usize>::with_capacity(n);

    fn dfs1(v: usize, adj: &Vec<Vec<usize>>, visited: &mut [bool], order: &mut Vec<usize>) {
        visited[v] = true;
        for &u in &adj[v] {
            if !visited[u] {
                dfs1(u, adj, visited, order);
            }
        }
        order.push(v);
    }

    for v in 0..n {
        if !visited[v] {
            dfs1(v, &adj, &mut visited, &mut order);
        }
    }

    // 2nd pass: 逆向きグラフで成分番号付け
    let mut comp = vec![usize::MAX; n];
    fn dfs2(v: usize, rev: &Vec<Vec<usize>>, comp: &mut [usize], current: usize) {
        comp[v] = current;
        for &u in &rev[v] {
            if comp[u] == usize::MAX {
                dfs2(u, rev, comp, current);
            }
        }
    }

    let mut current = 0;
    while let Some(v) = order.pop() {
        if comp[v] == usize::MAX {
            dfs2(v, &rev, &mut comp, current);
            current += 1;
        }
    }

    comp
}

#[derive(Copy, Clone, Debug, Eq, PartialEq)]
pub struct ModInt<const MOD: i64> {
    val: i64,
}

impl<const MOD: i64> ModInt<MOD> {
    pub fn new<T: Into<i64>>(x: T) -> Self {
        let mut v = x.into() % MOD;
        if v < 0 {
            v += MOD;
        }
        Self { val: v }
    }
    pub fn value(self) -> i64 {
        self.val
    }
    fn inv(self) -> Self {
        // 拡張ユークリッド
        fn egcd(a: i64, b: i64) -> (i64, i64) {
            if b == 0 {
                (1, 0)
            } else {
                let (x, y) = egcd(b, a % b);
                (y, x - (a / b) * y)
            }
        }
        let (x, _) = egcd(self.val, MOD);
        Self::new(x)
    }
}

impl<const MOD: i64> From<i64> for ModInt<MOD> {
    fn from(value: i64) -> Self {
        Self::new(value)
    }
}

impl<const MOD: i64> Display for ModInt<MOD> {
    fn fmt(&self, f: &mut Formatter<'_>) -> FmtResult {
        write!(f, "{}", self.val)
    }
}

// ---- 四則演算 ----
impl<const MOD: i64> Add for ModInt<MOD> {
    type Output = Self;
    fn add(self, rhs: Self) -> Self::Output {
        Self::new(self.val + rhs.val)
    }
}
impl<const MOD: i64> AddAssign for ModInt<MOD> {
    fn add_assign(&mut self, rhs: Self) {
        *self = *self + rhs;
    }
}
impl<const MOD: i64> Sub for ModInt<MOD> {
    type Output = Self;
    fn sub(self, rhs: Self) -> Self::Output {
        Self::new(self.val - rhs.val)
    }
}
impl<const MOD: i64> SubAssign for ModInt<MOD> {
    fn sub_assign(&mut self, rhs: Self) {
        *self = *self - rhs;
    }
}
impl<const MOD: i64> Mul for ModInt<MOD> {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self::Output {
        Self::new(self.val * rhs.val)
    }
}
impl<const MOD: i64> MulAssign for ModInt<MOD> {
    fn mul_assign(&mut self, rhs: Self) {
        *self = *self * rhs;
    }
}
impl<const MOD: i64> Div for ModInt<MOD> {
    type Output = Self;
    fn div(self, rhs: Self) -> Self::Output {
        self * rhs.inv()
    }
}
impl<const MOD: i64> DivAssign for ModInt<MOD> {
    fn div_assign(&mut self, rhs: Self) {
        *self = *self / rhs;
    }
}

const MOD: i64 = 998_244_353;
type Mint = ModInt<MOD>;

fn dfs(idx: usize, tree: &Vec<Vec<usize>>, dps: &mut [Vec<Mint>], visited: &mut [bool], m: usize) {
    for &child in &tree[idx] {
        dfs(child, tree, dps, visited, m);
        let mut acc = Mint::new(0);
        for j in 0..m {
            acc += dps[child][j];
            dps[idx][j] *= acc;
        }
    }
    visited[idx] = true;
}

fn calc(
    idx: usize,
    tree: &Vec<Vec<usize>>,
    dps: &mut [Vec<Mint>],
    visited: &mut [bool],
    m: usize,
) -> Mint {
    dfs(idx, tree, dps, visited, m);
    dps[idx].iter().fold(Mint::new(0), |s, &v| s + v)
}

fn solve() {
    input! {
        n: usize,
        m: usize,
        mut As: [usize; n],
    }

    // 元グラフと子リスト
    let mut g = Graph::<i64>::new(n);
    let mut node_edges = vec![Vec::<usize>::new(); n];

    for i in 0..n {
        let mut a: usize = As[i];
        a -= 1; // 0-index
        g.add_edge_default(a, i);
        node_edges[a].push(i);
    }

    // SCC
    let scc = get_scc(&g);
    let comp_cnt = scc.iter().copied().max().unwrap() + 1;
    let mut comp_edges = vec![Vec::<usize>::new(); comp_cnt];

    for v in 0..n {
        for &to in &node_edges[v] {
            if scc[v] != scc[to] {
                comp_edges[scc[v]].push(scc[to]);
            }
        }
    }

    // DP
    let mut dps = vec![vec![Mint::new(1); m]; comp_cnt];
    let mut visited = vec![false; comp_cnt];
    let mut ans = Mint::new(1);

    for c in 0..comp_cnt {
        if !visited[c] {
            ans *= calc(c, &comp_edges, &mut dps, &mut visited, m);
        }
    }
    println!("{}", ans.value().to_string());
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
