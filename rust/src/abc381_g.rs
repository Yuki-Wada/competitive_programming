#![allow(
    unused_imports,
    dead_code,
    non_snake_case,
    clippy::many_single_char_names
)]
use std::cmp::*;
use std::collections::*;
use std::fmt::{Display, Formatter, Result as FmtResult};
use std::io::{self, Read};
use std::ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Neg, Sub, SubAssign};
// use ac_library::ModInt998244353 as Mint;
use proconio::{
    input,
    marker::{Bytes, Chars, Usize1},
};

const INF: usize = 1000000007;

const MOD: i64 = 998_244_353;

#[derive(Clone, Copy, Debug, Eq, PartialEq)]
pub struct ModInt<const M: i64> {
    val: i64,
}
impl<const M: i64> ModInt<M> {
    #[inline]
    pub fn new<T: Into<i64>>(x: T) -> Self {
        let mut v = x.into() % M;
        if v < 0 {
            v += M;
        }
        Self { val: v }
    }
    #[inline]
    pub fn value(self) -> i64 {
        self.val
    }
    #[inline]
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
        let (x, _) = egcd(self.val, M);
        Self::new(x)
    }
}
impl<const M: i64> Default for ModInt<M> {
    fn default() -> Self {
        Self::new(0)
    }
}
impl<const M: i64> From<i64> for ModInt<M> {
    fn from(v: i64) -> Self {
        Self::new(v)
    }
}
impl<const M: i64> Display for ModInt<M> {
    fn fmt(&self, f: &mut Formatter<'_>) -> FmtResult {
        write!(f, "{}", self.val)
    }
}
impl<const M: i64> Neg for ModInt<M> {
    type Output = Self;
    #[inline]
    fn neg(self) -> Self::Output {
        Self::new(-self.val)
    }
}

// ---- 四則演算 ----
macro_rules! impl_op {
    ($trait:ident,$func:ident,$op:tt) => {
        impl<const M: i64> $trait for ModInt<M> {
            type Output = Self;
            #[inline] fn $func(self, rhs: Self) -> Self { Self::new(self.val $op rhs.val) }
        }
    };
}
impl_op!(Add, add, +);
impl_op!(Sub, sub, -);
impl_op!(Mul, mul, *);
impl<const M: i64> Div for ModInt<M> {
    type Output = Self;
    #[inline]
    fn div(self, rhs: Self) -> Self {
        self * rhs.inv()
    }
}
macro_rules! impl_assign {
    ($trait:ident,$func:ident,$op:tt) => {
        impl<const M: i64> $trait for ModInt<M> {
            #[inline]
            fn $func(&mut self, rhs: Self) {
                *self = *self $op rhs;
            }
        }
    };
}
impl_assign!(AddAssign, add_assign, +);
impl_assign!(SubAssign, sub_assign, -);
impl_assign!(MulAssign, mul_assign, *);
impl_assign!(DivAssign, div_assign, /);

// ======== 2. Rll : Fp(√5) 拡大体 ===========================================

type Mint = ModInt<MOD>;

#[derive(Clone, Copy, Debug, Default, Eq, PartialEq)]
struct Rll {
    x: Mint,
    y: Mint,
}
impl Rll {
    #[inline]
    fn new<X: Into<i64>, Y: Into<i64>>(x: X, y: Y) -> Self {
        Self {
            x: Mint::new(x),
            y: Mint::new(y),
        }
    }
}
impl From<i64> for Rll {
    fn from(v: i64) -> Self {
        Self::new(v, 0)
    }
}
impl From<Mint> for Rll {
    fn from(v: Mint) -> Self {
        Self {
            x: v,
            y: Mint::default(),
        }
    }
}
// ---- 四則演算 ----
impl Add for Rll {
    type Output = Self;
    #[inline]
    fn add(self, rhs: Self) -> Self {
        Self {
            x: self.x + rhs.x,
            y: self.y + rhs.y,
        }
    }
}
impl AddAssign for Rll {
    #[inline]
    fn add_assign(&mut self, rhs: Self) {
        *self = *self + rhs;
    }
}
impl Sub for Rll {
    type Output = Self;
    #[inline]
    fn sub(self, rhs: Self) -> Self {
        Self {
            x: self.x - rhs.x,
            y: self.y - rhs.y,
        }
    }
}
impl SubAssign for Rll {
    #[inline]
    fn sub_assign(&mut self, rhs: Self) {
        *self = *self - rhs;
    }
}
impl Neg for Rll {
    type Output = Self;
    #[inline]
    fn neg(self) -> Self::Output {
        Self {
            x: Mint::default() - self.x,
            y: Mint::default() - self.y,
        }
    }
}
impl Mul for Rll {
    type Output = Self;
    #[inline]
    fn mul(self, rhs: Self) -> Self {
        // (x1 + y1√5)(x2 + y2√5) = (x1x2 + 5y1y2) + (x1y2 + x2y1)√5
        Self {
            x: self.x * rhs.x + self.y * rhs.y * Mint::from(5),
            y: self.x * rhs.y + self.y * rhs.x,
        }
    }
}
impl MulAssign for Rll {
    #[inline]
    fn mul_assign(&mut self, rhs: Self) {
        *self = *self * rhs;
    }
}
impl Div for Rll {
    type Output = Self;
    #[inline]
    fn div(self, rhs: Self) -> Self {
        // 分母 = x^2 - 5y^2
        let denom = rhs.x * rhs.x - rhs.y * rhs.y * Mint::from(5);
        let inv = denom.inv();
        let nx = (self.x * rhs.x - self.y * rhs.y * Mint::from(5)) * inv;
        let ny = (-self.x * rhs.y + self.y * rhs.x) * inv;
        Self { x: nx, y: ny }
    }
}
impl DivAssign for Rll {
    #[inline]
    fn div_assign(&mut self, rhs: Self) {
        *self = *self / rhs;
    }
}

// ======== 3. 汎用 pow (二分累乗) ==========================================

fn pow<T>(mut base: T, mut exp: u64, one: T) -> T
where
    T: Copy + Mul<Output = T>,
{
    let mut res = one;
    while exp != 0 {
        if exp & 1 == 1 {
            res = res * base;
        }
        base = base * base;
        exp >>= 1;
    }
    res
}
#[inline]
fn rll_pow(base: Rll, exp: u64) -> Rll {
    pow(base, exp, Rll::from(1))
}

// ======== 4. FMT / 畳み込み（rll 専用） ===================================

fn power2_ceil(mut n: usize) -> usize {
    if n == 0 {
        return 1;
    }
    if n & (n - 1) == 0 {
        return n;
    }
    n = n.next_power_of_two();
    n
}

/// 一次元高速変換
fn fmt_impl(f: &[Rll], primitive_root: Rll) -> Vec<Rll> {
    let n = f.len();
    assert!(n.is_power_of_two(), "length must be power of two");
    if n == 1 {
        return vec![f[0]];
    }
    // ξ = primitive_root ^ ((MOD-1)/n)
    let xi = rll_pow(primitive_root, ((MOD - 1) as usize / n) as u64);

    let mut trans = f.to_vec();
    let mut stored = vec![Rll::default(); n];

    let log_n = n.trailing_zeros() as usize;
    // powers of ξ^2, ξ^4, ...
    let mut mod_xi_2s = Vec::with_capacity(log_n);
    let mut power_2s = Vec::with_capacity(log_n);
    mod_xi_2s.push(xi);
    power_2s.push(1_usize);
    for i in 1..log_n {
        mod_xi_2s.push(mod_xi_2s[i - 1] * mod_xi_2s[i - 1]);
        power_2s.push(1 << i);
    }

    for e in 0..log_n {
        let mod_xi = mod_xi_2s[log_n - e - 1];
        let skip = power_2s[log_n - e - 1];
        stored[..].clone_from_slice(&trans);
        let mut power_of_xi = Rll::from(1);
        for i in 0..(n / skip) {
            for start in 0..skip {
                let idx = start + skip * i;
                let res_i = i % (n / skip / 2);
                let stored_idx = start + skip * res_i * 2;
                trans[idx] = stored[stored_idx] + stored[stored_idx + skip] * power_of_xi;
            }
            power_of_xi *= mod_xi;
        }
    }
    trans
}

fn prim_root() -> Rll {
    Rll {
        x: Mint::new(3),
        y: Mint::default(),
    }
}
fn inv_prim_root() -> Rll {
    Rll {
        x: Mint::new(332_748_118),
        y: Mint::default(),
    }
}

fn fmt(f: &[Rll]) -> Vec<Rll> {
    fmt_impl(f, prim_root())
}
fn inv_fmt(f: &[Rll]) -> Vec<Rll> {
    let mut v = fmt_impl(f, inv_prim_root());
    let inv_n = Rll::from(1) / Rll::from(f.len() as i64);
    for x in &mut v {
        *x *= inv_n;
    }
    v
}

/// rll 用畳み込み (長さは自動で 2 の冪に丸める)
fn convolution(a: &[Rll], b: &[Rll]) -> Vec<Rll> {
    let need = a.len() + b.len() - 1;
    let n = power2_ceil(need);
    let mut fa = vec![Rll::default(); n];
    let mut fb = vec![Rll::default(); n];
    fa[..a.len()].clone_from_slice(a);
    fb[..b.len()].clone_from_slice(b);
    let mut fa = fmt(&fa);
    let fb = fmt(&fb);
    for (x, y) in fa.iter_mut().zip(fb.iter()) {
        *x *= *y;
    }
    let mut c = inv_fmt(&fa);
    c.truncate(need);
    c
}

// ======== 5. 汎用 Polynomial<T> （必要最小限） ============================

#[derive(Clone, Debug)]
struct Polynomial<T> {
    coefs: Vec<T>,
}
impl<T: Copy + Default> Polynomial<T> {
    fn new_constant(c: T) -> Self {
        Self { coefs: vec![c] }
    }
    fn zero_polynomial(n: usize) -> Self {
        Self {
            coefs: vec![T::default(); n],
        }
    }
    pub fn from_vec(coefs: Vec<T>) -> Self {
        Self { coefs }
    }
    #[inline]
    fn coef_num(&self) -> usize {
        self.coefs.len()
    }
    fn resize(&mut self, n: usize) {
        self.coefs.resize(n, T::default());
    }
    fn mod_xn(&mut self, n: usize) {
        if self.coefs.len() > n {
            self.coefs.truncate(n);
        }
    }
    fn zero_trim(&mut self)
    where
        T: PartialEq,
    {
        while self.coefs.len() > 1 && *self.coefs.last().unwrap() == T::default() {
            self.coefs.pop();
        }
    }
}
use std::ops::{Index, IndexMut};

impl<T> Polynomial<T>
where
    T: Copy + Default,
{
    /// **安全な読み出し**（範囲外なら `T::default()` を **値として** 返す）
    #[inline]
    fn coef(&self, idx: usize) -> T {
        if idx < self.coefs.len() {
            self.coefs[idx]
        } else {
            T::default()
        }
    }
}

impl<T: Copy> Index<usize> for Polynomial<T> {
    type Output = T;
    #[inline]
    fn index(&self, idx: usize) -> &Self::Output {
        &self.coefs[idx] // 範囲外なら panic （標準 slice と同じ挙動）
    }
}
impl<T: Copy + Default> IndexMut<usize> for Polynomial<T> {
    #[inline]
    fn index_mut(&mut self, idx: usize) -> &mut Self::Output {
        if idx >= self.coef_num() {
            self.coefs.resize(idx + 1, T::default());
        }
        &mut self.coefs[idx]
    }
}
// ---- 加算・減算・単項マイナス --------------------------------------------
impl<T> Add for Polynomial<T>
where
    T: Copy + Default + Add<Output = T> + AddAssign + PartialEq,
{
    type Output = Self;
    fn add(self, rhs: Self) -> Self {
        let n = self.coef_num().max(rhs.coef_num());
        let mut res = Self::zero_polynomial(n);
        for i in 0..n {
            res[i] = T::default();
            if i < self.coef_num() {
                res[i] += self[i];
            }
            if i < rhs.coef_num() {
                res[i] += rhs[i];
            }
        }
        res
    }
}
impl<T> Sub for Polynomial<T>
where
    T: Copy + Default + Sub<Output = T> + Add<Output = T> + SubAssign + PartialEq,
{
    type Output = Self;
    fn sub(self, rhs: Self) -> Self {
        let n = self.coef_num().max(rhs.coef_num());
        let mut res = Self::zero_polynomial(n);
        for i in 0..n {
            res[i] = T::default();
            if i < self.coef_num() {
                res[i] = res[i] + self[i];
            }
            if i < rhs.coef_num() {
                res[i] = res[i] - rhs[i];
            }
        }
        res
    }
}
impl<T> Neg for Polynomial<T>
where
    T: Copy + Default + Neg<Output = T>,
{
    type Output = Self;
    fn neg(mut self) -> Self::Output {
        for x in &mut self.coefs {
            *x = -*x;
        }
        self
    }
}
// ---- 乗算（rll だけ高速畳み込み、その他は O(n^2)） ------------------------
impl Mul for Polynomial<Rll> {
    type Output = Self;
    fn mul(self, rhs: Self) -> Self {
        Self {
            coefs: convolution(&self.coefs, &rhs.coefs),
        }
    }
}

// ======== 6. 問題固有のロジック ==========================================

/// 整数べき乗（Rll）
fn rll_pow_i64(base: Rll, exp: i64) -> Rll {
    rll_pow(base, exp as u64)
}

/// 再帰的に F を構成
fn construct_f(c1: Rll, c2: Rll, d: Rll, m: i64) -> Polynomial<Rll> {
    if m == 0 {
        return Polynomial::new_constant(Rll::from(1));
    }
    if m % 2 == 0 {
        let poly1 = construct_f(c1, c2, d, m / 2);
        let mut poly2 = Polynomial::<Rll>::zero_polynomial(poly1.coef_num());
        let dm = rll_pow_i64(d, m / 2);
        let mut dmi = Rll::from(1);
        for i in 0..poly1.coef_num() {
            poly2[i] = dmi * poly1[i];
            dmi *= dm;
        }
        let mut f = poly1.clone() * poly2;
        f.zero_trim();
        return f;
    }
    let poly1 = construct_f(c1, c2, d, m - 1);
    let poly2 = Polynomial::<Rll>::from_vec(vec![c2, c1 * rll_pow_i64(d, m)]);
    let mut f = poly1 * poly2;
    f.zero_trim();
    f
}

fn chirp_z_transform(f: &Polynomial<Rll>, w: Rll, r: usize) -> Vec<Rll> {
    let ys_size = f.coef_num();
    let vs_size = ys_size + r;
    // w^i
    let mut wis = vec![Rll::default(); vs_size];
    let mut wi = Rll::from(1);
    for x in &mut wis {
        *x = wi;
        wi *= w;
    }
    // w^{i(i+1)/2}
    let mut wtis = vec![Rll::default(); vs_size];
    let mut wti = Rll::from(1);
    for (i, x) in wtis.iter_mut().enumerate() {
        *x = wti;
        wti *= wis[i];
    }
    // ys = f[i] / w^{i(i+1)/2}, 反転
    let mut ys: Vec<Rll> = (0..ys_size).map(|i| f[i] / wtis[i]).collect();
    ys.reverse();
    // vs = w^{i(i+1)/2}
    let vs = wtis.clone();
    let conv = convolution(&ys, &vs);
    (0..r).map(|i| conv[ys_size - 1 + i] / wtis[i]).collect()
}

fn compute_product(c1: Rll, c2: Rll, d: Rll, n: i64) -> Rll {
    // M = floor(√n)
    let mut m = 0_i64;
    while (m + 1) * (m + 1) <= n {
        m += 1;
    }
    let f = construct_f(c1, c2, d, m);
    let dm = rll_pow_i64(d, m);
    let vals = chirp_z_transform(&f, dm, m as usize);

    let mut res = Rll::from(1);
    for v in vals {
        res *= v;
    }
    for i in m * m + 1..=n {
        res *= c1 * rll_pow_i64(d, i) + c2;
    }
    res
}

fn solve(n: i64, x: i64, y: i64) -> Rll {
    let a1 = Rll::from(x);
    let a2 = Rll::from(y);

    let half = Mint::new(1) / Mint::new(2);
    let alpha = Rll::new(half.value(), half.value()); // (1/2, 1/2)
    let beta = Rll::new(half.value(), (-half).value()); // (1/2, -1/2)
    let d = alpha / beta;

    let c1 = (beta * beta * a1 - beta * a2) / (alpha * beta * (beta - alpha));
    let c2 = (-alpha * alpha * a1 + alpha * a2) / (alpha * beta * (beta - alpha));

    let order = (MOD + 1) * 2; // (p+1)*2
    let mut res = Rll::from(1);
    res *= compute_product(c1, c2, d, n % order);
    if n / order > 0 {
        res *= rll_pow_i64(compute_product(c1, c2, d, order), n / order);
    }
    if n % 2 == 0 {
        let betan = rll_pow_i64(beta, n / 2);
        res *= rll_pow_i64(betan, n + 1);
    } else {
        let betan = rll_pow_i64(beta, n);
        res *= rll_pow_i64(betan, (n + 1) / 2);
    }
    res
}

fn main() {
    // solve();

    input! {
        t: i64,
    }
    for _ in 0..t {
        input! {
            n: i64,
            x: i64,
            y: i64,
        }
        let ans = solve(n, x, y);
        println!("{}", ans.x.value());
    }
}
