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

ll N, Q;
string S;

ll calc_diff_count(ll l, ll r, ll slash_idx, ll1d &ones, ll1d &twos)
{
	auto one_count = ones[slash_idx + 1LL] - ones[l];
	auto two_count = twos[r + 1LL] - twos[slash_idx];
	return one_count - two_count;
}

ll calc_res(ll l, ll r, ll slash_idx, ll1d &ones, ll1d &twos)
{
	auto one_count = ones[slash_idx + 1LL] - ones[l];
	auto two_count = twos[r + 1LL] - twos[slash_idx];
	return min(one_count, two_count) * 2LL + 1LL;
}

int solve()
{
	cin >> N >> Q >> S;

	ll1d ones(N + 1LL), twos(N + 1LL), slash_idxs;
	slash_idxs.reserve(N);
	REPD(i, 0, N)
	{
		auto ch = S[i];
		ones[i + 1LL] = ones[i];
		twos[i + 1LL] = twos[i];
		if (ch == '1')
		{
			ones[i + 1LL]++;
		}
		else if (ch == '2')
		{
			twos[i + 1LL]++;
		}
		else if (ch == '/')
		{
			slash_idxs.emplace_back(i);
		}
	}

	REPD(i, 0, Q)
	{
		ll l, r;
		cin >> l >> r;
		--l, --r;
		auto begin_idx = distance(slash_idxs.begin(), lower_bound(slash_idxs.begin(), slash_idxs.end(), l));
		auto end_idx = distance(slash_idxs.begin(), lower_bound(slash_idxs.begin(), slash_idxs.end(), r + 1LL));
		if (begin_idx == end_idx)
		{
			cout << 0 << endl;
			continue;
		}
		ll low_idx = begin_idx, high_idx = end_idx - 1LL;
		if (calc_diff_count(l, r, slash_idxs[low_idx], ones, twos) >= 0LL)
		{
			cout << calc_res(l, r, slash_idxs[low_idx], ones, twos) << endl;
			continue;
		}
		if (calc_diff_count(l, r, slash_idxs[high_idx], ones, twos) < 0LL)
		{
			cout << calc_res(l, r, slash_idxs[high_idx], ones, twos) << endl;
			continue;
		}

		ll mid_idx = (low_idx + high_idx) / 2LL;
		while (high_idx - low_idx >= 2LL)
		{
			if (calc_diff_count(l, r, slash_idxs[mid_idx], ones, twos) < 0LL)
			{
				low_idx = mid_idx;
			}
			else
			{
				high_idx = mid_idx;
			}
			mid_idx = (low_idx + high_idx) / 2LL;
		}

		ll res = max(calc_res(l, r, slash_idxs[low_idx], ones, twos), calc_res(l, r, slash_idxs[high_idx], ones, twos));
		cout << res << endl;
	}

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
