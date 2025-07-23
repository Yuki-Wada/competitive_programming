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
#include <random>

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
using pair1d = vector<llpair>;
using pair2d = vector2d<llpair>;

// constant
static constexpr ll MOD = 998244353LL;
static constexpr double PI = 3.14159265358979323846;

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

inline ll get_power(ll base, ull exponential, ll mod)
{
	ll result = 1;
	while (exponential >= 1)
	{
		if (exponential & 1)
		{
			result = result * base;
			result %= mod;
		}
		base = base * base;
		base %= mod;
		exponential >>= 1;
	}

	return result;
}

ll N, K;

int solve()
{
	cin >> N >> K;

	ll1d Ps(N);
	for (ll i = 0; i < N; ++i)
	{
		cin >> Ps[i];
		--Ps[i];
	}

	ll2d cyclics;
	vector<bool> is_checked(N, false);
	for (ll i = 0; i < N; ++i)
	{
		if (is_checked[i])
			continue;

		auto idx = i;
		ll1d cyclic;
		while (!is_checked[idx])
		{
			cyclic.emplace_back(idx);
			is_checked[idx] = true;
			idx = Ps[idx];
		}
		cyclics.emplace_back(cyclic);
	}

	vector<ll> results(N);
	for (auto &cyclic : cyclics)
	{
		auto cyclic_size = cyclic.size();
		ll power2 = get_power(2LL, K, cyclic_size);

		for (ll i = 0; i < cyclic_size; ++i)
		{
			auto idx = cyclic[i];
			results[idx] = cyclic[(power2 + i) % cyclic_size];
		}
	}

	for (ll i = 0; i < N; ++i)
		cout << results[i] + 1 << " ";

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
