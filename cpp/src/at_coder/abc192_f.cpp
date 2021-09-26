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
	ll N, X;
	cin >> N >> X;

	vector<ll> As(N);
	ll a;
	REPD(i, 0, N)
	{
		cin >> a;
		As[i] = a;
	}

	ll res = MAX_VALUE;
	ll tmp, idx;
	auto dps = make_multiple_vector(0, N + 1, N + 1, N);
	REPD(C, 1, N + 1)
	{
		REPD(i, 0, N)
		REPD(j, 0, C + 1)
		REPD(k, 0, C)
		dps[i + 1][j][k] = 0;

		REPD(i, 0, N)
		{
			a = As[i];
			REPD(j, 1, C + 1)
			{
				REPD(k, 0, C)
				{
					idx = (k + a) % C;
					tmp = dps[i][j][idx];
					if (j >= 2 && dps[i][j - 1][k] != 0)
					{
						tmp = max(tmp, dps[i][j - 1][k] + a);
					}
					if (j == 1 && idx == a % C)
					{
						tmp = max(tmp, dps[i][j - 1][k] + a);
					}
					dps[i + 1][j][idx] = tmp;
				}
			}
		}

		idx = X % C;
		if (dps[N][C][idx] != 0LL)
		{
			res = min(res, (X - dps[N][C][idx]) / C);
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
