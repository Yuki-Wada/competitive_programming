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

int solve()
{
	ll n, q;
	cin >> n >> q;

	BIT bit(n);
	BIT bit2(n);
	ll t, x, y, v;
	REPD(i, 0, q)
	{
		cin >> t >> x >> y >> v;
		if (t == 0)
		{
			if (bit2.query(x) - bit2.query(x - 1) == 0)
			{
				bit.update(x, v * (x % 2 == 1 ? -1 : 1));
				bit2.update(x, 1);
			}
		}

		ll res;
		if (t == 1)
		{
			if (y == x)
			{
				cout << v << endl;
			}
			if (y < x)
			{
				if (bit2.query(x - 1) - bit2.query(y - 1) == x - y)
				{
					res = (bit.query(x - 1) - bit.query(y - 1)) * (y % 2 == 1 ? -1LL : 1LL) + v * ((x - y) % 2 == 1 ? -1LL : 1LL);
					cout << res << endl;
				}
				else
				{
					cout << "Ambiguous" << endl;
				}
			}
			if (x < y)
			{
				if (bit2.query(y - 1) - bit2.query(x - 1) == y - x)
				{
					res = (bit.query(y - 1) - bit.query(x - 1)) * ((y + 1) % 2 == 1 ? -1LL : 1LL) + v * ((y - x) % 2 == 1 ? -1LL : 1LL);
					cout << res << endl;
				}
				else
				{
					cout << "Ambiguous" << endl;
				}
			}
		}
	}

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
