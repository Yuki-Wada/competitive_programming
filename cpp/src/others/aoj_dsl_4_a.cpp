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
			values_[index - 1] += increment;
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
			res += values_[index - 1];
			index -= index & -index;
		}
		return res;
	}
};
using BIT = BinaryIndexedTree<ll>;

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_4_A&lang=ja#
int solve()
{
	ll n;
	cin >> n;

	ll x1, y1, x2, y2;
	auto vec = make_multiple_vector(make_tuple(0LL, 0LL, 0LL, 0LL), n);
	vector<ll> xs, ys;
	xs.reserve(n * 2 + 2);
	ys.reserve(n * 2 + 2);
	REPD(i, 0, n)
	{
		cin >> x1 >> y1 >> x2 >> y2;
		vec[i] = make_tuple(x1, y1, x2, y2);
		xs.emplace_back(x1);
		xs.emplace_back(x2);
		ys.emplace_back(y1);
		ys.emplace_back(y2);
	}
	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());

	vector<BIT> bits(xs.size(), BIT(ys.size() + 1));
	REPI(v, vec)
	{
		tie(x1, y1, x2, y2) = v;
		x1 = distance(xs.begin(), lower_bound(xs.begin(), xs.end(), x1));
		x2 = distance(xs.begin(), lower_bound(xs.begin(), xs.end(), x2));
		y1 = distance(ys.begin(), lower_bound(ys.begin(), ys.end(), y1));
		y2 = distance(ys.begin(), lower_bound(ys.begin(), ys.end(), y2));
		REPD(i, x1, x2)
		{
			bits[i].update(y1, 1);
			bits[i].update(y2, -1);
		}
	}

	ll res = 0;
	REPD(i, 0, xs.size())
	REPD(j, 0, ys.size())
	{
		if (bits[i].query(j) >= 1)
		{
			res += (xs[i + 1] - xs[i]) * (ys[j + 1] - ys[j]);
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
