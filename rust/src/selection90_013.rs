#![allow(unused_imports, dead_code, non_snake_case)]
use std::cmp::*;
use std::collections::*;
use proconio::{input, marker::{Chars, Bytes, Usize1}};


const INF: usize = 1000000007;

fn main() {
    input! {
        n: usize,
        m: i64,
    }

    let mut g = vec![vec![]; n];
    for _ in 0..m {
        input! {
            mut a: usize,
            mut b: usize,
            c: usize,
        }
        a -= 1;
        b -= 1;
        g[a].push(dijkstra::Edge::new(b, c));
        g[b].push(dijkstra::Edge::new(a, c))
    }

    let dist0 = dijkstra::dijkstra(&g, 0);
    let distn = dijkstra::dijkstra(&g, n - 1);

	for i in 0..n {
		println!("{}", dist0[i] + distn[i]);
    }

}




mod dijkstra {
    use std::cmp::Reverse;
    use std::collections::BinaryHeap;

    #[derive(Debug, Clone, Copy)]
    pub struct Edge {
        to: usize,
        weight: usize,
    }

    impl Edge {
        pub fn new(to: usize, weight: usize) -> Edge {
            Edge { to, weight }
        }
    }

    pub fn dijkstra(graph: &Vec<Vec<Edge>>, start: usize) -> Vec<usize> {
        const INF: usize = 1_000_000_000 + 7;
        let size = graph.len();
        let mut queue = BinaryHeap::new();
        let mut dist = vec![INF; size];

        queue.push(Reverse((0, start)));
        dist[start] = 0;

        while !queue.is_empty() {
            let Reverse((d, v)) = queue.pop().unwrap();
            if dist[v] < d {
                continue;
            }
            for Edge { to, weight } in &graph[v] {
                if dist[*to] > dist[v] + *weight {
                    dist[*to] = dist[v] + *weight;
                    queue.push(Reverse((dist[*to], *to)));
                }
            }
        }

        dist
    }
}
