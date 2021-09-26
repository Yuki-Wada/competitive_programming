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

int solve()
{
	ll n;
	cin >> n;

	Graph<ll> g(n);
	ll a, b;
	REPD(i, 1, n)
	{
		cin >> a >> b;
		--a, --b;
		g.add_edge(a, b, 1);
		g.add_edge(b, a, 1);
	}

	auto dists = dijkstra(g).first;
	ll cnt = 0;
	REPD(i, 0, n)
	{
		dists[i] %= 2;
		if (dists[i] == 0)
			++cnt;
	}

	ll show_cnt = 0;
	REPD(i, 0, n)
	{
		if ((cnt >= n / 2) ^ (dists[i] == 1))
		{
			cout << i + 1 << endl;
			++show_cnt;
			if (show_cnt >= n / 2)
				break;
		}
	}

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
