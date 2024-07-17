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

// computational complexity: o(log(max(a, b)))
int dfs(vector<int> &dps, ll idx, vector<ll> &As, vector<ll> &Bs, ll N)
{
	if (dps[idx] != -1)
	{
		return dps[idx];
	}

	int res = 0;
	REPD(i, 0, N)
	REPD(j, 0, N)
	{
		if (i == j)
		{
			continue;
		}
		if ((idx & (1LL << i)) != 0LL)
		{
			continue;
		}
		if ((idx & (1LL << j)) != 0LL)
		{
			continue;
		}
		auto ai = As[i];
		auto aj = As[j];
		auto bi = Bs[i];
		auto bj = Bs[j];

		if (ai == aj || bi == bj)
		{
			ll new_idx = idx | (1LL << i) | (1LL << j);
			res = max(res, 1 - dfs(dps, new_idx, As, Bs, N));
		}
	}
	dps[idx] = res;
	return dps[idx];
}

int solve()
{
	ll N;
	cin >> N;

	auto As = make_multiple_vector(0LL, N);
	auto Bs = make_multiple_vector(0LL, N);
	REPD(i, 0, N)
	{
		cin >> As[i] >> Bs[i];
	}

	auto dps = make_multiple_vector(-1, 1LL << N);
	auto res = dfs(dps, 0, As, Bs, N);

	cout << (res == 1 ? "Takahashi" : "Aoki") << endl;

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
