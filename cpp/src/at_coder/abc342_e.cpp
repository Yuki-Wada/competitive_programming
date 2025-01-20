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

ll N, M;

ll binary_search(ll l, ll d, ll k, ll max_t)
{
	ll low = 0, high = k - 1LL, mid = (low + high) / 2LL;
	if (l + high * d <= max_t)
	{
		return l + high * d;
	}
	while (high - low >= 2LL)
	{
		if (l + mid * d <= max_t)
		{
			low = mid;
		}
		else
		{
			high = mid;
		}

		mid = (low + high) / 2LL;
	}

	return l + low * d;
}

int solve()
{
	cin >> N >> M;

	vector2d<tuple<ll, ll, ll, ll, ll>> edges(N);
	REPD(i, 0, M)
	{
		ll l, d, k, c, a, b;
		cin >> l >> d >> k >> c >> a >> b;
		--a, --b;
		edges[b].emplace_back(l, d, k, c, a);
	}

	ll1d res(N, -1LL);
	vector<bool> is_visited(N, false);

	priority_queue<tuple<ll, ll>> queue;
	queue.emplace(MAX_VALUE, N - 1LL);
	res[N - 1LL] = MAX_VALUE;
	while (!queue.empty())
	{
		auto [time, node] = queue.top();
		queue.pop();

		if (is_visited[node])
		{
			continue;
		}
		is_visited[node] = true;

		REPD(i, 0, edges[node].size())
		{
			auto [l, d, k, c, a] = edges[node][i];
			if (l <= time - c)
			{
				auto t = binary_search(l, d, k, time - c);
				res[a] = max(res[a], t);
				queue.emplace(t, a);
			}
		}
	}

	REPD(i, 0, N - 1LL)
	{
		if (res[i] != -1LL)
		{
			cout << res[i] << endl;
		}
		else
		{
			cout << "Unreachable" << endl;
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
