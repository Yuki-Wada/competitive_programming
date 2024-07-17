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

ll compute_gcd(ll a, ll b)
{
	if (b == 0LL)
	{
		return a;
	}
	if (a % b == 0LL)
	{
		return b;
	}
	return compute_gcd(b, a % b);
}

pair<ll, ll> bezout_solution(ll a, ll b)
{
	if (b == 0LL)
	{
		return {1LL, 0LL};
	}
	if (a % b == 0LL)
	{
		return {0LL, 1LL};
	}
	ll r = a % b;
	ll q = a / b;

	auto [prev_x, prev_y] = bezout_solution(b, r);
	ll x = prev_y, y = prev_x - q * prev_y;

	x = ((x % b) + b) % b;
	y = ((y % a) + a) % a - a;

	return {x, y};
}

int solve()
{
	ll X, Y;
	cin >> X >> Y;

	auto gcd = compute_gcd(abs(X), abs(Y));
	if (gcd > 2LL)
	{
		cout << -1 << endl;
		return 0;
	}
	auto [B, A] = bezout_solution(abs(X) / gcd, abs(Y) / gcd);

	A *= (X >= 0LL ? 1LL : -1LL);
	B *= (Y >= 0LL ? 1LL : -1LL);
	B *= -1LL;

	cout << A * (2LL / gcd) << " " << B * (2LL / gcd) << endl;
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
