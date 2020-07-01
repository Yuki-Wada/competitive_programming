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
#include <complex>

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
using comp = complex<double>;

const ll MOD = 1000000007LL;
const double PI = 3.14159265358979323846;

//conversion
//------------------------------------------
inline int toint(string s) { int v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// for loop
#define REP(i, n) for ((i) = 0;(i) < (ll)(n);(i)++)

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __line__ << ")" << " " << __file__ << endl

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

int solve() {
	ll i, j, k;

	ll n, m, s;
	cin >> n >> m >> s;
	s = min(s, 2500LL);

	vector<tuple<ll, ll, ll, ll>> uvabs;
	uvabs.reserve(m);
	ll u, v, a, b;
	REP (i, m) {
		cin >> u >> v >> a >> b;
		--u, --v;
		uvabs.emplace_back(u, v, a, b);
	}
	vector<tuple<ll, ll>> cds;
	cds.reserve(n);
	ll c, d;
	REP(i, n) {
		cin >> c >> d;
		cds.emplace_back(c, d);
	}

	Graph g(n * 2501LL);
	vector<ll> lengths;
	REP(i, m) {
		tie(u, v, a, b) = uvabs[i];
		REP(j, 2501LL) {
			if (j < a) continue;
			g.add_edge(Edge(u * 2501LL + j, v * 2501LL + j - a));
			g.add_edge(Edge(v * 2501LL + j, u * 2501LL + j - a));
			lengths.emplace_back(b);
			lengths.emplace_back(b);
		}
	}

	REP(i, n) {
		tie(c, d) = cds[i];
		REP(j, 2500LL) {
			g.add_edge(Edge(i * 2501LL + j, i * 2501LL + min(j + c, 2500LL)));
			lengths.emplace_back(d);
		}
	}

	auto dists = dijkstra(g, lengths, s).first;
	REP(i, n) {
		if (i == 0) continue;
		ll res = 1LL << 60LL;
		REP(j, 2501LL) {
			if (dists[i * 2501LL + j] == -1) continue;
			res = min(res, dists[i * 2501LL + j]);
		}
		cout << res << endl;
	}

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}
