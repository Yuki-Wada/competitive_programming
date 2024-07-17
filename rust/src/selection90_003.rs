use proconio::input;
use std::collections::VecDeque;

fn maximum_distance_node(edges: &Vec<Vec<usize>>, start: usize) -> (usize, i32) {
    const INF: i32 = 999999;
    let mut dist = vec![INF; edges.len()];
    dist[start] = 0;

    let mut queue = VecDeque::new();
    queue.push_back(start);
    while queue.len() > 0 {
        let now = queue.pop_front().unwrap();
        for &next in edges[now].iter() {
            if dist[next] > dist[now] + 1 {
                dist[next] = dist[now] + 1;
                queue.push_back(next);
            }
        }
    }

    let mut node = 0;
    let mut max_dist = dist[0];
    for (n, &d) in dist.iter().enumerate() {
        if d > max_dist {
            max_dist = d;
            node = n;
        }
    }

    (node, max_dist)
}

fn main() {
    input! {
        n: i32,
    }

    let mut edges = vec![vec![]; n as usize];
    for _ in 0..n-1 {
        input! {
            mut from: usize,
            mut to: usize,
        }

        from -= 1;
        to -= 1;

        edges[from].push(to);
        edges[to].push(from);
    }

    let (node, _) = maximum_distance_node(&edges, 0);
    let (_, res) = maximum_distance_node(&edges, node);

    println!("{}", res + 1);
}
