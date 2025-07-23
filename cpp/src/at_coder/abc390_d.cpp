// include
//------------------------------------------
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_set>
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

ll N;

void dfs(ll idx, ll2d &groups, ll1d &As, unordered_set<ll> &result)
{
	if (idx >= N)
	{
		ll xor_val = 0;
		for (auto group : groups)
		{
			ll sum_val = 0;
			for (auto idx : group)
				sum_val += As[idx];
			xor_val ^= sum_val;
		}
		result.insert(xor_val);
		return;
	}

	for (ll i = 0; i < groups.size(); ++i)
	{
		groups[i].emplace_back(idx);
		dfs(idx + 1LL, groups, As, result);
		groups[i].pop_back();
	}

	ll1d new_group{idx};
	groups.emplace_back(new_group);
	dfs(idx + 1LL, groups, As, result);
	groups.pop_back();

	return;
}

ll calc(ll1d &As)
{
	unordered_set<ll> result;
	ll2d groups;
	dfs(0LL, groups, As, result);
	return result.size();
}

int solve()
{
	cin >> N;
	ll1d idxs(N);
	ll1d As(N);
	REPD(i, 0, N)
	cin >> As[i], idxs[i] = i;

	cout << calc(As) << endl;

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
