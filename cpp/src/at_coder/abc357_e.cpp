// include
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

// debug
#ifdef LOCAL_ENV
#define DUMP(x) cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" \
					  << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854787LL

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
		vector<vector<Edge>> adjacency_list(vertex_count);
		for (ull i = 0; i < edges.size(); ++i)
		{
			Vertex from, to;
			EdgeInfo info;
			tie(from, to, info) = edges[i];
			adjacency_list[from].emplace_back(from, to, info);
		}
		return adjacency_list;
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
pair<vector<ll>, ll> get_scc(const Graph<EdgeInfo> &graph)
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

	return {dfs.component_numbers, component_count};
}

pair<bool, vector<ll>> topological_sort(const vector<vector<ll>> &edges)
{
	struct DFS
	{
		static bool visit(ll node, const vector<vector<ll>> &edges, vector<ll> &status, vector<ll> &result)
		{
			if (status[node] == 1)
				return false;
			if (status[node] == 0)
			{
				status[node] = 1;
				for (ull i = 0; i < edges[node].size(); ++i)
				{
					if (!visit(edges[node][i], edges, status, result))
						return false;
				}
				status[node] = 2;
				result.emplace_back(node);
			}

			return true;
		}
	};

	vector<ll> result;
	vector<ll> status(edges.size());
	for (ull i = 0; i < edges.size(); ++i)
	{
		if (status[i] == 0 && !DFS::visit(i, edges, status, result))
			return make_pair(false, vector<ll>());
	}
	reverse(result.begin(), result.end());

	return make_pair(true, result);
}

int solve()
{
	ll N;
	cin >> N;

	Graph<ll> g(N);
	ll a;
	REPD(i, 0, N)
	{
		cin >> a;
		g.add_edge(i, a - 1LL);
	}
	auto [scc, component_count] = get_scc(g);
	auto edges = g.get_adjacency_list_with_no_info();
	auto component_graph = make_multiple_vector(0LL, component_count, 0LL);
	auto component_sizes = make_multiple_vector(0LL, component_count);
	REPD(i, 0, N)
	{
		auto src_scc = scc[i];
		REPI(to, edges[i])
		{
			auto dst_scc = scc[to];
			if (src_scc != dst_scc)
			{
				component_graph[dst_scc].push_back(src_scc);
			}
		}
		++component_sizes[src_scc];
	}
	auto topological_orders = topological_sort(component_graph);
	auto accum_counts = make_multiple_vector(0LL, component_count);

	ll res = 0;
	REPI(order, topological_orders.second)
	{
		accum_counts[order] += component_sizes[order];
		res += component_sizes[order] * (accum_counts[order]);
		REPI(to, component_graph[order])
		{
			accum_counts[to] += accum_counts[order];
		}
	}
	cout << res << endl;

	return 0;
}

// main function
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
