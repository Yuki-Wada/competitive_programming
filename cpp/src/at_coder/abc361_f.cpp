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

ll N;

bool is_smaller(ll a, ll b, ll n)
{
	REPD(i, 0, b)
	{
		n /= a;
		if (n >= 1LL)
		{
			continue;
		}
		else
		{
			return false;
		}
	}
	return true;
}
int solve()
{
	cin >> N;

	ll res = 0;
	ll1d p1s = {2};
	ll1d p2s = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};

	vector<bool> are_vals_a_b(1000001LL, false);
	are_vals_a_b[0] = true;

	REPI(p, p1s)
	{
		ll low = 1LL;
		ll high = 1000000001LL;
		ll mid = (low + high) / 2LL;
		while (high - low >= 2LL)
		{
			if (is_smaller(mid, p, N))
			{
				low = mid;
			}
			else
			{
				high = mid;
			}
			mid = (low + high) / 2LL;
		}
		res += low;

		REPD(i, 1, 1001LL)
		{
			are_vals_a_b[i * i] = true;
		}
	}

	REPI(p, p2s)
	{
		ll max_a;
		if (p == 3LL)
		{
			max_a = 1000000LL;
		}
		else if (p == 5LL)
		{
			max_a = 3981LL;
		}
		else if (p == 7LL)
		{
			max_a = 372LL;
		}
		else
		{
			max_a = 100LL;
		}

		ll1d idxs;
		REPD(a, 1, max_a + 1LL)
		{
			if (!is_smaller(a, p, N))
			{
				break;
			}

			if (are_vals_a_b[a])
			{
				continue;
			}

			++res;

			auto idx = 1LL;
			REPD(i, 0, p)
			{
				idx *= a;
			}
			if (idx <= 1000000LL)
			{
				idxs.push_back(idx);
			}
		}

		REPI(idx, idxs)
		{
			are_vals_a_b[idx] = true;
		}
	}

	RET(res);

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
