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
static const ll MOD = 1000000007LL;
// static const ll MOD = (1LL << 61LL) - 1LL;
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

template <class T, class... Args>
auto make_multiple_vector(T default_value)
{
	return T(default_value);
}

template <class T, class... Args>
auto make_multiple_vector(T default_value, ull size, Args... args)
{
	using value_type = std::decay_t<decltype(make_multiple_vector<T>(default_value, args...))>;
	return vector<value_type>(size, make_multiple_vector<T>(default_value, args...));
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
		return adjancency_list;
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
		return adjancency_list;
	}
};

// 始点 s から終点 t への最大フローを返します。
ll edmonds_karp(const Graph<ll> &graph, ll s, ll t)
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
		vector<Edge *> prev_vertices(graph.vertex_count, nullptr);

		queue.emplace(s);
		while (prev_vertices[t] == nullptr && !queue.empty())
		{
			Vertex v = queue.front();
			queue.pop();
			for (auto &edge : edges[v])
			{
				if (edge.capacity == 0 || prev_vertices[edge.to] != nullptr)
					continue;
				prev_vertices[edge.to] = &edge;
				queue.emplace(edge.to);
			}
		}

		// 最小パスがなければループを抜ける
		if (prev_vertices[t] == nullptr)
			break;

		// 最小パスを見つける
		stack<Edge *> path;
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
			auto &edge = *path.top();
			path.pop();
			edge.capacity -= min_capacity;
			get_reverse_edge(edge).capacity += min_capacity;
		}

		max_flow += min_capacity;
	}

	return max_flow;
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
	auto update_dists = [&](Vertex s) -> void {
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

int solve()
{
	ll N;
	cin >> N;

	auto masses = make_multiple_vector('.', N, N);
	REPD(i, 0, N)
	REPD(j, 0, N)
	{
		cin >> masses[i][j];
		if ((i + j) % 2 == 1 && masses[i][j] != '?')
		{
			masses[i][j] = masses[i][j] == 'B' ? 'W' : 'B';
		}
	}

	Graph<ll> g(N * N + 2);
	ll S = N * N, T = N * N + 1;
	auto get_node = [&](ll i, ll j) { return i + j * N; };
	REPD(i, 0, N)
	REPD(j, 0, N)
	{
		if (masses[i][j] == 'B')
		{
			g.add_edge(get_node(i, j), T, 1LL << 60LL);
		}
		else if (masses[i][j] == 'W')
		{
			g.add_edge(S, get_node(i, j), 1LL << 60LL);
		}

		if (i > 0)
		{
			g.add_edge(get_node(i, j), get_node(i - 1, j), 1);
		}
		if (i + 1 < N)
		{
			g.add_edge(get_node(i, j), get_node(i + 1, j), 1);
		}
		if (j > 0)
		{
			g.add_edge(get_node(i, j), get_node(i, j - 1), 1);
		}
		if (j + 1 < N)
		{
			g.add_edge(get_node(i, j), get_node(i, j + 1), 1);
		}
	}

	auto res = dinic(g, S, T);
	cout << N * (N - 1) * 2 - res << endl;

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
