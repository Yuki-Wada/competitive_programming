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
#include <random>

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
static constexpr ll MOD = 998244353LL;
static constexpr double PI = 3.14159265358979323846;

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

class UnionFindTree
{
private:
	const unsigned elemCount_;
	vector<unsigned> parentNodeNumbers_;
	vector<unsigned> treeDepths_;
	vector<unsigned> setSizes_;
	vector<ll> indexes_;
	ll index_;

public:
	UnionFindTree(unsigned elemCount) : elemCount_(elemCount),
										parentNodeNumbers_(elemCount),
										treeDepths_(elemCount, 0),
										setSizes_(elemCount, 1),
										indexes_(elemCount, -1),
										index_(0)
	{
		for (unsigned i = 0; i < parentNodeNumbers_.size(); ++i)
		{
			parentNodeNumbers_[i] = i;
		}
	}

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

ll N, M;

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
	cin >> N >> M;

	ll1d As(N);
	UnionFindTree uft(N);
	REPD(i, 0, N)
	{
		ll a;
		cin >> a;
		As[i] = a;
	}

	pair1d uvs;
	REPD(i, 0, M)
	{
		ll u, v;
		cin >> u >> v;
		--u, --v;
		if (As[u] == As[v])
			uft.uniteSet(u, v);
		else
			uvs.emplace_back(u, v);
	}

	ll2d edges(N);
	REPD(i, 0, uvs.size())
	{
		auto [u, v] = uvs[i];
		if (As[u] > As[v])
			edges[uft.getRootNode(v)].emplace_back(uft.getRootNode(u));
		else if (As[u] < As[v])
			edges[uft.getRootNode(u)].emplace_back(uft.getRootNode(v));
	}

	auto [_, sorted_nodes] = topological_sort(edges);

	ll start = uft.getRootNode(0);
	ll end = uft.getRootNode(N - 1LL);
	ll1d results(N, -(N + M) * 2LL);
	results[start] = 1;
	for (auto u : sorted_nodes)
		for (auto v : edges[u])
			if (results[uft.getRootNode(u)] > 0)
				results[uft.getRootNode(v)] = max(results[uft.getRootNode(v)], results[uft.getRootNode(u)] + 1LL);

	cout << max(results[end], 0LL) << endl;

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
