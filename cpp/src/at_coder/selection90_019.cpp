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

ll calc(ll start, ll end, vector<vector<ll>> &dps, const vector<ll> &as)
{
	if (start == end)
		return 0;
	if (dps[start][end] != -1LL)
		return dps[start][end];

	ll res = abs(as[start] - as[end - 1LL]) + calc(start + 1LL, end - 1LL, dps, as), curr;
	for (ll i = 2; start + i < end; i += 2LL)
	{
		curr = calc(start, start + i, dps, as);
		curr += calc(start + i, end, dps, as);
		res = min(res, curr);
	}

	dps[start][end] = res;
	return dps[start][end];
}

int solve()
{
	ll n;
	cin >> n;

	auto as = make_multiple_vector(0LL, n * 2LL);
	REPD(i, 0, n * 2LL)
	cin >> as[i];

	auto dps = make_multiple_vector(-1LL, n * 2LL, n * 2LL + 1LL);

	calc(0LL, n * 2LL, dps, as);
	cout << dps[0LL][n * 2LL] << endl;

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
