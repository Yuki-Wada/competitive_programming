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

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
static const ll MOD = 998244353LL;
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
	ll N;
	cin >> N;

	vector<vector<bool>> res(1, vector<bool>(1, true));
	for (ll i = 1; i <= N; ++i)
	{
		auto prev = res;
		ll prev_carpet_size = ll(prev.size());
		res = vector<vector<bool>>(prev_carpet_size * 3LL, vector<bool>(prev_carpet_size * 3LL, false));
		for (ll j = 0; j < 3; ++j)
		{
			for (ll k = 0; k < 3; ++k)
			{
				if (j == 1 && k == 1)
				{
					continue;
				}
				for (ll p_j = 0; p_j < prev_carpet_size; ++p_j)
				{
					for (ll p_k = 0; p_k < prev_carpet_size; ++p_k)
					{
						res[p_j + prev_carpet_size * j][p_k + prev_carpet_size * k] = prev[p_j][p_k];
					}
				}
			}
		}
	}

	for (ll i = 0; i < res.size(); ++i)
	{
		for (ll j = 0; j < res[i].size(); ++j)
		{
			cout << (res[i][j] ? "#" : ".");
		}
		cout << endl;
	}

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
	// REPD(i, 0, t) solve();

	return 0;
}
