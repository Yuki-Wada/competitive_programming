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
static constexpr ll MOD = 998244353LL;
static constexpr double PI = 3.14159265358979323846;

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

ll N, X;
vector<vector<llpair>> nutritions(3);

ll calc(const vector<llpair> &nuts, ll x, ll val)
{
	ll1d prev_dps(x + 1LL);
	ll1d curr_dps(x + 1LL);
	for (auto [a, c] : nuts)
	{
		REPD(i, 0, x + 1LL)
		{
			if (i + c > x)
				break;
			curr_dps[i + c] = max(curr_dps[i + c], prev_dps[i] + a);
		}
		REPD(i, 0, x + 1LL)
		prev_dps[i] = curr_dps[i];
	}

	REPD(i, 0, x + 1LL)
	if (prev_dps[i] >= val)
		return i;

	return x + 1LL;
}

bool is_possible(ll x, ll val)
{
	REPD(i, 0, 3)
	{
		x -= calc(nutritions[i], x, val);
		if (x < 0LL)
			return false;
	}
	return true;
}

int solve()
{
	cin >> N >> X;

	REPD(i, 0, N)
	{
		ll v, a, c;
		cin >> v >> a >> c;
		--v;
		nutritions[v].emplace_back(a, c);
	}

	ll min_res = 0LL, max_res = 1000000001LL, mid_res = (max_res + min_res) / 2LL;
	while (max_res - min_res >= 2LL)
	{
		if (is_possible(X, mid_res))
			min_res = mid_res;
		else
			max_res = mid_res;
		mid_res = (max_res + min_res) / 2LL;
	}

	cout << min_res << endl;

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
