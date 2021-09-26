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
	ll n, m;
	cin >> n >> m;

	vector<bool> x(n, false);
	vector<bool> y(m, false);
	auto A = make_multiple_vector(false, m, n);

	ll t, a;
	REPD(i, 0, n)
	{
		cin >> t;
		REPD(j, 0, t)
		{
			cin >> a;
			--a;
			A[a][i] = true;
		}
	}
	REPD(i, 0, m)
	{
		cin >> t;
		if (t == 1)
			y[i] = true;
	}

	ll row = 0;
	bool tmp;
	REPD(col, 0, n)
	{
		REPD(i, row, m)
		{
			if (A[i][col])
			{
				REPD(j, 0, n)
				{
					tmp = A[i][j];
					A[i][j] = A[row][j];
					A[row][j] = tmp;
				}
				tmp = y[i];
				y[i] = y[row];
				y[row] = tmp;
				REPD(i2, row + 1, m)
				{
					if (A[i2][col])
					{
						REPD(j, 0, n)
						{
							A[i2][j] = A[i2][j] ^ A[row][j];
						}
						y[i2] = y[i2] ^ y[row];
					}
				}
				++row;
				break;
			}
		}
	}

	ll res = 1;
	REPD(i, 0, (n - row))
	{
		res *= 2LL;
		res %= 998244353LL;
	}
	REPD(i, row, m)
	{
		if (y[i])
			res = 0;
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
