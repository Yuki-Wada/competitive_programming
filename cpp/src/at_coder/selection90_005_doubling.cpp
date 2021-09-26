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

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_4_A&lang=ja#
int solve()
{
	ll n, b, k;
	cin >> n >> b >> k;

	auto cs = make_multiple_vector(0LL, k);
	REPD(i, 0, k)
	cin >> cs[i];

	auto dps = make_multiple_vector(0LL, 64LL, b);
	REPI(c, cs)
	{
		++dps[0][c % b];
	}

	ll pow10 = 10 % b;
	REPD(i, 0, 62LL)
	{
		REPD(j, 0, b)
		REPD(k, 0, b)
		{
			dps[i + 1][(pow10 * j + k) % b] += dps[i][j] * dps[i][k];
			dps[i + 1][(pow10 * j + k) % b] %= MOD;
		}
		pow10 *= pow10;
		pow10 %= b;
	}

	auto prev = make_multiple_vector(0LL, b);
	auto curr = make_multiple_vector(0LL, b);
	prev[0] = 1;

	pow10 = 10 % b;
	ll idx = 0;
	while ((n >> idx) > 0LL)
	{
		if ((n & (1LL << idx)) != 0LL)
		{
			REPD(j, 0, b)
			REPD(k, 0, b)
			{
				curr[(pow10 * j + k) % b] += prev[j] * dps[idx][k];
				curr[(pow10 * j + k) % b] %= MOD;
			}
			REPD(i, 0, b)
			{
				prev[i] = curr[i];
				curr[i] = 0;
			}
		}
		pow10 *= pow10;
		pow10 %= b;
		++idx;
	}

	cout << prev[0] << endl;

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
