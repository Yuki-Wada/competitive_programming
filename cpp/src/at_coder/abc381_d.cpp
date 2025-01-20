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

ll N;
pair1d As;

int solve()
{
	cin >> N;
	As.reserve(N);
	REPD(i, 0, N)
	{
		ll a;
		cin >> a;
		if (As.size() > 0 && As[ll(As.size()) - 1LL].first == a)
		{
			As[ll(As.size()) - 1LL].second++;
		}
		else
		{
			As.emplace_back(a, 1);
		}
	}

	pair1d subarray_idxs;
	ll left_idx = -1LL;
	REPD(i, 0, As.size())
	{
		if (As[i].second != 2LL)
		{
			if (left_idx != -1LL)
			{
				subarray_idxs.emplace_back(left_idx, i + (As[i].second > 2LL ? 1LL : 0LL));
				left_idx = -1LL;
			}
		}

		if (As[i].second >= 2LL)
		{
			if (left_idx == -1LL)
			{
				left_idx = i;
			}
		}
		else
		{
			left_idx = -1LL;
		}
	}
	if (left_idx != -1LL)
	{
		subarray_idxs.emplace_back(left_idx, As.size());
	}

	ll res = 0LL;
	REPD(i, 0, subarray_idxs.size())
	{
		auto [l, r] = subarray_idxs[i];

		auto li = l;
		set<ll> found;
		REPD(ri, l, r)
		{
			auto [ra, _1] = As[ri];
			if (found.count(ra) > 0LL)
			{
				while (found.count(ra) > 0LL)
				{
					auto [la, _2] = As[li];
					found.erase(la);
					++li;
				}
			}
			found.insert(ra);
			res = max(res, ri - li + 1LL);
		}
	}

	res *= 2LL;

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
