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

tuple<ll, ll, ll> dfs(ll node, const vector<char> &types, const vector<vector<ll>> &edges, vector<bool> &is_visited)
{
	ll node_type = types[node];
	is_visited[node] = true;
	ll res_a = (node_type == 'a'), res_b = (node_type == 'b'), res_ab = 1;
	ll a, b, ab;
	REPI(next, edges[node])
	{
		if (is_visited[next])
			continue;
		tie(a, b, ab) = dfs(next, types, edges, is_visited);
		res_a = (res_a * (a + ab)) % MOD;
		res_b = (res_b * (b + ab)) % MOD;
		res_ab = (res_ab * (a + b + ab + ab)) % MOD;
	}

	res_ab = ((res_ab - res_a - res_b) + MOD) % MOD;

	return {res_a, res_b, res_ab};
}

int solve()
{
	ll n, d;
	cin >> n >> d;

	vector<ll> as(n);
	REPD(i, 0, n)
	{
		cin >> as[i];
	}

	ll res = 0;
	REPD(i, 0, 1LL << n)
	{
		ll curr = 0;
		REPD(j, 0, n)
		if (((i >> j) & 1LL) == 1LL)
			curr = curr | as[j];
		ll subset_cnt = 0;
		REPD(j, 0, n)
		if (((i >> j) & 1LL) == 1LL)
			++subset_cnt;
		ll bit_cnt = 0;
		REPD(j, 0, d)
		if (((curr >> j) & 1LL) == 1LL)
			++bit_cnt;
		res += (subset_cnt % 2LL == 0LL ? 1LL : -1LL) * (1LL << (d - bit_cnt));
	}

	cout << res << endl;

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
