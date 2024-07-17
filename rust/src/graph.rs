mod dijkstra {
    use std::cmp::Reverse;
    use std::collections::BinaryHeap;

    const INF: usize = 1_000_000_000 + 7;

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
