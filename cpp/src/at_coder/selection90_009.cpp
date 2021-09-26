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
	ll n;
	cin >> n;

	vector<pair<ll, ll>> xys(n);
	REPD(i, 0, n)
	{
		cin >> xys[i].first >> xys[i].second;
	}

	long double res = 0.0;
	vector<long double> sorted_angles(n * 3 - 3);
	vector<long double> angles(n - 1);
	long double xi, yi, xj, yj, angle;
	ll idx, modified_j;
	REPD(i, 0, n)
	{
		tie(xi, yi) = xys[i];
		REPD(j, 0, n)
		{
			if (j == i)
				continue;
			modified_j = j - (j >= i ? 1LL : 0LL);
			tie(xj, yj) = xys[j];
			angle = atan2(static_cast<long double>(yj - yi), static_cast<long double>(xj - xi)) / PI * 180.0L;
			angles[modified_j] = angle;
			sorted_angles[modified_j * 3] = angle;
			sorted_angles[modified_j * 3 + 1] = angle + 360.0L;
			sorted_angles[modified_j * 3 + 2] = angle - 360.0L;
		}
		sort(sorted_angles.begin(), sorted_angles.end());
		REPD(j, 0, n)
		{
			if (j == i)
				continue;
			modified_j = j - (j >= i ? 1LL : 0LL);

			angle = angles[modified_j];
			idx = distance(sorted_angles.begin(), lower_bound(sorted_angles.begin(), sorted_angles.end(), angle + 180.0L));
			if (idx - 1 >= 0)
				res = max(res, sorted_angles[idx - 1] - angle);
			idx = distance(sorted_angles.begin(), lower_bound(sorted_angles.begin(), sorted_angles.end(), angle - 180.0L));
			if (idx + 1 < sorted_angles.size())
				res = max(res, angle - sorted_angles[idx + 1]);
		}
	}

	cout << fixed << setprecision(12) << res << endl;

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
