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

ll calc_dps(ll bit, ll k, ll n, vector<vector<ll>> &dps, const vector<ll> &dists, const vector<ll> &subset_bits, map<ll, pair<ll, ll>> &subset_map)
{
	if (dps[bit][k] != -1LL)
		return dps[bit][k];

	ll res = MAX_VALUE;
	ll cnt_1 = 0;
	REPD(i, 0, n)
	if (((bit >> i) & 1LL) == 1LL)
		++cnt_1;

	ll begin, end;
	tie(begin, end) = subset_map[bit];
	REPD(i, begin, end)
	{
		ll main_subbit = subset_bits[i];
		ll comp_subbit = bit ^ main_subbit;
		res = min(res, max(calc_dps(main_subbit, k - 1LL, n, dps, dists, subset_bits, subset_map), dists[comp_subbit]));
	}

	dps[bit][k] = res;

	return dps[bit][k];
}

int solve()
{
	ll n, k;
	cin >> n >> k;

	vector<pair<ll, ll>> xys(n);
	REPD(i, 0, n)
	{
		cin >> xys[i].first >> xys[i].second;
	}

	ll subset_cnt = 1;
	REPD(i, 0, n)
	{
		subset_cnt *= 3LL;
	}

	auto dps = make_multiple_vector(-1LL, 1LL << n, k + 1LL);
	auto dists = make_multiple_vector(0LL, 1LL << n);
	ll dist, cnt_1;
	vector<pair<ll, ll>> subxys(n);
	vector<ll> subset_bits;
	subset_bits.reserve(subset_cnt);
	map<ll, pair<ll, ll>> subset_map;
	REPD(bit, 0, 1LL << n)
	{
		dps[bit][0] = MAX_VALUE;

		dist = 0;
		cnt_1 = 0;
		REPD(i, 0, n)
		{
			if (((bit >> i) & 1LL) == 1LL)
				subxys[cnt_1++] = xys[i];
		}
		REPD(i, 0, cnt_1)
		REPD(j, i + 1, cnt_1)
		{
			dist = max(
				dist,
				(subxys[i].first - subxys[j].first) * (subxys[i].first - subxys[j].first) +
					(subxys[i].second - subxys[j].second) * (subxys[i].second - subxys[j].second));
		}
		dists[bit] = dist;

		subset_map[bit] = make_pair(subset_bits.size(), subset_bits.size() + (1LL << cnt_1) - 1LL);
		REPD(bit2, 0, 1LL << cnt_1)
		{
			if (bit2 + 1LL == (1LL << cnt_1))
				continue;
			ll subidx = 0;
			ll main_subbit = bit;
			REPD(i, 0, n)
			{
				while ((subidx < n) && ((main_subbit >> subidx) & 1LL) == 0LL)
				{
					++subidx;
					continue;
				}
				if (subidx >= n)
					break;
				if (((bit2 >> i) & 1LL) != 1LL)
					main_subbit = main_subbit ^ (1LL << subidx);
				++subidx;
			}
			subset_bits.emplace_back(main_subbit);
		}
	}

	REPD(i, 0, k + 1LL)
	{
		dps[0][k] = MAX_VALUE;
	}
	dps[0][0] = 0;

	cout << calc_dps((1LL << n) - 1LL, k, n, dps, dists, subset_bits, subset_map) << endl;

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
