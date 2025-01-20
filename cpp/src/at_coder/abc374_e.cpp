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
#include <random>

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
using pair1d = vector<llpair>;
using pair2d = vector2d<llpair>;

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

using Machine = tuple<ll, ll, ll, ll>;
using Machines = vector<Machine>;
ll N, X;
Machines machines;

ll calq_req_x(ll a, ll p, ll b, ll q, ll w)
{
	ll res = MAX_VALUE;
	REPD(u, 0, b + 1LL)
	{
		if (w <= a * u)
		{
			res = min(res, p * u);
		}
		else
		{
			auto v = (w - a * u + b - 1LL) / b;
			res = min(res, p * u + q * v);
		}
	}

	REPD(v, 0, a + 1LL)
	{
		if (w <= b * v)
		{
			res = min(res, q * v);
		}
		else
		{
			auto u = (w - b * v + a - 1LL) / a;
			res = min(res, p * u + q * v);
		}
	}

	return res;
}

int solve()
{
	cin >> N >> X;
	machines.resize(N);
	REPD(i, 0, N)
	{
		ll a, p, b, q;
		cin >> a >> p >> b >> q;
		machines[i] = make_tuple(a, p, b, q);
	}

	ll max_w = 1000000001LL, min_w = 0LL;
	ll mid_w = (max_w + min_w) / 2LL;
	while (max_w - min_w >= 2LL)
	{
		ll req_x = 0LL;
		REPD(i, 0, N)
		{
			auto [a, p, b, q] = machines[i];
			req_x += calq_req_x(a, p, b, q, mid_w);
		}
		if (req_x <= X)
		{
			min_w = mid_w;
		}
		else
		{
			max_w = mid_w;
		}
		mid_w = (max_w + min_w) / 2LL;
	}

	cout << min_w << endl;

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
