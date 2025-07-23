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
