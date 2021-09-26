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
pair<ll, Graph<ll>> dinic(const Graph<ll> &graph, ll s, ll t)
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

	Graph<ll> result(graph.vertex_count);
	for (const auto &edges_from_base_node : edges)
		for (const auto &edge : edges_from_base_node)
		{
			if (edge.is_original)
			{
				result.add_edge(edge.from, edge.to, edge.capacity);
			}
		}

	return {max_flow, result};
}

ll N, M;
vector<string> masses;

int d[] = {0, 1, 0, -1};
bool isvalid(int x, int y)
{
	return x >= 0 && x < N && y >= 0 && y < M && masses[x][y] == '.';
}

int solve()
{
	cin >> N >> M;
	masses.resize(N);
	REPD(i, 0, N)
	cin >> masses[i];

	ll S = N * M, T = N * M + 1LL;
	Graph<ll> g(N * M + 2LL);
	REPD(i, 0, N)
	REPD(j, 0, M)
	{
		if (masses[i][j] != '.')
			continue;
		if ((i ^ j) & 1)
			g.add_edge(i * M + j, T, 1);
		else
		{
			g.add_edge(S, i * M + j, 1);
			for (int k = 0; k < 4; ++k)
			{
				int nx = i + d[k], ny = j + d[k ^ 1];
				if (isvalid(nx, ny))
					g.add_edge(i * M + j, nx * M + ny, 1);
			}
		}
	}

	ll max_flow;
	Graph<ll> res_g;
	tie(max_flow, res_g) = dinic(g, S, T);

	ll from, to, cap;
	ll fromi, fromj, toi, toj;
	REPI(edge, res_g.edges)
	{
		tie(from, to, cap) = edge;
		if (from >= N * M || to >= N * M)
			continue;
		if (cap == 1)
			continue;
		fromi = from / M, fromj = from % M;
		toi = to / M, toj = to % M;
		if (fromi == toi)
		{
			if (fromj < toj)
			{
				masses[fromi][fromj] = '>';
				masses[toi][toj] = '<';
			}
			else
			{
				masses[toi][toj] = '>';
				masses[fromi][fromj] = '<';
			}
		}
		else
		{
			if (fromi < toi)
			{
				masses[fromi][fromj] = 'v';
				masses[toi][toj] = '^';
			}
			else
			{
				masses[toi][toj] = 'v';
				masses[fromi][fromj] = '^';
			}
		}
	}

	cout << max_flow << endl;
	REPD(i, 0, N)
	cout << masses[i] << endl;

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
