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
static const ll MOD = 998244353LL;
static const double PI = 3.14159265358979323846;

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

using pair1d = vector<llpair>;
ll N, X, Y;
pair1d ABs;
ll2d dps = make_multiple_vector(100000000000LL, 81, 10001);

int solve()
{
	cin >> N >> X >> Y;
	ABs.reserve(N);

	for (ll j = 0; j < 10001; ++j)
	{
		dps[0][j] = 0;
	}

	{
		ll a, b;
		REPD(i, 0, N)
		cin >> a >> b, ABs.emplace_back(a, b);
	}

	for (ll i = 0; i < N; ++i)
	{
		auto [a, b] = ABs[i];
		for (ll j = 0; j < N; ++j)
		{
			for (ll k = 0; k < 10001; ++k)
			{
				if (k - a < 0LL)
				{
					continue;
				}
				dps[N - j][k] = min(dps[N - j][k], dps[N - j - 1LL][k - a] + b);
			}
		}
	}

	ll res = 1;
	for (ll i = 1; i < N; ++i)
	{
		for (ll j = 0; j <= X; ++j)
		{
			if (dps[i][j] <= Y)
			{
				res = i + 1;
				break;
			}
		}
	}

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
