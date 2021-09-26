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

int solve()
{
	ll n, k, p;
	cin >> n >> k >> p;

	vector<ll> as(n);
	REPD(i, 0, n)
	cin >> as[i];

	vector<vector<ll>> set1(k + 1LL), set2(k + 1LL);
	ll cnt1, val;
	REPD(bit, 0, 1LL << (n / 2LL))
	{
		cnt1 = 0, val = 0;
		REPD(i, 0, (n / 2LL))
		{
			if (((bit >> i) & 1LL) == 1LL)
			{
				++cnt1;
				val += as[i];
			}
		}
		if (cnt1 > k)
			continue;
		set1[cnt1].emplace_back(val);
	}

	REPD(bit, 0, 1LL << (n - n / 2LL))
	{
		cnt1 = 0, val = 0;
		REPD(i, 0, (n - k / 2LL))
		{
			if (((bit >> i) & 1LL) == 1LL)
			{
				++cnt1;
				val += as[n / 2LL + i];
			}
		}
		if (cnt1 > k)
			continue;
		set2[cnt1].emplace_back(val);
	}
	REPD(i, 0, k + 1LL)
	sort(set1[i].begin(), set1[i].end());
	REPD(i, 0, k + 1LL)
	sort(set2[i].begin(), set2[i].end());

	ll res = 0;
	REPD(i, 0, k + 1LL)
	{
		REPD(j, 0, set1[i].size())
		{
			auto iter = upper_bound(set2[k - i].begin(), set2[k - i].end(), p - set1[i][j]);
			res += distance(set2[k - i].begin(), iter);
		}
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
