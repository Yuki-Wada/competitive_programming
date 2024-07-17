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

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
static const ll MOD = 998244353LL;
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

// computational complexity: o(log(max(a, b)))
inline ull get_gcd(ull a, ull b)
{
	if (b == 0)
	{
		return a;
	}
	return get_gcd(b, a % b);
}

int solve()
{
	ll N, L, R;
	cin >> N >> L >> R;
	++R;

	ll array_length = 1LL << N;
	vector<vector<ll>> edges(array_length + 1LL);
	for (ll i = 1; i <= array_length; i *= 2LL)
	{
		for (ll j = 0; j + i <= array_length; j += i)
		{
			edges[j].emplace_back(j + i);
			edges[j + i].emplace_back(j);
		}
	}

	vector<ll> visited(array_length + 1LL, -1LL);
	queue<ll> que;
	visited[L] = L;
	que.push(L);

	while (!que.empty())
	{
		auto q = que.front();
		que.pop();
		if (q == R)
		{
			break;
		}
		REPI(n, edges[q])
		{
			if (visited[n] == -1LL)
			{
				visited[n] = q;
				que.push(n);
			}
		}
	}
	vector<pair<ll, ll>> ps;
	ll curr = R, prev = visited[curr];
	ps.emplace_back(prev, curr);
	while (prev != L)
	{
		curr = prev, prev = visited[prev];
		ps.emplace_back(prev, curr);
	}

	ll res = 0;
	REPI(p, ps)
	{
		auto [l, r] = p;
		ll small = min(l, r), large = max(l, r);
		ll div = get_gcd(small, large);
		ll i = 0, j = small / div;
		while (div > 1LL)
		{
			div /= 2LL;
			++i;
		}

		cout << "? " << i << " " << j << endl;

		ll tmp;
		cin >> tmp;
		res += (l < r ? 1LL : -1LL) * tmp;
		res %= 100LL;
		res += 100LL;
		res %= 100LL;
	}
	cout << "! " << res << endl;

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
