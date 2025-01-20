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

using pair1d = vector<llpair>;
ll N, Q;
ll1d As;

ll compute_point_oount(ll b, ll d)
{
	auto left = lower_bound(As.begin(), As.end(), b - d);
	auto right = upper_bound(As.begin(), As.end(), b + d);
	return distance(left, right);
}

ll compute_min_distance(ll b, ll k)
{
	if (compute_point_oount(b, 0LL) >= k)
	{
		return 0LL;
	}

	ll low = 0, high = 200000000LL, middle = (low + high) / 2LL;
	while (high - low >= 2)
	{
		auto pc = compute_point_oount(b, middle);

		if (pc >= k)
		{
			high = middle;
		}
		else
		{
			low = middle;
		}
		middle = (low + high) / 2LL;
	}
	return high;
}

int solve()
{
	cin >> N >> Q;
	As.resize(N);

	REPD(i, 0, N)
	cin >> As[i];

	sort(As.begin(), As.end());

	ll b, k;
	for (ll i = 0; i < Q; ++i)
	{
		cin >> b >> k;
		cout << compute_min_distance(b, k) << endl;
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
