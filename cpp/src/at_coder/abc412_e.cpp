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

// temporary
#include <atcoder/all>
using namespace atcoder;

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

// constant
static constexpr ll MOD = 998244353LL;
static constexpr double PI = 3.14159265358979323846;

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args)
{
	return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args)
{
	using value_type = std::decay_t<decltype(make_multiple_vector<N - 1LL, T>(args...))>;
	return vector<value_type>(size, make_multiple_vector<N - 1LL, T>(args...));
}

ll solve()
{
	ll l, r;
	cin >> l >> r;

	ll num = 10000001LL;

	vector<bool> is_prime_1(num, true);
	vector<bool> is_prime_2(r - l, true);
	set<ll> pows;
	is_prime_1[0] = is_prime_1[1] = false;
	REPD(p, 2, num)
	{
		if (!is_prime_1[p])
		{
			continue;
		}
		for (ll pp = p * p; pp <= r; pp *= p)
		{
			pows.insert(pp);
		}
		for (ll j = p * 2LL; j <= num; j += p)
		{
			is_prime_1[j] = false;
		}
		ll begin = ((l + 1LL + p - 1LL) / p) * p;
		if (begin == p)
		{
			begin += p;
		}
		for (ll j = begin; j <= r; j += p)
		{
			ll idx = j - (l + 1LL);
			is_prime_2[idx] = false;
		}
	}

	ll res = 1LL;
	REPD(i, 0, r - l)
	{
		if (is_prime_2[i])
		{
			res++;
		}
		else if (pows.count(i + l + 1LL) > 0LL)
		{
			res++;
		}
	}

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
