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

#define MAX_VALUE 9223372036854775807

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

// 始点 s から終点 t への最大フローを返します。
// 距離 capacities の各要素は非負である必要があります。
double edmonds_karp(const Graph& graph, const vector<double>& capacities, ll s, ll t)
{
	using Capacity = double;
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
	Capacity max_flow = 0LL;
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

ll edmonds_karp(const Graph& graph, const vector<double>& capacities)
{
	return edmonds_karp(graph, capacities, 0LL, graph.vertex_count - 1LL);
}

int solve() {
	ll N, M;
	cin >> N >> M;

	vector<ll> Ss(N);
	vector<ll> Ts(M);
	REPD(i, 0, N) cin >> Ss[i];
	REPD(i, 0, M) cin >> Ts[i];

	Graph g(N + M + 2);
	vector<double> capacities;
	ll K, A;
	REPD(i, 0, N) {
		cin >> K;
		REPD(j, 0, K) {
			cin >> A;
			--A;
			g.add_edge({i + 1, A + N + 1});
			capacities.emplace_back(MAX_VALUE);
		}
	}
	REPD(i, 0, N) {
		g.add_edge({0, i + 1});
		capacities.emplace_back(Ss[i]);
	}

	double low = 0.0, high = double(100 * N), mid = (low + high) / 2.0;
	double sum_S = 0.0;
	REPD(i, 0, N) sum_S += double(Ss[i]);	
	ll begin_idx = capacities.size();
	REPD(i, 0, M) {
		g.add_edge({i + N + 1, M + N + 1});
		capacities.emplace_back(double(Ts[i]) * mid);
	}
	while (high - low > 1e-10) {
		double flow = edmonds_karp(g, capacities);
		flow -= sum_S;
		if (flow < -1e-12) low = mid;
		else high = mid;
		mid = (low + high) / 2.0;

		REPD(i, 0, M) capacities[begin_idx + i] = double(Ts[i]) * mid;
	}

	cout << setprecision(6) << mid << endl;

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
