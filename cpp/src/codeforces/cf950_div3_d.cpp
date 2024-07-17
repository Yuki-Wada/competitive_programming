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

// computational complexity: o(log(max(a, b)))
inline ull get_gcd(ull a, ull b)
{
	if (b == 0)
	{
		return a;
	}
	return get_gcd(b, a % b);
}

int solve()
{
	ll N;
	cin >> N;

	auto As = make_multiple_vector(0LL, N);
	REPD(i, 0, N)
	{
		cin >> As[i];
	}

	auto dps = make_multiple_vector(MAX_VALUE, N, 2LL);

	ll b01, b02, b12;
	b01 = gcd(As[0], As[1]);
	b02 = gcd(As[0], As[2]);
	b12 = gcd(As[1], As[2]);

	dps[1][0] = b01;
	if (b01 <= b12)
	{
		dps[2][0] = b12;
	}
	dps[2][1] = min(b02, b12);

	REPD(i, 3, N)
	{
		ll b = gcd(As[i], As[i - 1]), b_ = gcd(As[i], As[i - 2]);
		if (dps[i - 1][0] != MAX_VALUE && dps[i - 1][0] <= b)
		{
			dps[i][0] = b;
		}

		ll b1 = MAX_VALUE, b2 = MAX_VALUE;
		if (dps[i - 2][0] != MAX_VALUE && dps[i - 2][0] <= b_)
		{
			b1 = b_;
		}
		if (dps[i - 1][1] != MAX_VALUE && dps[i - 1][1] <= b)
		{
			b2 = b;
		}
		dps[i][1] = min(b1, b2);
	}

	cout << ((dps[N - 2][0] == MAX_VALUE && dps[N - 1][1] == MAX_VALUE) ? "No" : "Yes") << endl;

	return 0;
}

// main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	// solve();

	ll t;
	cin >> t;
	REPD(i, 0, t)
	{
		solve();
	}

	return 0;
}
