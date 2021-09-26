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

ll calc(ll w, ll b, vector<vector<ll>> &grundy)
{
	if (grundy[w][b] != -1LL)
		return grundy[w][b];

	set<ll> found;
	if (w >= 1)
		found.insert(calc(w - 1, b + w, grundy));
	REPD(i, 1, b / 2 + 1)
	{
		found.insert(calc(w, b - i, grundy));
	}

	ll cnt = 0;
	for (auto iter = found.begin(); iter != found.end(); ++iter)
	{
		if ((*iter) > cnt)
			break;
		++cnt;
	}

	grundy[w][b] = cnt;
	return cnt;
}

int solve()
{
	ll n;
	cin >> n;

	auto grundy = make_multiple_vector(-1LL, 51LL, 1326LL);
	grundy[0][0] = 0;
	grundy[0][1] = 0;

	auto ws = make_multiple_vector(0LL, n);
	auto bs = make_multiple_vector(0LL, n);
	REPD(i, 0, n)
	cin >> ws[i];
	REPD(i, 0, n)
	cin >> bs[i];

	ll res = 0;
	REPD(i, 0, n)
	{
		res ^= calc(ws[i], bs[i], grundy);
	}

	cout << (res != 0LL ? "First" : "Second") << endl;

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
