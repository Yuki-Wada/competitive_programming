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
using pair1d = vector<llpair>;
using pair2d = vector2d<llpair>;

// constant
static const ll MOD = 998244353LL;
static const double PI = 3.14159265358979323846;

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

ll N, M, Q, K;

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

// 頂点点の最短距離を返します。
// パス自体が存在しない場合は -1 を返します。
vector<vector<long long>> floyd_warshall(const Graph<long long> &graph)
{
	using Length = long long;

	// アルゴリズム本体
	unsigned long long N = graph.vertex_count;
	vector<vector<Length>> dists(N, vector<Length>(N, 1LL << 60));
	for (unsigned long long i = 0; i < N; ++i)
	{
		dists[i][i] = 0LL;
	}

	for (unsigned long long i = 0; i < graph.edges.size(); ++i)
	{
		auto [from, to, info] = graph.edges[i];
		dists[from][to] = min(dists[from][to], info);
	}

	for (unsigned long long k = 0; k < N; ++k)
		for (unsigned long long i = 0; i < N; ++i)
			for (unsigned long long j = 0; j < N; ++j)
			{
				dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);
			}

	return dists;
}

vector<vector<ll>> compute_permutations(ll n)
{
	vector<ll> nums(n);
	ll permutation_count = 1LL;
	for (ll i = 0; i < n; ++i)
	{
		nums[i] = i;
		permutation_count *= n + 1LL;
	}

	vector<vector<ll>> permutations;
	permutations.reserve(permutation_count);
	do
	{
		permutations.push_back(nums);
	} while (next_permutation(nums.begin(), nums.end()));

	return permutations;
}
int solve()
{
	cin >> N >> M;

	Graph<ll> g(N);
	vector<tuple<ll, ll, ll>> bridges(M);
	REPD(i, 0, M)
	{
		ll u, v, t;
		cin >> u >> v >> t;
		--u, --v;
		g.add_edge(u, v, t);
		g.add_edge(v, u, t);
		bridges[i] = {u, v, t};
	}

	auto dists = floyd_warshall(g);

	cin >> Q;
	REPD(_, 0, Q)
	{
		ll res = MAX_VALUE;
		cin >> K;
		ll1d B_idxs(K);
		REPD(i, 0, K)
		{
			cin >> B_idxs[i];
			--B_idxs[i];
		}
		auto perms = compute_permutations(K);
		REPI(perm, perms)
		{
			REPD(bits, 0, 1LL << K)
			{
				ll dist = 0LL;
				ll src = 0LL;
				REPD(i, 0, perm.size())
				{
					auto idx = perm[i];
					auto [u, v, t] = bridges[B_idxs[idx]];
					auto bit = bits & (1LL << i);
					if (bit > 0LL)
					{
						auto tmp = u;
						u = v;
						v = tmp;
					}
					dist += dists[src][u] + t;
					src = v;
				}
				dist += dists[src][N - 1LL];
				res = min(res, dist);
			}
		}

		cout << res << endl;
	}

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
	// REPD(i, 0, t)
	// {
	// 	solve();
	// }

	return 0;
}
