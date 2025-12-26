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

template <class Integer>
class BinaryIndexedTree
{
private:
	ull maxSize_;
	vector<Integer> values_;

public:
	BinaryIndexedTree(ull maxSize) : maxSize_(maxSize), values_(maxSize_, 0) {}

	void update(ll index, Integer increment)
	{
		if (maxSize_ <= index)
		{
			throw invalid_argument("Index should be less than maxSize.");
		}
		++index;

		while (index <= maxSize_)
		{
			values_[index - 1LL] += increment;
			index += index & -index;
		}
	}

	Integer query(ll index)
	{
		if (index < 0LL)
			return 0;
		if (maxSize_ <= index)
		{
			throw invalid_argument("Index should be less than maxSize.");
		}
		++index;

		Integer res = 0;
		while (index > 0)
		{
			res += values_[index - 1LL];
			index -= index & -index;
		}
		return res;
	}
};
using BIT = BinaryIndexedTree<ll>;

ll solve()
{
	ll n;
	cin >> n;
	ll1d p(n);

	BIT bit(n + 1LL);
	REPD(i, 0, n)
	{
		cin >> p[i];
		p[i]--;
		bit.update(i, 1LL);
	}

	ll1d b(n, -1);
	REPD(i, 0, n)
	{
		auto v = p[n - i - 1LL];
		{
			auto c = bit.query(0LL);
			if (c >= v + 1LL)
			{
				b[n - i - 1LL] = 0LL;
				bit.update(0LL, -1LL);
				continue;
			}
		}
		ll low = 0LL, high = n;
		ll mid = (low + high) / 2LL;
		while (high - low > 1LL)
		{
			auto c = bit.query(mid);
			if (c >= v + 1LL)
			{
				high = mid;
			}
			else
			{
				low = mid;
			}
			mid = (low + high) / 2LL;
		}
		b[n - i - 1LL] = high;
		bit.update(high, -1LL);
	}

	ll1d a(n);
	REPD(i, 0, n)
	{
		a[b[i]] = i + 1LL;
	}

	REPD(i, 0, n)
	{
		cout << a[i];
		if (i + 1LL < n)
			cout << " ";
		else
			cout << endl;
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
