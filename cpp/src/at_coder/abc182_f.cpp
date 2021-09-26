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

ll calc(ll i, ll x, const vector<ll> &as, vector<map<ll, ll>> &dps)
{
	if (dps[i].count(x) > 0)
		return dps[i][x];

	ll v = (x + as[i - 1]) % as[i];
	if (v == 0)
		return dps[i][x] = 1;

	ll res = 0;
	if ((-as[i - 1] / as[i] < (x - v) / as[i]) && ((x - v) / as[i] < as[i - 1] / as[i]))
		res += calc(i + 1, v, as, dps);

	v -= as[i];
	if ((-as[i - 1] / as[i] < (x - v) / as[i]) && ((x - v) / as[i] < as[i - 1] / as[i]))
		res += calc(i + 1, v, as, dps);

	return dps[i][x] = res;
}

ll exec(ll x, const vector<ll> &as)
{
	vector<map<ll, ll>> dps(as.size());

	ll v = (x + as[0]) % as[0];
	if (v == 0)
		return 1;
	return calc(1, v, as, dps) + calc(1, v - as[0], as, dps);
}

int solve()
{
	ll n, x;
	cin >> n >> x;

	vector<ll> as(n);
	REPD(i, 0, n)
	cin >> as[n - i - 1];

	cout << exec(x, as) << endl;

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
