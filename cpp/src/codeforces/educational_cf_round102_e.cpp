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
inline ll toint(string s) { ll v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a);(i) < (ll)(b);(i)++)
#define REPD(i, a, b) for (ll i = (ll)(a);(i) < (ll)(b);(i)++)
#define REPI(v, vs) for (auto& v : vs)

//debug
#ifdef LOCAL_ENV
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854775807LL

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args) {
    return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args) {
    using value_type = std::decay_t<decltype(make_multiple_vector<N - 1, T>(args...))>;
    return vector<value_type>(size, make_multiple_vector<N - 1, T>(args...));
}

template <class EdgeInfo>
struct Graph {
	using Vertex = ll;
	using Edge = tuple<Vertex, Vertex, EdgeInfo>;
	ll vertex_count;
	vector<vector<Edge>> adjacency_list;

	Graph() : vertex_count(0LL), adjacency_list(0LL) {}
	Graph(ll vertex_count) : vertex_count(vertex_count), adjacency_list(vertex_count) {}

	void add_edge(Vertex from, Vertex to, EdgeInfo edge_info)
	{
		adjacency_list[from].emplace_back(from, to, edge_info);
	}
};


// 始点 s から各点への最短距離を返します。
// パス自体が存在しない場合は -1 を返します。
pair<vector<ll>, vector<ll>> dijkstra(const Graph<ll>& graph, ll s = 0LL)
{
	using Vertex = ll;
	using Length = ll;

	// 辺の隣接リストを作成
	auto adjacency_list = graph.adjacency_list;

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
		if (dists[v] < l) continue;
		for (auto& edge : adjacency_list[v])
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

	return { dists, prev_vertices };
}

int solve() {
	ll n, m;
	cin >> n >> m;

	Graph<ll> g(n * 4LL);
	ll v, u, w;

	auto get_index = [&](ll node, ll min_flag, ll max_flag) {
		return node + min_flag * n + max_flag * n * 2LL;
	};
	REPD(i, 0, m) {
		cin >> v >> u >> w;
		--v, --u;
		g.add_edge(get_index(v, 0, 0), get_index(u, 0, 0), w);
		g.add_edge(get_index(v, 0, 0), get_index(u, 1, 0), w * 2LL);
		g.add_edge(get_index(v, 0, 0), get_index(u, 0, 1), 0);
		g.add_edge(get_index(v, 0, 0), get_index(u, 1, 1), w);
		g.add_edge(get_index(v, 1, 0), get_index(u, 1, 0), w);
		g.add_edge(get_index(v, 1, 0), get_index(u, 1, 1), 0);
		g.add_edge(get_index(v, 0, 1), get_index(u, 0, 1), w);
		g.add_edge(get_index(v, 0, 1), get_index(u, 1, 1), w * 2LL);
		g.add_edge(get_index(v, 1, 1), get_index(u, 1, 1), w);

		g.add_edge(get_index(u, 0, 0), get_index(v, 0, 0), w);
		g.add_edge(get_index(u, 0, 0), get_index(v, 1, 0), w * 2LL);
		g.add_edge(get_index(u, 0, 0), get_index(v, 0, 1), 0);
		g.add_edge(get_index(u, 0, 0), get_index(v, 1, 1), w);
		g.add_edge(get_index(u, 1, 0), get_index(v, 1, 0), w);
		g.add_edge(get_index(u, 1, 0), get_index(v, 1, 1), 0);
		g.add_edge(get_index(u, 0, 1), get_index(v, 0, 1), w);
		g.add_edge(get_index(u, 0, 1), get_index(v, 1, 1), w * 2LL);
		g.add_edge(get_index(u, 1, 1), get_index(v, 1, 1), w);
	}

	auto dists = dijkstra(g, 0).first;
	REPD(i, 1, n) {
		cout << dists[i + n * 3LL] << (i + 1 < n ? " " : "\n");
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
