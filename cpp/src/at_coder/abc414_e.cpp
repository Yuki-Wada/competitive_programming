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

ll solve()
{
	ll n;
	cin >> n;

	ll res = 0;

	res = n % MOD;
	res = (res * (res + 1)) % MOD;
	res = (res * (MOD / 2LL + 1LL)) % MOD;

	ll q = 1;
	for (; q * q <= n; q++)
	{
		res = (res - n / q) % MOD;
	}
	ll m = n / q;
	res = (res - ((n / m) - q + 1LL) * m) % MOD;
	for (ll i = m - 1LL; i >= 1LL; i--)
	{
		ll l = n / (i + 1LL);
		ll r = n / i;

		res = (res - (r - l) * i) % MOD;
	}

	res = (res + MOD) % MOD;

	cout << res << endl;

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
