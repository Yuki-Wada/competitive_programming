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

vector<vector<ll>> floyd_warshall(vector<vector<ll>> &dists)
{
	ll n = dists.size();

	for (ll i = 0; i < n; ++i)
	{
		dists[i][i] = 0;
	}

	for (ll k = 0; k < n; ++k)
		for (ll i = 0; i < n; ++i)
			for (ll j = 0; j < n; ++j)
			{
				dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);
			}

	return dists;
}

ll exec(ll x, ll p, const vector<vector<ll>> &edges)
{
	ll n = edges.size();
	vector<vector<ll>> x_edges(n, vector<ll>(n));
	REPD(i, 0, edges.size())
	{
		REPD(j, 0, edges.size())
		{
			if (edges[i][j] != -1LL)
				x_edges[i][j] = edges[i][j];
			else
				x_edges[i][j] = x;
		}
	}

	auto dists = floyd_warshall(x_edges);

	ll res = 0;
	REPD(i, 0, n)
	{
		REPD(j, i + 1, n)
		{
			if (dists[i][j] <= p)
				++res;
		}
	}
	return res;
}

int solve()
{
	ll n, p, k;
	cin >> n >> p >> k;

	vector<vector<ll>> edges(n, vector<ll>(n));
	REPD(i, 0, n)
	REPD(j, 0, n)
	{
		cin >> edges[i][j];
	}

	ll left, right;
	ll res;

	res = exec(p + 1LL, p, edges);
	if (res == k)
		RET("Infinity");

	res = exec(1LL, p, edges);
	if (res < k)
		RET(0);

	res = exec(p, p, edges);
	if (res > k)
		RET(0);

	res = exec(1LL, p, edges);
	if (res == k)
		left = 1;
	else
	{
		ll low = 1, high = p, mid;
		while (high - low >= 2LL)
		{
			mid = (high + low) / 2LL;

			res = exec(mid, p, edges);
			if (res <= k)
				high = mid;
			else
				low = mid;
		}
		left = high;
	}

	res = exec(p, p, edges);
	if (res == k)
		right = p;
	else
	{
		ll low = 1, high = p, mid;
		while (high - low >= 2LL)
		{
			mid = (high + low) / 2LL;
			res = exec(mid, p, edges);
			if (res >= k)
				low = mid;
			else
				high = mid;
		}
		right = low;
	}

	cout << right - left + 1LL << endl;

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
