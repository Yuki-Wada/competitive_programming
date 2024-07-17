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

class Solver
{
private:
	ll N;
	ll M;
	vector<ll> As;
	UnionFindTree uft;
	vector<tuple<ll, ll, ll>> edges;

public:
	Solver(vector<ll> As, ll M) : N(As.size()), M(M), As(As), uft(N), edges()
	{
		for (ll i = 0; i < N; ++i)
		{
			for (ll j = i + 1; j < N; ++j)
			{
				auto score = calc_score(As[i], As[j]);
				edges.emplace_back(score, i, j);
			}
		}
	}

	ll get_power(ll base, ull exponential)
	{
		ll result = 1LL;
		while (exponential >= 1LL)
		{
			if (exponential & 1LL)
			{
				result = result * base;
				result %= M;
			}
			base = base * base;
			base %= M;
			exponential >>= 1LL;
		}

		return result;
	}

	ll calc_score(ll x, ll y)
	{
		ll res = get_power(x, y) + get_power(y, x);
		res %= M;
		return res;
	}

	ll solve()
	{
		sort(edges.begin(), edges.end(), greater<tuple<ll, ll, ll>>());

		ll res = 0;
		ll add_count = 0;
		for (ll i = 0; i < edges.size(); ++i)
		{
			if (add_count > N)
			{
				break;
			}
			auto [score, l, r] = edges[i];
			if (!uft.includedInSameSet(l, r))
			{
				res += score;
				uft.uniteSet(l, r);
				add_count += 1;
			}
		}
		return res;
	}
};

int solve()
{
	ll N, M;
	cin >> N >> M;
	vector<ll> As(N);
	for (ll i = 0; i < N; ++i)
	{
		cin >> As[i];
	}

	auto solver = Solver(As, M);
	cout << solver.solve() << endl;

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
	// REPD(i, 0, t) solve();

	return 0;
}
