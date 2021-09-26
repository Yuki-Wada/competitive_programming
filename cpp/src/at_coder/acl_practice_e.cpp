//include
//------------------------------------------
#include <string>
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
#include <complex>

#include <sstream>
#include <iostream>
#include <iomanip>

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <ctime>

// namespace
using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
static const ll MOD = 998244353LL;
static const double PI = 3.14159265358979323846;

// conversion
inline ll toint(string s)
{
	ll v;
	istringstream sin(s);
	sin >> v;
	return v;
}
template <class t>
inline string tostring(t x)
{
	ostringstream sout;
	sout << x;
	return sout.str();
}

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a); (i) < (ll)(b); (i)++)
#define REPD(i, a, b) for (ll i = (ll)(a); (i) < (ll)(b); (i)++)
#define REPI(v, vs) for (auto &v : vs)

//debug
#ifdef LOCAL_ENV
#define DUMP(x) cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" \
					  << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854775807LL

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args)
{
	return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args)
{
	using value_type = std::decay_t<decltype(make_multiple_vector<N - 1, T>(args...))>;
	return vector<value_type>(size, make_multiple_vector<N - 1, T>(args...));
}

template <class EdgeInfo>
struct Graph
{
	using Vertex = ll;
	using Edge = tuple<Vertex, Vertex, EdgeInfo>;
	ll vertex_count;
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
		for (ll i = 0; i < edges.size(); ++i)
		{
			Vertex from, to;
			EdgeInfo info;
			tie(from, to, info) = edges[i];
			adjancency_list[from].emplace_back(from, to, info);
		}
		return move(adjancency_list);
	}

	vector<vector<Vertex>> get_adjacency_list_with_no_info() const
	{
		// 辺の隣接リストを作成
		vector<vector<Vertex>> adjancency_list(vertex_count);
		for (ll i = 0; i < edges.size(); ++i)
		{
			Vertex from, to;
			EdgeInfo info;
			tie(from, to, info) = edges[i];
			adjancency_list[from].emplace_back(to);
		}
		return move(adjancency_list);
	}
};

// 始点 s から終点 t への最大フローを返します。
// 距離 capacities の各要素は非負である必要があります。
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
	auto dijkstra = [&]() -> pair<vector<ll>, vector<ll>> {
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

int solve()
{
	ll N, K;
	cin >> N >> K;
	vector<vector<ll>> masses(N, vector<ll>(N));
	Graph<ll> g_from_1(N);
	REPD(i, 0, N)
		REPD(j, 0, N) cin >> masses[i][j];

	const ll const_big = 1LL << 32LL;

	Graph<pair<ll, ll>> g(N * 2LL + 2LL);
	ll S = N * 2LL, T = N * 2LL + 1LL;
	g.add_edge(S, T, {K, const_big});
	REPD(i, 0, N)
	REPD(j, 0, N) g.add_edge(i, j + N, {1LL, const_big - masses[i][j]});
	REPD(i, 0, N)
	g.add_edge(S, i, {K, 0LL});
	REPD(j, 0, N)
	g.add_edge(j + N, T, {K, 0LL});

	ll min_cost;
	Graph<ll> res_g;
	tie(min_cost, res_g) = min_cost_flow(g, K * N, S, T);

	vector<string> selected(N, string(N, '.'));
	ll from, to, cap;
	REPI(edge, res_g.edges)
	{
		tie(from, to, cap) = edge;
		if (from >= N * 2LL || to >= N * 2LL)
			continue;
		if (cap == 0)
			selected[from][to - N] = 'X';
	}

	cout << K * N * const_big - min_cost << endl;
	REPD(i, 0, N)
		cout << selected[i] << endl;

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();
	// ll t;
	// cin >> t;
	// REPD(i, 0, t) solve();

	return 0;
}
