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

llpair dfs(const string &a, ll start_idx, ll sz)
{
	if (sz == 1LL)
	{
		return {ll(a[start_idx] - '0'), 1LL};
	}
	sz = sz / 3LL;

	auto [res0, ch0] = dfs(a, start_idx, sz);
	auto [res1, ch1] = dfs(a, start_idx + sz, sz);
	auto [res2, ch2] = dfs(a, start_idx + sz * 2LL, sz);

	ll res = (res0 + res1 + res2 >= 2LL ? 1LL : 0LL);
	ll1d chs;
	if (res0 == res)
	{
		chs.emplace_back(ch0);
	}
	if (res1 == res)
	{
		chs.emplace_back(ch1);
	}
	if (res2 == res)
	{
		chs.emplace_back(ch2);
	}
	sort(chs.begin(), chs.end());
	ll ch = 0LL;
	if (chs.size() == 3LL)
	{
		ch = chs[0] + chs[1];
	}
	else
	{
		ch = chs[0];
	}

	return {res, ch};
}

ll solve()
{
	ll n;
	cin >> n;

	string a;
	cin >> a;

	auto res = dfs(a, 0, a.size()).second;
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
