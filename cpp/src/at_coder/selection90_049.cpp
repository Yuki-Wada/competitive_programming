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

pair<bool, vector<tuple<ll, ll, ll>>> get_minimum_spanning_tree(const Graph<ll> &graph)
{
	class UnionFindTree
	{
	private:
		const unsigned elemCount_;
		vector<unsigned> parentNodeNumbers_;
		vector<unsigned> treeDepths_;
		vector<unsigned> setSizes_;

		// Average Computational Complexity: O(log(elemCount_)))
		unsigned getRootNode(unsigned x)
		{
			if (parentNodeNumbers_[x] == x)
			{
				return x;
			}
			else
			{
				return getRootNode(parentNodeNumbers_[x]);
			}
		}

	public:
		UnionFindTree(unsigned elemCount) : elemCount_(elemCount),
											parentNodeNumbers_(elemCount),
											treeDepths_(elemCount, 0),
											setSizes_(elemCount, 1)
		{
			for (unsigned i = 0; i < parentNodeNumbers_.size(); ++i)
			{
				parentNodeNumbers_[i] = i;
			}
		}

		// Average Computational Complexity: O(log(elemCount_)))
		void uniteSet(unsigned x, unsigned y)
		{
			x = getRootNode(x);
			y = getRootNode(y);
			if (x == y)
			{
				return;
			}

			if (treeDepths_[x] < treeDepths_[y])
			{
				parentNodeNumbers_[x] = y;
				setSizes_[y] = setSizes_[x] + setSizes_[y];
			}
			else
			{
				parentNodeNumbers_[y] = x;
				setSizes_[x] = setSizes_[x] + setSizes_[y];
				if (treeDepths_[x] == treeDepths_[y])
				{
					++treeDepths_[x];
				}
			}
		}

		unsigned getSetSize(unsigned x)
		{
			return setSizes_[getRootNode(x)];
		}

		// Average Computational Complexity: O(log(elemCount_)))
		bool includedInSameSet(unsigned x, unsigned y)
		{
			return getRootNode(x) == getRootNode(y);
		}
	};

	using Vertex = ll;
	using Edge = tuple<Vertex, Vertex, ll>;

	auto edges = graph.edges;
	auto compare = [](const Edge &a, const Edge &b)
	{
		ll a_weight, b_weight;
		tie(ignore, ignore, a_weight) = a;
		tie(ignore, ignore, b_weight) = b;
		if (a_weight != b_weight)
			return a_weight > b_weight;
		return a > b;
	};
	priority_queue<Edge, vector<Edge>, decltype(compare)> q(compare);
	for (auto edge : edges)
	{
		q.emplace(edge);
	}

	UnionFindTree uft(graph.vertex_count);
	Vertex a, b, weight;
	vector<Edge> results;
	results.reserve(graph.vertex_count - 1LL);
	while (!q.empty())
	{
		if (results.size() + 1ULL >= graph.vertex_count)
			break;

		tie(a, b, weight) = q.top();
		q.pop();
		if (uft.includedInSameSet(a, b))
			continue;
		uft.uniteSet(a, b);
		results.emplace_back(a, b, weight);
	}

	if (results.size() + 1ULL >= graph.vertex_count)
		return {true, results};

	return {false, {}};
}

int solve()
{
	ll n, m;
	cin >> n >> m;

	ll c, l, r;
	Graph<ll> g1(n + 1);
	REPD(i, 0, m)
	{
		cin >> c >> l >> r;
		--l;
		g1.add_edge(l, r, c);
	}

	ll res = -1;

	bool is_ok;
	vector<tuple<ll, ll, ll>> tree;
	tie(is_ok, tree) = get_minimum_spanning_tree(g1);
	if (is_ok)
	{
		res = 0;
		REPI(e, tree)
		{
			tie(ignore, ignore, c) = e;
			res += c;
		}
	}

	cout << res << endl;

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
