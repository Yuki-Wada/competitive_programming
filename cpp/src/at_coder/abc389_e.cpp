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

ll N, M;
ll1d Ps;

ll calc_total_count(ll S)
{
	ll total_fix_count = 0LL;
	ll total_possible_count = 0LL;
	ll total_price = 0LL;
	REPD(i, 0, N)
	{
		auto p = Ps[i];
		auto k = (S / p + 1LL) / 2LL;
		if (k >= 1000000001LL)
			return -1LL;
		if (k * k > (M / p + 1LL))
			return -1LL;
		total_price += k * k * p;
		if (total_price > M)
			return -1LL;

		total_fix_count += k;
		if ((k * 2LL + 1LL) * p == (S + 1LL))
			++total_possible_count;
	}

	auto total_count = total_fix_count + min(total_possible_count, (M - total_price) / (S + 1LL));
	return total_count;
}

int solve()
{
	cin >> N >> M;

	Ps.resize(N);
	REPD(i, 0, N)
	cin >> Ps[i];

	ll low = 0, high = 1000000000000000002LL, mid = (low + high) / 2LL;
	while (high - low >= 2LL)
	{
		if (calc_total_count(mid) != -1LL)
			low = mid;
		else
			high = mid;
		mid = (low + high) / 2LL;
	}

	cout << calc_total_count(low) << endl;

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
