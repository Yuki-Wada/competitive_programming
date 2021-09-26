#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__ 0

//include
//------------------------------------------
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>

#include <stdexcept>

using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;

#define MAX_VALUE 9223372036854775807LL

template <class EdgeInfo>
struct Graph
{
	using Vertex = ll;
	using Edge = tuple<Vertex, Vertex, EdgeInfo>;
	ull vertex_count;
	vector<Edge> edges;

	Graph() : vertex_count(0LL), edges(0LL) {}
	Graph(ll vertex_count) : vertex_count(vertex_count), edges(0LL) {}

	void add_edge(Vertex from, Vertex to, EdgeInfo edge_info)
	{
		edges.emplace_back(from, to, edge_info);
	}

	void add_edge(Vertex from, Vertex to)
	{
		edges.emplace_back(from, to, EdgeInfo());
	}

	vector<vector<Edge>> get_adjacency_list() const
	{
		// 辺の隣接リストを作成
		vector<vector<Edge>> adjancency_list(vertex_count);
		for (ull i = 0; i < edges.size(); ++i)
		{
			Vertex from, to;
			EdgeInfo info;
			tie(from, to, info) = edges[i];
			adjancency_list[from].emplace_back(from, to, info);
		}
		return adjancency_list;
	}

	vector<vector<Edge>> get_reverse_adjacency_list() const
	{
		// 辺の隣接リストを作成
		vector<vector<Edge>> adjancency_list(vertex_count);
		for (ull i = 0; i < edges.size(); ++i)
		{
			Vertex from, to;
			EdgeInfo info;
			tie(from, to, info) = edges[i];
			adjancency_list[to].emplace_back(to, from, info);
		}
		return adjancency_list;
	}

	vector<vector<Vertex>> get_adjacency_list_with_no_info() const
	{
		// 辺の隣接リストを作成
		vector<vector<Vertex>> adjancency_list(vertex_count);
		for (ull i = 0; i < edges.size(); ++i)
		{
			Vertex from, to;
			EdgeInfo info;
			tie(from, to, info) = edges[i];
			adjancency_list[from].emplace_back(to);
		}
		return adjancency_list;
	}
};

// グラフの強連結成分を返します。
template <class EdgeInfo>
vector<ll> get_scc(const Graph<EdgeInfo> &graph)
{
	using Vertex = ll;
	using Edge = tuple<Vertex, Vertex, EdgeInfo>;

	// 辺の隣接リストを作成
	ll vertex_count = graph.vertex_count;
	auto adjacency_list = graph.get_adjacency_list();
	auto rev_adjacency_list = graph.get_reverse_adjacency_list();
	// アルゴリズム本体
	struct DFS
	{
		Vertex to;
		ll visit_order;
		vector<pair<ll, ll>> visit_orders;
		vector<ll> component_numbers;

		DFS(ll vertex_count) : visit_order(0),
							   visit_orders(vertex_count, {-1, 0}),
							   component_numbers(vertex_count, -1) {}

		void execute_phase1(Vertex i, const vector<vector<Edge>> &adjacency_list)
		{
			visit_orders[i].first = 0;
			for (ull j = 0; j < adjacency_list[i].size(); ++j)
			{
				tie(ignore, to, ignore) = adjacency_list[i][j];
				if (is_visited_phase1(to))
					continue;
				execute_phase1(to, adjacency_list);
			}
			visit_orders[i] = make_pair(visit_order, i);
			++visit_order;
		}

		bool is_visited_phase1(Vertex i)
		{
			return visit_orders[i].first >= 0;
		}

		void sort_orders()
		{
			sort(visit_orders.begin(), visit_orders.end(), greater<pair<ll, ll>>());
		}

		void execute_phase2(Vertex i, ll component_count, const vector<vector<Edge>> &adjacency_list)
		{
			component_numbers[i] = 0;
			for (ull j = 0; j < adjacency_list[i].size(); ++j)
			{
				tie(ignore, to, ignore) = adjacency_list[i][j];
				if (is_visited_phase2(to))
					continue;
				execute_phase2(to, component_count, adjacency_list);
			}
			component_numbers[i] = component_count;
		}

		bool is_visited_phase2(Vertex i)
		{
			return component_numbers[i] >= 0;
		}
	};

	DFS dfs(vertex_count);

	for (Vertex i = 0; i < vertex_count; ++i)
	{
		if (dfs.is_visited_phase1(i))
			continue;
		dfs.execute_phase1(i, adjacency_list);
	}

	dfs.sort_orders();
	Vertex v;
	ll component_count = 0;
	for (ll i = 0; i < vertex_count; ++i)
	{
		tie(ignore, v) = dfs.visit_orders[i];
		if (dfs.is_visited_phase2(v))
			continue;
		dfs.execute_phase2(v, component_count, rev_adjacency_list);
		++component_count;
	}

	return dfs.component_numbers;
}

template <class EdgeInfo>
struct TwoSAT
{
	using Vertex = ll;

	TwoSAT(ll vertex_count) : _node_count(vertex_count), g(vertex_count * 2LL), _answers(vertex_count) {}

	void add_clause(Vertex from, bool from_b, Vertex to, bool to_b)
	{
		g.add_edge(from * 2LL + (from_b ? 0LL : 1LL), to * 2LL + (to_b ? 1LL : 0LL));
		g.add_edge(to * 2LL + (to_b ? 0LL : 1LL), from * 2LL + (from_b ? 1LL : 0LL));
	}

	bool satisfiable()
	{
		if (_components == nullopt)
			_components = get_scc(g);
		auto &id = _components.value();
		for (ll i = 0; i < _node_count; i++)
		{
			if (id[2 * i] == id[2 * i + 1])
				return false;
			_answers[i] = id[2 * i] < id[2 * i + 1];
		}
		return true;
	}

	std::vector<bool> answer() { return _answers; }

private:
	ll _node_count;
	Graph<EdgeInfo> g;
	optional<vector<ll>> _components;
	vector<bool> _answers;
};

// 始点 s から各点への最短距離を返します。
// パス自体が存在しない場合は -1 を返します。
// 長さが負となる経路が存在しない場合を想定しており、負経路が存在するかは別の方法で検出する必要があります。
pair<vector<ll>, vector<ll>> bellman_ford(const Graph<ll> &graph, ll s, ll iter_count)
{
	using Vertex = ll;
	using Length = ll;

	// アルゴリズム本体
	vector<Length> dists(graph.vertex_count, 1LL << 60);
	vector<Vertex> prev_vertices(graph.vertex_count, -1LL);

	dists[s] = 0LL;
	prev_vertices[s] = s;
	ll from, to, length;
	for (ll i = 0; i + 1 < iter_count; ++i)
	{
		for (ll j = 0; j < graph.edges.size(); ++j)
		{
			auto &edge = graph.edges[j];
			tie(from, to, length) = edge;
			if (dists[to] > dists[from] + length)
			{
				dists[to] = min(dists[to], dists[from] + length);
				prev_vertices[to] = from;
			}
		}
	}

	return {dists, prev_vertices};
}

pair<vector<ll>, vector<ll>> bellman_ford(const Graph<ll> &graph, ll s = 0LL)
{
	return bellman_ford(graph, s, graph.vertex_count);
}

// 始点 s から各点への最短距離を返します。
// パス自体が存在しない場合は -1 を返します。
pair<vector<ll>, vector<ll>> dijkstra(const Graph<ll> &graph, ll s = 0LL)
{
	using Vertex = ll;
	using Length = ll;

	// 辺の隣接リストを作成
	auto adjacency_list = graph.get_adjacency_list();

	// アルゴリズム本体
	using VertexInfo = pair<Length, Vertex>;
	priority_queue<VertexInfo, vector<VertexInfo>, greater<VertexInfo>> queue;
	vector<Length> dists(graph.vertex_count, 1LL << 60);
	vector<Vertex> prev_vertices(graph.vertex_count, -1LL);

	dists[s] = 0LL;
	queue.emplace(dists[s], s);
	prev_vertices[s] = s;
	Vertex v, to;
	Length l, length;
	while (!queue.empty())
	{
		tie(l, v) = queue.top();
		queue.pop();
		if (dists[v] < l)
			continue;
		for (auto &edge : adjacency_list[v])
		{
			tie(ignore, to, length) = edge;
			if (dists[to] > dists[v] + length)
			{
				dists[to] = dists[v] + length;
				queue.emplace(dists[to], to);
				prev_vertices[to] = v;
			}
		}
	}
	for (ll i = 0; i < graph.vertex_count; ++i)
	{
		if (prev_vertices[i] == -1LL)
			dists[i] = -1LL;
	}

	return {dists, prev_vertices};
}

pair<bool, vector<tuple<ll, ll, ll>>> get_minimum_spanning_tree(const Graph<ll> &graph)
{
	class UnionFindTree
	{
	private:
		const unsigned elemCount_;
		vector<unsigned> parentNodeNumbers_;
		vector<unsigned> treeDepths_;
		vector<unsigned> setSizes_;

		// Average Computational Complexity: O(log(elemCount_)))
		unsigned getRootNode(unsigned x)
		{
			if (parentNodeNumbers_[x] == x)
			{
				return x;
			}
			else
			{
				return getRootNode(parentNodeNumbers_[x]);
			}
		}

	public:
		UnionFindTree(unsigned elemCount) : elemCount_(elemCount),
											parentNodeNumbers_(elemCount),
											treeDepths_(elemCount, 0),
											setSizes_(elemCount, 1)
		{
			for (unsigned i = 0; i < parentNodeNumbers_.size(); ++i)
			{
				parentNodeNumbers_[i] = i;
			}
		}

		// Average Computational Complexity: O(log(elemCount_)))
		void uniteSet(unsigned x, unsigned y)
		{
			x = getRootNode(x);
			y = getRootNode(y);
			if (x == y)
			{
				return;
			}

			if (treeDepths_[x] < treeDepths_[y])
			{
				parentNodeNumbers_[x] = y;
				setSizes_[y] = setSizes_[x] + setSizes_[y];
			}
			else
			{
				parentNodeNumbers_[y] = x;
				setSizes_[x] = setSizes_[x] + setSizes_[y];
				if (treeDepths_[x] == treeDepths_[y])
				{
					++treeDepths_[x];
				}
			}
		}

		unsigned getSetSize(unsigned x)
		{
			return setSizes_[getRootNode(x)];
		}

		// Average Computational Complexity: O(log(elemCount_)))
		bool includedInSameSet(unsigned x, unsigned y)
		{
			return getRootNode(x) == getRootNode(y);
		}
	};

	using Vertex = ll;
	using Edge = tuple<Vertex, Vertex, ll>;

	auto edges = graph.edges;
	auto compare = [](const Edge &a, const Edge &b)
	{
		ll a_weight, b_weight;
		tie(ignore, ignore, a_weight) = a;
		tie(ignore, ignore, b_weight) = b;
		if (a_weight != b_weight)
			return a_weight > b_weight;
		return a > b;
	};
	priority_queue<Edge, vector<Edge>, decltype(compare)> q(compare);
	for (auto edge : edges)
	{
		q.emplace(edge);
	}

	UnionFindTree uft(graph.vertex_count);
	Vertex a, b, weight;
	vector<Edge> results;
	results.reserve(graph.vertex_count - 1LL);
	while (!q.empty())
	{
		if (results.size() + 1ULL >= graph.vertex_count)
			break;

		tie(a, b, weight) = q.top();
		q.pop();
		if (uft.includedInSameSet(a, b))
			continue;
		uft.uniteSet(a, b);
		results.emplace_back(a, b, weight);
	}

	if (results.size() + 1ULL >= graph.vertex_count)
		return {true, results};

	return {false, {}};
}

// 始点 s から終点 t への最大フローを返します。
pair<ll, Graph<ll>> edmonds_karp(const Graph<ll> &graph, ll s, ll t)
{
	using Capacity = ll;
	using Vertex = ll;
	using Index = ll;
	struct Edge
	{
		Vertex from, to;
		Capacity capacity;
		Index reverse_index;
		bool is_original;
		Edge() : from(-1LL), to(-1LL), capacity(0LL), reverse_index(-1LL), is_original(false) {}
		Edge(Vertex from, Vertex to, Capacity capacity, Index reverse_index, bool is_original) : from(from), to(to), capacity(capacity), reverse_index(reverse_index), is_original(is_original) {}
	};

	if (s == t)
		throw runtime_error("フローの始点と終点は異なっている必要があります。");

	// 辺の隣接リストを作成
	vector<vector<Edge>> edges(graph.vertex_count);
	Vertex from, to;
	Capacity capacity;
	for (ll i = 0; i < graph.edges.size(); ++i)
	{
		tie(from, to, capacity) = graph.edges[i];
		if (capacity < 0)
			throw runtime_error("グラフの辺の容量は非負である必要があります。");

		edges[from].emplace_back(from, to, capacity, static_cast<ll>(edges[to].size()), true);
		edges[to].emplace_back(to, from, 0LL, static_cast<ll>(edges[from].size()) - 1LL, false);
	}
	auto get_reverse_edge = [&edges](Edge edge) -> auto &
	{
		return edges[edge.to][edge.reverse_index];
	};

	// アルゴリズム本体
	ll max_flow = 0LL;
	while (true)
	{
		// BFS
		queue<Vertex> queue;
		vector<pair<Vertex, Index>> prev_vertices(graph.vertex_count, {-1, 0});

		queue.emplace(s);
		while (prev_vertices[t].first == -1 && !queue.empty())
		{
			Vertex v = queue.front();
			queue.pop();
			for (ll i = 0; i < edges[v].size(); ++i)
			{
				auto &edge = edges[v][i];
				if (edge.capacity == 0 || prev_vertices[edge.to].first != -1)
					continue;
				prev_vertices[edge.to] = make_pair(v, i);
				queue.emplace(edge.to);
			}
		}

		// 最小パスがなければループを抜ける
		if (prev_vertices[t].first == -1)
			break;

		// 最小パスを見つける
		stack<pair<Vertex, Vertex>> path;
		Capacity min_capacity = 1LL << 60;
		Vertex v = t;
		Index idx;
		while (v != s)
		{
			path.emplace(prev_vertices[v]);
			tie(v, idx) = prev_vertices[v];
			min_capacity = min(min_capacity, edges[v][idx].capacity);
		}

		// Capacity を更新
		while (!path.empty())
		{
			tie(v, idx) = path.top();
			auto &edge = edges[v][idx];
			path.pop();
			edge.capacity -= min_capacity;
			get_reverse_edge(edge).capacity += min_capacity;
		}

		max_flow += min_capacity;
	}

	Graph<ll> result(graph.vertex_count);
	for (const auto &edges_from_base_node : edges)
		for (const auto &edge : edges_from_base_node)
		{
			if (edge.is_original)
			{
				result.add_edge(edge.from, edge.to, edge.capacity);
			}
		}

	return {max_flow, result};
}

// 始点 s から終点 t への最大フローを返します。
ll dinic(const Graph<ll> &graph, ll s, ll t)
{
	using Capacity = ll;
	using Vertex = ll;
	using Index = ll;
	struct Edge
	{
		Vertex from, to;
		Capacity capacity;
		Index reverse_index;
		bool is_original;
		Edge() : from(-1LL), to(-1LL), capacity(0LL), reverse_index(-1LL), is_original(false) {}
		Edge(Vertex from, Vertex to, Capacity capacity, Index reverse_index, bool is_original) : from(from), to(to), capacity(capacity), reverse_index(reverse_index), is_original(is_original) {}
	};

	if (s == t)
		throw runtime_error("フローの始点と終点は異なっている必要があります。");

	// 辺の隣接リストを作成
	vector<vector<Edge>> edges(graph.vertex_count);
	Vertex from, to;
	Capacity capacity;
	for (ll i = 0; i < graph.edges.size(); ++i)
	{
		tie(from, to, capacity) = graph.edges[i];
		if (capacity < 0)
			throw runtime_error("グラフの辺の容量は非負である必要があります。");

		edges[from].emplace_back(from, to, capacity, static_cast<ll>(edges[to].size()), true);
		edges[to].emplace_back(to, from, 0LL, static_cast<ll>(edges[from].size()) - 1LL, false);
	}

	vector<ll> dists(graph.vertex_count);
	auto update_dists = [&](Vertex s) -> void
	{
		fill(dists.begin(), dists.end(), -1);
		queue<Vertex> queue;
		dists[s] = 0;
		queue.emplace(s);

		while (!queue.empty())
		{
			Vertex v = queue.front();
			queue.pop();
			for (auto &edge : edges[v])
			{
				if (edge.capacity > 0LL && dists[edge.to] < 0LL)
				{
					dists[edge.to] = dists[v] + 1LL;
					queue.emplace(edge.to);
				}
			}
		}
	};

	struct DFS
	{
		vector<ll> check_counts;
		DFS(ll vertex_count) : check_counts(vertex_count) {}

		void initialize_check_counts()
		{
			fill(check_counts.begin(), check_counts.end(), 0);
		}

		ll execute(Vertex v, Vertex t, ll flow, vector<vector<Edge>> &edges, const vector<ll> &dists)
		{
			if (v == t)
				return flow;

			for (ll &i = check_counts[v]; i < edges[v].size(); ++i)
			{
				Edge &e = edges[v][i];
				if (e.capacity > 0 && dists[v] < dists[e.to])
				{
					ll d = execute(e.to, t, min(flow, e.capacity), edges, dists);
					if (d > 0)
					{
						e.capacity -= d;
						edges[e.to][e.reverse_index].capacity += d;
						return d;
					}
				}
			}

			return 0LL;
		}
	};
	auto dfs = DFS(graph.vertex_count);

	// アルゴリズム本体
	ll max_flow = 0LL;
	while (true)
	{
		// 最小パスを BFS で見つける
		update_dists(s);
		if (dists[t] < 0LL)
			break;

		// Capacity を更新
		ll f;
		dfs.initialize_check_counts();
		while ((f = dfs.execute(s, t, MAX_VALUE, edges, dists)) > 0)
		{
			max_flow += f;
		}
	}

	return max_flow;
}

// 始点 s から終点 t への最小費用流を返します。
pair<ll, Graph<ll>> min_cost_flow(const Graph<pair<ll, ll>> &graph, ll flow, ll s, ll t)
{
	using Capacity = ll;
	using Cost = ll;
	using Vertex = ll;
	using Index = ll;
	struct Edge
	{
		Vertex from, to;
		Capacity capacity;
		Cost cost;
		Index reverse_index;
		bool is_original;
		Edge() : from(-1LL), to(-1LL), capacity(0LL), cost(0LL), reverse_index(-1LL), is_original(false) {}
		Edge(Vertex from, Vertex to, Capacity capacity, Cost cost, Index reverse_index, bool is_original) : from(from), to(to), capacity(capacity), cost(cost), reverse_index(reverse_index), is_original(is_original) {}
	};

	if (s == t)
		throw runtime_error("フローの始点と終点は異なっている必要があります。");

	// 辺の隣接リストを作成
	vector<vector<Edge>> edges(graph.vertex_count);
	Vertex from, to;
	Capacity capacity;
	Cost cost;
	for (ll i = 0; i < graph.edges.size(); ++i)
	{
		forward_as_tuple(from, to, tie(capacity, cost)) = graph.edges[i];
		if (capacity < 0)
			throw runtime_error("グラフの辺の容量は非負である必要があります。");

		edges[from].emplace_back(from, to, capacity, cost, static_cast<ll>(edges[to].size()), true);
		edges[to].emplace_back(to, from, 0LL, -cost, static_cast<ll>(edges[from].size()) - 1LL, false);
	}
	auto get_reverse_edge = [&edges](Edge edge) -> auto &
	{
		return edges[edge.to][edge.reverse_index];
	};

	vector<ll> hs(graph.vertex_count);
	auto dijkstra = [&]() -> pair<vector<ll>, vector<ll>>
	{
		using VertexInfo = pair<Cost, Vertex>;
		priority_queue<VertexInfo, vector<VertexInfo>, greater<VertexInfo>> queue;
		vector<Cost> dists(graph.vertex_count, 1LL << 60);
		vector<Vertex> prev_vertices(graph.vertex_count, -1LL);

		dists[s] = 0LL;
		queue.emplace(dists[s], s);
		prev_vertices[s] = s;
		Vertex v, to;
		Cost c, cost;
		while (!queue.empty())
		{
			tie(c, v) = queue.top();
			queue.pop();
			if (dists[v] < c)
				continue;
			for (auto &edge : edges[v])
			{
				to = edge.to;
				cost = edge.cost;
				if (edge.capacity > 0 && dists[to] > dists[v] + cost + hs[v] - hs[to])
				{
					dists[to] = dists[v] + cost + hs[v] - hs[to];
					queue.emplace(dists[to], to);
					prev_vertices[to] = v;
				}
			}
		}
		for (ll i = 0; i < graph.vertex_count; ++i)
		{
			if (prev_vertices[i] == -1LL)
				dists[i] = -1LL;
		}

		return {dists, prev_vertices};
	};

	// アルゴリズム本体
	ll min_cost = 0LL;
	vector<ll> dists, prev_vertices;
	while (flow > 0LL)
	{
		tie(dists, prev_vertices) = dijkstra();

		// 最小パスがなければループを抜ける
		if (dists[t] == -1LL)
			break;
		for (ll i = 0; i < graph.vertex_count; ++i)
			hs[i] += dists[i];

		// 最小パスを見つける
		Capacity min_capacity = flow;
		stack<ll> path;
		ll curr_vertex = t, prev_vertex = prev_vertices[t];
		path.emplace(curr_vertex);
		do
		{
			curr_vertex = prev_vertex;
			prev_vertex = prev_vertices[curr_vertex];
			path.emplace(curr_vertex);
			for (auto &edge : edges[prev_vertex])
			{
				if (edge.to == curr_vertex)
				{
					min_capacity = min(min_capacity, edge.capacity);
					break;
				}
			}
		} while (path.top() != s);

		// Capacity を更新
		prev_vertex = path.top();
		path.pop();
		while (!path.empty())
		{
			curr_vertex = path.top();
			path.pop();
			for (auto &edge : edges[prev_vertex])
			{
				if (edge.to == curr_vertex)
				{
					edge.capacity -= min_capacity;
					get_reverse_edge(edge).capacity += min_capacity;
					min_cost += edge.cost * min_capacity;
					break;
				}
			}
			prev_vertex = curr_vertex;
		}
		flow -= min_capacity;
	}

	Graph<ll> result(graph.vertex_count);
	for (const auto &edges_from_base_node : edges)
		for (const auto &edge : edges_from_base_node)
		{
			if (edge.is_original)
			{
				result.add_edge(edge.from, edge.to, edge.capacity);
			}
		}

	return {min_cost, result};
}

template <class EdgeInfo>
Graph<EdgeInfo> get_rooted_bfs_tree_graph(const Graph<EdgeInfo> &graph, ll r = 0LL)
{
	Graph<EdgeInfo> rooted_tree(graph.vertex_count);
	auto adjacency_list = graph.get_adjacency_list();

	queue<ll> queue;
	vector<bool> have_checked(graph.vertex_count);

	queue.push(r);
	have_checked[r] = true;
	ll from, to;
	EdgeInfo info;
	while (!queue.empty())
	{
		from = queue.front();
		queue.pop();
		for (auto &edge : adjacency_list[from])
		{
			tie(ignore, to, info) = edge;
			if (have_checked[to])
				continue;
			rooted_tree.add_edge(from, to, info);
			queue.push(to);
			have_checked[to] = true;
		}
	}

	return rooted_tree;
}

class TreeLCACalculator
{
private:
	vector<vector<ll>> parent_by_power2;
	vector<ll> depths;

public:
	TreeLCACalculator(ll node_count, const vector<vector<ll>> &edges, ll s = 0LL) : parent_by_power2(node_count), depths(node_count)
	{
		ll log_n = 0;
		while ((node_count >> (log_n + 1LL)) > 0)
		{
			++log_n;
		}

		vector<bool> have_checked(node_count, false);
		queue<ll> queue;

		queue.emplace(s);
		depths[s] = 0;
		parent_by_power2[s].resize(log_n + 2LL, s);
		have_checked[s] = true;

		ll from, to;
		while (!queue.empty())
		{
			from = queue.front();
			queue.pop();

			for (auto &edge : edges[from])
			{
				to = edge;
				if (have_checked[to])
					continue;

				depths[to] = depths[from] + 1;
				parent_by_power2[to].resize(log_n + 2LL, s);
				parent_by_power2[to][0] = from;
				for (ll i = 0; i + 1 < log_n + 2LL; ++i)
				{
					parent_by_power2[to][i + 1] = parent_by_power2[parent_by_power2[to][i]][i];
				}
				queue.push(to);
				have_checked[to] = true;
			}
		}
	}

	ll calculate(ll node1, ll node2)
	{

		auto get_index = [](ull a)
		{
			ll index = -1;
			for (; a != 0; a >>= 1)
			{
				++index;
			}
			return index;
		};

		if (depths[node1] < depths[node2])
		{
			auto tmp = node1;
			node1 = node2;
			node2 = tmp;
		}
		if (depths[node1] > depths[node2])
		{
			auto diff = depths[node1] - depths[node2];
			while (diff > 0)
			{
				node1 = parent_by_power2[node1][get_index(diff & -diff)];
				diff -= diff & -diff;
			}
		}

		if (node1 == node2)
			return node1;

		const ll sz = parent_by_power2[node1].size();
		for (ll i = 0; i < sz; ++i)
		{
			if (parent_by_power2[node1][sz - i - 1] != parent_by_power2[node2][sz - i - 1])
			{
				node1 = parent_by_power2[node1][sz - i - 1];
				node2 = parent_by_power2[node2][sz - i - 1];
			}
		}

		return parent_by_power2[node1][0];
	}
};

template <class EdgeInfo>
pair<vector<pair<tuple<ll, ll, EdgeInfo>, string>>, vector<pair<ll, ll>>>
get_euler_tour(const Graph<EdgeInfo> &rooted_tree, ll r)
{
	using Vertex = ll;
	using Edge = tuple<Vertex, Vertex, EdgeInfo>;
	auto adjacent_list = rooted_tree.get_adjacency_list();

	// DFS
	struct EulerTourCalculator
	{
		const vector<vector<Edge>> adjacency_list;
		vector<bool> have_checked;
		vector<Edge> prev_edges;
		vector<pair<Edge, string>> euler_tour;

		EulerTourCalculator(const vector<vector<Edge>> &adjacency_list, ll r) : adjacency_list(adjacency_list),
																				have_checked(adjacency_list.size(), false),
																				prev_edges(adjacency_list.size())
		{
			have_checked[r] = true;
			get<0>(prev_edges[r]) = -1LL;
			get<1>(prev_edges[r]) = r;
			call(r);
		}

		void call(ll from)
		{
			for (const auto &edge : adjacency_list[from])
			{
				ll to = get<1>(edge);

				if (have_checked[to])
					continue;

				have_checked[to] = true;
				prev_edges[to] = edge;
				euler_tour.emplace_back(edge, "+");
				call(to);
			}
			euler_tour.emplace_back(prev_edges[from], "-");
		}
	};

	auto euler_tour = EulerTourCalculator(adjacent_list, r).euler_tour;
	euler_tour.pop_back();

	vector<pair<ll, ll>> tour_index(rooted_tree.vertex_count, {-1, -1});
	tour_index[r].first = 0LL;
	for (ll i = 0; i < euler_tour.size(); ++i)
	{
		Edge edge;
		string type;
		tie(edge, type) = euler_tour[i];
		ll from = get<0>(edge), to = get<1>(edge);

		if (type == "+" && tour_index[to].first == -1)
		{
			tour_index[to].first = i + 1;
		}
		else if (type == "-" && tour_index[to].second == -1)
		{
			tour_index[to].second = i;
		}
	}

	return {euler_tour, tour_index};
}

#endif
