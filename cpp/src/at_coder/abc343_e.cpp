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

ll v1, v2, v3;

ll intersect_length(ll a, ll b)
{
	return max(min(a + 7LL, b + 7LL) - max(a, b), 0LL);
}

ll intersect_length(ll a, ll b, ll c)
{
	return max(min({a + 7LL, b + 7LL, c + 7LL}) - max({a, b, c}), 0LL);
}
bool aaa(ll b1, ll b2, ll b3)
{
	ll _v3 = 0;
	ll _v2 = intersect_length(0LL, b1) * intersect_length(0LL, b2) * intersect_length(0LL, b3);
	ll _v1 = 7 * 7 * 7 * 3 - _v2 * 2 - _v3 * 3;
	return ((v1 == _v1) && (v2 == _v2) && (v3 == _v3));
}

bool bbb(ll b1, ll b2, ll b3, ll c1, ll c2, ll c3)
{
	ll _v3 = intersect_length(0LL, b1, c1) * intersect_length(0LL, b2, c2) * intersect_length(0LL, b3, c3);

	ll _v2 = 0;
	_v2 += intersect_length(0LL, b1) * intersect_length(0LL, b2) * intersect_length(0LL, b3) - _v3;
	_v2 += intersect_length(0LL, c1) * intersect_length(0LL, c2) * intersect_length(0LL, c3) - _v3;
	_v2 += intersect_length(b1, c1) * intersect_length(b2, c2) * intersect_length(b3, c3) - _v3;

	ll _v1 = 7 * 7 * 7 * 3 - _v2 * 2 - _v3 * 3;
	return ((v1 == _v1) && (v2 == _v2) && (v3 == _v3));
}

int solve()
{
	cin >> v1 >> v2 >> v3;

	if (v2 == 0 && v3 == 0)
	{
		if (v1 == 7 * 7 * 7 * 3)
		{
			cout << "Yes" << endl;
			cout << 0 << " " << 0 << " " << 0 << " " << -100 << " " << -100 << " " << -100 << " " << 100 << " " << 100 << " " << 100 << endl;
			return 0;
		}
		else
		{
			cout << "No" << endl;
			return 0;
		}
	}

	for (ll i1 = -6; i1 < 7; ++i1)
		for (ll i2 = -6; i2 < 7; ++i2)
			for (ll i3 = -6; i3 < 7; ++i3)
			{
				if (aaa(i1, i2, i3))
				{
					cout << "Yes" << endl;
					cout << 0 << " " << 0 << " " << 0 << " " << i1 << " " << i2 << " " << i3 << " " << 100 << " " << 100 << " " << 100 << endl;
					return 0;
				}
				ll min_j1 = min(-6LL + i1, -6LL);
				ll max_j1 = max(7LL + i1, 7LL);
				ll min_j2 = min(-6LL + i2, -6LL);
				ll max_j2 = max(7LL + i2, 7LL);
				ll min_j3 = min(-6LL + i3, -6LL);
				ll max_j3 = max(7LL + i3, 7LL);
				for (ll j1 = min_j1; j1 < max_j1; ++j1)
					for (ll j2 = min_j2; j2 < max_j2; ++j2)
						for (ll j3 = min_j3; j3 < max_j3; ++j3)
						{
							if (bbb(i1, i2, i3, j1, j2, j3))
							{
								cout << "Yes" << endl;
								cout << 0 << " " << 0 << " " << 0 << " " << i1 << " " << i2 << " " << i3 << " " << j1 << " " << j2 << " " << j3 << endl;
								return 0;
							}
						}
			}

	cout << "No" << endl;

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
