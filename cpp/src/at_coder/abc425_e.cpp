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
	using value_type = std::decay_t<decltype(make_multiple_vector<N - 1, T>(args...))>;
	return vector<value_type>(size, make_multiple_vector<N - 1, T>(args...));
}

ll2d construct_dp()
{
	vector<bool> are_primes(5001, true);
	are_primes[0] = false;
	are_primes[1] = false;
	REPD(i, 2, 5000)
	{
		if (!are_primes[i])
		{
			continue;
		}
		for (ll j = i * 2; j <= 5000; j += i)
		{
			are_primes[j] = false;
		}
	}

	ll2d dp = make_multiple_vector<2, ll>(5001, 5001, 0);
	REPD(i, 2, 5001)
	{
		ll num = i;
		REPD(j, 2, 5001)
		{
			if (!are_primes[j])
			{
				continue;
			}
			while (num % j == 0)
			{
				dp[i][j]++;
				num /= j;
			}
			if (num == 1)
			{
				break;
			}
		}
	}

	REPD(i, 2, 5001)
	{
		REPD(j, 2, 5001)
		{
			dp[i][j] += dp[i - 1][j];
		}
	}

	return dp;
}

ll solve(const ll2d &dp, const ll m)
{
	ll n;
	cin >> n;
	ll1d a(n);
	ll sum_c = 0;
	REPD(i, 0, n)
	{
		cin >> a[i];
		sum_c += a[i];
	}

	ll1d primes(5001, 0);
	REPD(i, 2, 5001)
	{
		primes[i] = dp[sum_c][i];
	}
	REPD(i, 0, n)
	{
		REPD(j, 2, 5001)
		{
			primes[j] -= dp[a[i]][j];
		}
	}

	ll result = 1;
	REPD(i, 2, 5001)
	{
		if (primes[i] == 0)
		{
			continue;
		}
		REPD(j, 0, primes[i])
		{
			result *= i;
			result %= m;
		}
	}

	return result;
}

// main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	// cin >> N >> x >> y;
	// solve();

	ll t, m;
	cin >> t >> m;

	auto dp = construct_dp();
	REPD(i, 0, t)
	{
		auto r = solve(dp, m);
		cout << r << endl;
	}

	return 0;
}
