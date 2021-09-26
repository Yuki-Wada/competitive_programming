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

int solve()
{
	ll N, D;
	cin >> N >> D;
	ll X[N], Y[N];
	for (int i = 0; i < N; i++)
	{
		cin >> X[i] >> Y[i];
	}
	TwoSAT<ll> ts(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			ll pat1 = abs(X[i] - X[j]);
			ll pat2 = abs(X[i] - Y[j]);
			ll pat3 = abs(Y[i] - X[j]);
			ll pat4 = abs(Y[i] - Y[j]);
			if (pat1 < D)
				ts.add_clause(i, true, j, true);
			if (pat2 < D)
				ts.add_clause(i, true, j, false);
			if (pat3 < D)
				ts.add_clause(i, false, j, true);
			if (pat4 < D)
				ts.add_clause(i, false, j, false);
		}
	}
	if (ts.satisfiable())
	{
		cout << "Yes" << endl;
		vector<bool> v = ts.answer();
		for (ull i = 0; i < v.size(); i++)
		{
			if (!v[i])
				cout << X[i] << endl;
			else
				cout << Y[i] << endl;
		}
	}
	else
		cout << "No" << endl;

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