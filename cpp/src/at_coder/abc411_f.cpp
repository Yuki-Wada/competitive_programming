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

ll solve()
{
	ll n, m;
	cin >> n >> m;

	vector<pair<ll, ll>> edges(m);
	vector<set<ll>> adj(n);
	REPD(i, 0, m)
	{
		ll u, v;
		cin >> u >> v;
		--u;
		--v;
		edges[i] = make_pair(u, v);
		adj[u].insert(v);
		adj[v].insert(u);
	}

	ll1d pos(n);
	auto pieces = make_multiple_vector<2, ll>(n, 0LL, 0LL);
	REPD(i, 0, n)
	{
		pos[i] = i;
		pieces[i].emplace_back(i);
	}

	ll res = m;
	ll q;
	cin >> q;
	REPD(i, 0, q)
	{
		ll x;
		cin >> x;
		--x;
		auto [u, v] = edges[x];
		auto pos_u = pos[u];
		auto pos_v = pos[v];
		if (pos_u != pos_v)
		{
			if (pieces[pos_u].size() + adj[pos_u].size() <= pieces[pos_v].size() + adj[pos_v].size())
			{
				swap(pos_u, pos_v);
			}
			for (auto iter = pieces[pos_v].begin(); iter != pieces[pos_v].end(); ++iter)
			{
				pieces[pos_u].emplace_back(*iter);
				pos[*iter] = pos_u;
			}
			pieces[pos_v].clear();

			for (auto iter = adj[pos_v].begin(); iter != adj[pos_v].end(); ++iter)
			{
				auto to = *iter;
				if (to == pos_u)
				{
					adj[pos_u].erase(to);
					--res;
				}
				else
				{
					adj[to].erase(pos_v);
					if (adj[pos_u].count(to) >= 1LL)
					{
						--res;
					}
					else
					{
						adj[pos_u].insert(to);
						adj[to].insert(pos_u);
					}
				}
			}
			adj[pos_v].clear();
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

	auto r = solve();

	// ll t;
	// cin >> t;

	// REPD(i, 0, t)
	// {
	// 	auto r = solve();
	// }

	return 0;
}
