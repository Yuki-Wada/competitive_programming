use proconio::input;

//iteratorでの実装

pub fn get_gcd(mut a: i64, mut b: i64) -> i64 {
    while b != 0 {
        a %= b;
        std::mem::swap(&mut a, &mut b);
    }
    a
}

fn main() {
    input! {
        a: i64,
        b: i64,
    };

    let gcd = get_gcd(a, b);

    if b / gcd > 1000000000000000000 / a {
        print!("Large");
    }
    else {
        print!("{}", b / gcd * a);
    }
    println!();
    }
