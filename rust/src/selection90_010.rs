use proconio::input;

//iteratorでの実装

fn main() {
    input! {
        n: usize,
        cps: [(usize, i64); n],
        q: usize,
        lrs: [(usize, usize); q],
    };

    let mut sum1 = vec![0; n + 1];
    let mut sum2 = vec![0; n + 1];

    for i in 0 .. n {
        let (c, p) = cps[i];
        sum1[i + 1] = sum1[i];
        sum2[i + 1] = sum2[i];
        if c == 1 {
            sum1[i + 1] += p;
        }
        else {
            sum2[i + 1] += p;
        }
    }

    for i in 0 .. q {
        let (l, r) = lrs[i];
        print!("{} {}", sum1[r] - sum1[l - 1], sum2[r] - sum2[l - 1]);
        println!();
    }
}
