pub fn compute_gcd(a: i64, b: i64) -> i64 {
    if b == 0 {
        return a;
    }
    let r = a % b;
    get_gcd(b, r)
}

pub fn compute_bezout(a: i64, b: i64) -> (i64, i64) {
    if b == 0 {
        return (1, 0);
    }
    if a % b == 0_i64 {
        return (0, 1);
    }

    let r = a % b;
    let q = a / b;
    let (px, py) = compute_bezout(b, r);
    let (cx, cy) = (py, px - q * py);

    let x = ((cx % b) + b) % b;
    let y = ((cy % a) + a) % a - a;
    (x, y)
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
