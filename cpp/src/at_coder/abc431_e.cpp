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

// temporary
#include <atcoder/all>
using namespace atcoder;

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

#define MAX_VALUE 9223372036854775807LL

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;
using llpair = pair<ll, ll>;
template <class T>
using vector2d = vector<vector<T>>;
template <class T>
using vector3d = vector<vector<vector<T>>>;
using ll1d = vector<ll>;
using ll2d = vector2d<ll>;
using ll3d = vector3d<ll>;

// constant
static constexpr ll MOD = 998244353LL;
static constexpr double PI = 3.14159265358979323846;

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args)
{
	return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args)
{
	using value_type = std::decay_t<decltype(make_multiple_vector<N - 1LL, T>(args...))>;
	return vector<value_type>(size, make_multiple_vector<N - 1LL, T>(args...));
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

ll solve()
{
	ll unit = 10000000;
	ll h, w;
	cin >> h >> w;

	Graph<ll> graph((h + 2LL) * (w + 2LL) * 4 + 100);
	for (ll i = 0; i < h; ++i)
	{
		string s;
		cin >> s;
		REPD(j, 0, w)
		{
			auto in_e = ((i + 1LL) * (w + 2LL) + (j + 1LL)) * 4 + 0;
			auto in_w = ((i + 1LL) * (w + 2LL) + (j + 1LL)) * 4 + 1;
			auto in_s = ((i + 1LL) * (w + 2LL) + (j + 1LL)) * 4 + 2;
			auto in_n = ((i + 1LL) * (w + 2LL) + (j + 1LL)) * 4 + 3;

			auto out_e = ((i + 1LL) * (w + 2LL) + (j + 2LL)) * 4 + 1;
			auto out_w = ((i + 1LL) * (w + 2LL) + (j + 0LL)) * 4 + 0;
			auto out_s = ((i + 2LL) * (w + 2LL) + (j + 1LL)) * 4 + 3;
			auto out_n = ((i + 0LL) * (w + 2LL) + (j + 1LL)) * 4 + 2;

			graph.add_edge(in_w, out_e, s[j] == 'A' ? 1LL : unit);
			graph.add_edge(in_s, out_e, s[j] == 'C' ? 1LL : unit);
			graph.add_edge(in_n, out_e, s[j] == 'B' ? 1LL : unit);

			graph.add_edge(in_e, out_w, s[j] == 'A' ? 1LL : unit);
			graph.add_edge(in_s, out_w, s[j] == 'B' ? 1LL : unit);
			graph.add_edge(in_n, out_w, s[j] == 'C' ? 1LL : unit);

			graph.add_edge(in_e, out_s, s[j] == 'C' ? 1LL : unit);
			graph.add_edge(in_w, out_s, s[j] == 'B' ? 1LL : unit);
			graph.add_edge(in_n, out_s, s[j] == 'A' ? 1LL : unit);

			graph.add_edge(in_e, out_n, s[j] == 'B' ? 1LL : unit);
			graph.add_edge(in_w, out_n, s[j] == 'C' ? 1LL : unit);
			graph.add_edge(in_s, out_n, s[j] == 'A' ? 1LL : unit);
		}
	}

	ll start = ((w + 2LL) + 1LL) * 4 + 1;
	ll goal = (h * (w + 2LL) + w + 1LL) * 4 + 1;

	auto [dists, prev_vertices] = dijkstra(graph, start);
	cout << dists[goal] / unit << endl;

	return 0;
}

// main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	// solve();

	ll t;
	cin >> t;

	REPD(i, 0, t)
	{
		solve();
	}

	return 0;
}
