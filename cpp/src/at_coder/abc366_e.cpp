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

ll N, D;
ll D_LIMIT = 1000000LL;

int solve()
{
	cin >> N >> D;

	ll1d xs(N), ys(N);
	ll sum_x = 0, sum_y = 0;
	REPD(i, 0, N)
	{
		cin >> xs[i] >> ys[i];
		sum_x += xs[i];
		sum_y += ys[i];
	}
	sort(xs.begin(), xs.end());
	sort(ys.begin(), ys.end());

	ll1d dist_x(D_LIMIT * 2LL * 2LL + 1LL);
	dist_x[0] = D_LIMIT * 2LL * N + sum_x;
	REPD(i, -D_LIMIT * 2LL, D_LIMIT * 2LL)
	{
		auto v = i + 1LL;
		auto cnt = distance(xs.begin(), lower_bound(xs.begin(), xs.end(), v));
		dist_x[v + D_LIMIT * 2LL] = dist_x[i + D_LIMIT * 2LL] - (N - cnt * 2LL);
	}

	ll1d dist_y((D_LIMIT * 2LL + 1LL) * 2LL + 1LL);
	dist_y[0] = (D_LIMIT * 2LL + 1LL) * N + sum_y;
	REPD(i, -(D_LIMIT * 2LL + 1LL), (D_LIMIT * 2LL + 1LL))
	{
		auto v = i + 1LL;
		auto cnt = distance(ys.begin(), lower_bound(ys.begin(), ys.end(), v));
		dist_y[v + (D_LIMIT * 2LL + 1LL)] = dist_y[i + (D_LIMIT * 2LL + 1LL)] - (N - cnt * 2LL);
	}

	ll min_y_idx = distance(dist_y.begin(), min_element(dist_y.begin(), dist_y.end()));

	REPD(i, min_y_idx - 10, min_y_idx + 20)
	{
		// cout << dist_y[i] << endl;
	}

	ll res = 0;
	REPD(i, -(D_LIMIT * 2LL), (D_LIMIT * 2LL + 1LL))
	{
		auto diff = D - dist_x[i + (D_LIMIT * 2LL)];
		if (dist_y[min_y_idx] > diff)
		{
			continue;
		}
		ll low = min_y_idx, high = (D_LIMIT * 2LL + 1LL) * 2LL, mid = (low + high) / 2LL;
		while (high - low > 1LL)
		{
			if (dist_y[mid] > diff)
			{
				high = mid;
			}
			else
			{
				low = mid;
			}
			mid = (low + high) / 2LL;
		}
		res += high - min_y_idx;

		low = 0LL, high = min_y_idx, mid = (low + high) / 2LL;
		while (high - low > 1LL)
		{
			if (dist_y[mid] > diff)
			{
				low = mid;
			}
			else
			{
				high = mid;
			}
			mid = (low + high) / 2LL;
		}
		res += min_y_idx - low;
		--res;
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
