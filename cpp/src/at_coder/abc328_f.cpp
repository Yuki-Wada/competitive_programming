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

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
static const ll MOD = 998244353LL;
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

// debug
#ifdef LOCAL_ENV
#define DUMP(x) cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" \
					  << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854787LL

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

int solve()
{
	ll N, Q;
	cin >> N >> Q;

	vector<ll> Xs(N);
	UnionFindTree uft(N);

	auto edges = make_multiple_vector(0LL, N, 0LL);
	vector<ll> visited_times = make_multiple_vector(-1LL, N);

	ll a, b, d;
	REPD(i, 0, Q)
	{
		cin >> a >> b >> d;
		--a, --b;

		auto is_effective = true;
		if (uft.includedInSameSet(a, b))
		{
			is_effective = Xs[a] - Xs[b] == d;
		}
		else
		{
			auto a_set_size = uft.getSetSize(a);
			auto b_set_size = uft.getSetSize(b);
			auto idx = a_set_size < b_set_size ? a : b;
			auto diff = Xs[a] - Xs[b] - d;
			diff *= a_set_size < b_set_size ? -1LL : 1LL;

			queue<ll> que;
			que.emplace(idx);
			Xs[idx] += diff;
			visited_times[idx] = i;

			while (!que.empty())
			{
				auto curr_idx = que.front();
				que.pop();
				REPI(n, edges[curr_idx])
				{
					if (visited_times[n] == i)
					{
						continue;
					}
					que.emplace(n);
					Xs[n] += diff;
					visited_times[n] = i;
				}
			}

			uft.uniteSet(a, b);
		}
		edges[a].emplace_back(b);
		edges[b].emplace_back(a);

		if (is_effective)
		{
			cout << i + 1LL << " ";
		}
	}
	cout << endl;
	
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
