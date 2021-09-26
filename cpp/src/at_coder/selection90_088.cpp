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
	ll n, q;
	cin >> n >> q;

	vector<ll> as(n);
	REPD(i, 0, n)
	cin >> as[i];

	vector<vector<bool>> mismatch(n, vector<bool>(n, false));
	ll x, y;
	REPD(i, 0, q)
	{
		cin >> x >> y;
		--x, --y;
		mismatch[x][y] = true;
		mismatch[y][x] = true;
	}

	vector<vector<bool>> mass(8889, vector<bool>(n, false));

	vector<ll> found;
	found.reserve(n);
	found.emplace_back(0);
	REPD(i, 0, as.size())
	{
		auto a = as[i];
		REPI(f, found)
		{
			bool loop_end = false;
			REPD(j, 0, n)
			if (mismatch[i][j] && mass[f][j])
			{
				loop_end = true;
				break;
			}
			if (loop_end)
				continue;

			REPD(j, 0, i)
			{
				if (mass[f + a][j])
				{
					vector<ll> bs, cs;
					bs.reserve(n);
					cs.reserve(n);

					REPD(k, 0, n)
					if (mass[f + a][k])
						bs.emplace_back(k + 1LL);
					REPD(k, 0, n)
					if (mass[f][k])
						cs.emplace_back(k + 1LL);
					cs.emplace_back(i + 1LL);

					cout << bs.size() << endl;
					REPD(k, 0, bs.size())
					{
						cout << bs[k];
						if (k + 1LL < bs.size())
							cout << " ";
						else
							cout << endl;
					}

					cout << cs.size() << endl;
					REPD(k, 0, cs.size())
					{
						cout << cs[k];
						if (k + 1LL < cs.size())
							cout << " ";
						else
							cout << endl;
					}

					return 0;
				}
			}

			REPD(j, 0, i)
			{
				mass[f + a][j] = mass[f][j];
			}
			mass[f + a][i] = true;
			found.emplace_back(f + a);
		}
	}

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
