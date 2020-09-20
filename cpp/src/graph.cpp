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

using Edge = pair<ll, ll>;

struct Graph
{
	using Vertex = ll;
	ll vertex_count;
	vector<Edge> edges;

	Graph() : vertex_count(0LL), edges(0LL) {}
	Graph(ll vertex_count) : vertex_count(vertex_count), edges(0LL) {}

	void add_edge(const Edge& edge)
	{
		edges.emplace_back(edge);
	}

	vector<vector<tuple<Vertex, Vertex>>> get_adjacency_list() const
	{
		using EdgeWithInfo = tuple<Vertex, Vertex>;
		// 辺の隣接リストを作成
		vector<vector<EdgeWithInfo>> adjancency_list(vertex_count);
		for (ll i = 0; i < edges.size(); ++i)
		{
			Vertex from, to;
			tie(from, to) = edges[i];
			adjancency_list[from].emplace_back(from, to);
		}
		return move(adjancency_list);
	}

	template<class EdgeInfo>
	vector<vector<tuple<Vertex, Vertex, EdgeInfo>>> get_adjacency_list(const vector<EdgeInfo>& infos) const
	{
		using EdgeWithInfo = tuple<Vertex, Vertex, EdgeInfo>;
		// 辺の隣接リストを作成
		vector<vector<EdgeWithInfo>> adjancency_list(vertex_count);
		for (ll i = 0; i < edges.size(); ++i)
		{
			Vertex from, to;
			tie(from, to) = edges[i];
			const EdgeInfo& info = infos[i];
			adjancency_list[from].emplace_back(from, to, info);
		}
		return move(adjancency_list);
	}
};

// 始点 s から各点への最短距離を返します。
// パス自体が存在しない場合は -1 を返します。
// 距離 lengths の各要素にとくに条件はありません。
// 長さが負となる経路が存在しない場合を想定しており、負経路が存在するかは別の方法で検出する必要があります。
pair<vector<ll>, vector<ll>> bellman_ford(const Graph& graph, const vector<ll>& lengths, ll s = 0LL)
{
	using Vertex = ll;
	using Length = ll;

	if (graph.edges.size() != lengths.size())
		throw runtime_error("グラフの辺の要素数と辺の長さの要素数は一致している必要があります。");

	// アルゴリズム本体
	vector<Length> dists(graph.vertex_count, 1LL << 60);
	vector<Vertex> prev_vertices(graph.vertex_count, -1LL);

	dists[s] = 0LL;
	prev_vertices[s] = s;
	for (ll i = 0; i + 1 < graph.vertex_count; ++i)
	{
		for (ll j = 0; j < graph.edges.size(); ++j)
		{
			auto& edge = graph.edges[j];
			ll from, to;
			tie(from, to) = edge;
			ll length = lengths[j];
			if (dists[to] > dists[from] + length)
			{
				dists[to] = min(dists[to], dists[from] + length);
				prev_vertices[to] = from;
			}
		}
	}

	return { dists, prev_vertices };
}

// 始点 s から各点への最短距離を返します。
// パス自体が存在しない場合は -1 を返します。
// 距離 lengths の各要素は非負である必要があります。
pair<vector<ll>, vector<ll>> dijkstra(const Graph& graph, const vector<ll>& lengths, ll s = 0LL)
{
	using Vertex = ll;
	using Length = ll;

	if (graph.edges.size() != lengths.size())
		throw runtime_error("グラフの辺の要素数と辺の長さの要素数は一致している必要があります。");

	// 辺の隣接リストを作成
	auto adjacency_list = graph.get_adjacency_list(lengths);

	// アルゴリズム本体
	using VertexInfo = pair<Length, Vertex>;
	priority_queue<VertexInfo, vector<VertexInfo>, greater<VertexInfo>> queue;
	vector<Length> dists(graph.vertex_count, 1LL << 60);
	vector<Vertex> prev_vertices(graph.vertex_count, -1LL);

	dists[s] = 0LL;
	queue.emplace(dists[s], s);
	prev_vertices[s] = s;
	while (!queue.empty())
	{
		Length l;
		Vertex v;
		tie(l, v) = queue.top();
		queue.pop();
		if (dists[v] < l) continue;
		for (auto& edge : adjacency_list[v])
		{
			Vertex to = get<1>(edge);
			Length length = get<2>(edge);
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

	return { dists, prev_vertices };
}

// 始点 s から終点 t への最大フローを返します。
// 距離 capacities の各要素は非負である必要があります。
ll edmonds_karp(const Graph& graph, const vector<ll>& capacities, ll s, ll t)
{
	using Capacity =ll;
	using Vertex = ll;
	using Index = ll;
	struct _Edge
	{
		Vertex from, to;
		Capacity capacity;
		Index reverse_index;
		_Edge() : from(-1LL), to(-1LL), capacity(0LL), reverse_index(-1LL) {}
		_Edge(Vertex from, Vertex to, Capacity capacity, Index reverse_index) :
			from(from), to(to), capacity(capacity), reverse_index(reverse_index) {}
	};

	if (s == t)
		throw runtime_error("フローの始点と終点は異なっている必要があります。");

	if (graph.edges.size() != capacities.size())
		throw runtime_error("グラフの辺の要素数と辺の容量の要素数は一致している必要があります。");

	// 辺の隣接リストを作成
	vector<vector<_Edge>> edges(graph.vertex_count);
	for (ll i = 0; i < graph.edges.size(); ++i)
	{
		Vertex from, to;
		tie(from, to) = graph.edges[i];
		Capacity capacity = capacities[i];
		if (capacity < 0)
			throw runtime_error("グラフの辺の容量は非負である必要があります。");

		edges[from].emplace_back(from, to, capacity, -1LL);
		edges[to].emplace_back(to, from, 0LL, -1LL);
		edges[from].back().reverse_index = static_cast<ll>(edges[to].size()) - 1LL;
		edges[to].back().reverse_index = static_cast<ll>(edges[from].size()) - 1LL;
	}
	auto get_reverse_edge = [&edges](_Edge edge) -> auto & {
		return edges[edge.to][edge.reverse_index];
	};

	// アルゴリズム本体
	ll max_flow = 0LL;
	while (true)
	{
		// BFS
		queue<Vertex> queue;
		vector<_Edge*> prev_vertices(graph.vertex_count, nullptr);

		queue.emplace(s);
		while (prev_vertices[t] == nullptr && !queue.empty())
		{
			Vertex v = queue.front();
			queue.pop();
			for (auto& edge : edges[v])
			{
				if (edge.capacity == 0 || prev_vertices[edge.to] != nullptr) continue;
				prev_vertices[edge.to] = &edge;
				queue.emplace(edge.to);
			}
		}

		// 最小パスがなければループを抜ける
		if (prev_vertices[t] == nullptr) break;

		// 最小パスを見つける
		stack<_Edge*> path;
		Capacity min_capacity = 1LL << 60;
		path.emplace(prev_vertices[t]);
		while (path.top()->from != s)
		{
			min_capacity = min(min_capacity, path.top()->capacity);
			path.emplace(prev_vertices[path.top()->from]);
		}
		min_capacity = min(min_capacity, path.top()->capacity);

		// Capacity を更新
		while (!path.empty())
		{
			auto& edge = *path.top();
			path.pop();
			edge.capacity -= min_capacity;
			get_reverse_edge(edge).capacity += min_capacity;
		}

		max_flow += min_capacity;
	}

	return max_flow;
}

ll edmonds_karp(const Graph& graph, const vector<ll>& capacities)
{
	return edmonds_karp(graph, capacities, 0LL, graph.vertex_count - 1LL);
}

template<class EdgeInfo>
pair<Graph, vector<EdgeInfo>> get_rooted_bfs_tree_graph(const Graph& graph, vector<EdgeInfo>& infos, ll r = 0LL)
{
	Graph rooted_tree(graph.vertex_count);
	auto adjacency_list = graph.get_adjacency_list(infos);

	vector<EdgeInfo> new_infos;

	queue<ll> queue;
	vector<bool> have_checked(graph.vertex_count);

	queue.push(r);
	have_checked[r] = true;
	while (!queue.empty())
	{
		ll from = queue.front();
		queue.pop();
		for (auto& edge : adjacency_list[from])
		{
			ll to;
			EdgeInfo info;
			tie(from, to, info) = edge;
			if (have_checked[to])
				continue;
			rooted_tree.add_edge({ from, to });
			new_infos.emplace_back(info);
			queue.push(to);
			have_checked[to] = true;
		}
	}

	return { rooted_tree, new_infos };
}

class TreeLCACalculator
{
private:
	vector<vector<ll>> parent_by_power2;
	vector<ll> depths;
public:
	TreeLCACalculator(ll node_count, const vector<vector<ll>>& edges, ll s = 0LL) :
		parent_by_power2(node_count), depths(node_count)
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

		while (!queue.empty())
		{
			ll from = queue.front();
			queue.pop();

			for (auto& to : edges[from])
			{
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

	ll calculate(ll node1, ll node2) {

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

template<class EdgeInfo>
pair<vector<pair<tuple<ll, ll, EdgeInfo>, string>>, vector<pair<ll, ll>>>
get_euler_tour(const Graph& rooted_tree, const vector<EdgeInfo>& edge_infos, ll r)
{
	using Vertex = ll;
	using EdgeWithInfo = tuple<Vertex, Vertex, EdgeInfo>;
	auto adjacent_list = rooted_tree.get_adjacency_list(edge_infos);

	// DFS
	struct EulerTourCalculator
	{
		const vector<vector<EdgeWithInfo>> adjacency_list;
		vector<bool> have_checked;
		vector<EdgeWithInfo> prev_edges;
		vector<pair<EdgeWithInfo, string>> euler_tour;

		EulerTourCalculator(const vector<vector<EdgeWithInfo>>& adjacency_list, ll r) :
			adjacency_list(adjacency_list),
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
			for (const auto& edge : adjacency_list[from])
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

	vector<pair<ll, ll>> tour_index(rooted_tree.vertex_count, { -1, -1 });
	tour_index[r].first = 0LL;
	for (ll i = 0; i < euler_tour.size(); ++i)
	{
		EdgeWithInfo edge;
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

	return { euler_tour, tour_index };
}
