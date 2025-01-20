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
static const ll MOD = 998244353LL;
static const double PI = 3.14159265358979323846;

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

ll N, M, K;
ll1d As;
ll1d sorted_As;
ll1d accum_As;

bool is_x_valid(ll a, ll x, ll residue)
{
	residue -= x;
	ll cutoff_a = a + x + 1LL;

	auto dist = distance(sorted_As.begin(), upper_bound(sorted_As.begin(), sorted_As.end(), cutoff_a, greater<ll>()));
	if (dist >= M)
	{
		return false;
	}

	ll diff = cutoff_a * (M - dist);
	if (distance(sorted_As.begin(), upper_bound(sorted_As.begin(), sorted_As.end(), a, greater<ll>())) > M)
	{
		diff -= accum_As[M] - accum_As[dist];
	}
	else
	{
		diff -= accum_As[M + 1] - accum_As[dist] - a;
	}

	if (residue >= diff)
	{
		return false;
	};
	return true;
}

ll find_min_x(ll a)
{
	if (M == N)
	{
		return 0LL;
	}
	ll residue = K - accum_As[N];
	if (!is_x_valid(a, residue, residue))
	{
		return -1LL;
	}
	if (is_x_valid(a, 0LL, residue))
	{
		return 0LL;
	}

	ll low = 0, high = residue, mid = (low + high) / 2LL;
	while (high - low >= 2LL)
	{
		if (is_x_valid(a, mid, residue))
		{
			high = mid;
		}
		else
		{
			low = mid;
		}
		mid = (low + high) / 2LL;
	}

	return high;
}

int solve()
{
	cin >> N >> M >> K;

	As.resize(N);
	sorted_As.resize(N);
	REPD(i, 0, N)
	{
		ll a;
		cin >> a;
		As[i] = a;
		sorted_As[i] = a;
	}
	sort(sorted_As.begin(), sorted_As.end());
	reverse(sorted_As.begin(), sorted_As.end());

	accum_As.resize(N + 1LL);
	REPD(i, 0, N)
	{
		accum_As[i + 1] = accum_As[i] + sorted_As[i];
	}

	ll1d results(N);
	REPD(i, 0, N)
	{
		results[i] = find_min_x(As[i]);
	}

	REPD(i, 0, N)
	{
		cout << results[i];
		if (i + 1 < N)
		{
			cout << ' ';
		}
		else
		{
			cout << endl;
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
