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

ll1d top_sort(const ll2d &edges)
{
	vector<bool> is_visited(edges.size(), false);
	ll1d results;
	stack<llpair> s;
	s.push({0LL, 0LL});
	is_visited[0LL] = true;
	while (!s.empty())
	{
		auto [n, type] = s.top();
		s.pop();
		if (type == 0LL)
		{
			s.push({n, 1LL});
			for (auto node : edges[n])
			{
				if (is_visited[node])
					continue;
				s.push({node, 0LL});
				is_visited[node] = true;
			}
		}
		else if (type == 1LL)
		{
			results.emplace_back(n);
		}
	}
	reverse(results.begin(), results.end());

	return results;
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

	pair2d edges(200002LL);
	REPD(i, 0, M)
	{
		ll u, v;
		cin >> u >> v;
		--u, --v;
		if (As[u] == As[v])
			uft.uniteSet(u, v);
		else if (As[u] > As[v])
			edges[As[v]].emplace_back(v, u);
		else if (As[u] < As[v])
			edges[As[u]].emplace_back(u, v);
	}

	ll start = uft.getRootNode(0);
	ll end = uft.getRootNode(N - 1LL);
	ll1d results(N, -(N + M) * 2LL);
	results[start] = 1;
	for (auto color_edges : edges)
		for (auto [u, v] : color_edges)
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
