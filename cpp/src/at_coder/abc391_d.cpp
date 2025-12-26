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
	ll n, w;
	cin >> n >> w;

	auto blocks = make_multiple_vector<2, pair<ll, ll>>(w, 0LL, make_pair(0LL, 0LL));
	REPD(i, 0, n)
	{
		ll x, y;
		cin >> x >> y;
		--x, --y;
		blocks[x].emplace_back(y, i);
	}
	REPD(i, 0, w)
	{
		sort(blocks[i].begin(), blocks[i].end());
	}
	auto ords = make_multiple_vector<1, ll>(n, 0LL);
	REPD(i, 0, w)
	{
		REPD(ord_, 0, blocks[i].size())
		{
			auto num = blocks[i][ord_].second;
			ords[num] = ord_;
		}
	}

	ll1d max_hs;
	ll ord = 0LL;
	while (true)
	{
		bool computed = true;
		ll max_h = 0LL;
		REPD(i, 0, w)
		{
			if (ord >= blocks[i].size())
			{
				computed = false;
				break;
			}
			max_h = max(max_h, blocks[i][ord].first);
		}
		if (!computed)
		{
			break;
		}
		max_hs.emplace_back(max_h + 1LL);
		++ord;
	}

	ll q;
	cin >> q;
	REPD(i, 0, q)
	{
		ll t, a;
		cin >> t >> a;
		--a;
		if (ords[a] < max_hs.size() && t >= max_hs[ords[a]])
		{
			cout << "No" << endl;
		}
		else
		{
			cout << "Yes" << endl;
		}
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

	// REPD(i, 0, t)
	// {
	// 	solve();
	// }

	return 0;
}
