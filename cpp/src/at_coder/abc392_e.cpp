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

public:
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

	UnionFindTree uft(n);
	auto edges = make_multiple_vector<1, tuple<ll, ll, bool>>(0, make_tuple(0LL, 0LL, false));
	REPD(i, 0, m)
	{
		ll a, b;
		cin >> a >> b;
		--a, --b;
		auto residual = uft.includedInSameSet(a, b);
		edges.emplace_back(a, b, residual);
		uft.uniteSet(a, b);
	}

	ll2d node_groups;
	map<ll, ll> node2idx;
	REPD(i, 0, n)
	{
		auto node = uft.getRootNode(i);
		if (node2idx.count(node) == 0)
		{
			node2idx[node] = node2idx.size();
			node_groups.emplace_back(ll1d());
		}
		auto idx = node2idx[node];
		node_groups[idx].emplace_back(i);
	}

	ll2d edge_residuals(node_groups.size());
	REPD(i, 0, m)
	{
		auto [a, b, residual] = edges[i];
		if (residual)
		{
			auto node = uft.getRootNode(a);
			auto idx = node2idx[node];
			edge_residuals[idx].emplace_back(i);
		}
	}
	vector<llpair> edge_counts;
	REPD(i, 0, edge_residuals.size())
	{
		edge_counts.emplace_back(edge_residuals[i].size(), i);
	}
	sort(edge_counts.begin(), edge_counts.end(), greater<llpair>());

	vector<llpair> flatten_edge_residuals;
	REPD(i, 0, edge_residuals.size())
	{
		auto idx = edge_counts[i].second;
		REPD(j, 0, edge_residuals[idx].size())
		{
			flatten_edge_residuals.emplace_back(idx, edge_residuals[idx][j]);
		}
	}

	auto results = make_multiple_vector<1, tuple<ll, ll, ll>>(0, make_tuple(0, 0, 0));
	REPD(i, 1, edge_residuals.size())
	{
		auto [node_idx, edge_idx] = flatten_edge_residuals[i - 1LL];
		auto node = get<0>(edges[edge_idx]);
		auto connect_node_idx = edge_counts[i].second;
		auto connect_node = node_groups[connect_node_idx][0];
		results.emplace_back(edge_idx, node, connect_node);
	}

	cout << results.size() << endl;
	REPD(i, 0, results.size())
	{
		auto [x, y, z] = results[i];
		cout << x + 1LL << " " << y + 1LL << " " << z + 1LL << endl;
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
