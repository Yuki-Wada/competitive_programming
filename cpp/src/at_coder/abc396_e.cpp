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

using Edges = vector<vector<llpair>>;

bool compute(const Edges &edges, ll n, ll bit, ll2d &result)
{
	REPD(i, 0, n)
	{
		if (result[i][bit] != -1LL)
		{
			continue;
		}
		queue<ll> que;
		que.push(i);
		result[i][bit] = 0LL;
		ll1d visited;
		while (!que.empty())
		{
			ll v = que.front();
			visited.push_back(v);
			que.pop();
			REPD(j, 0, edges[v].size())
			{
				ll u = edges[v][j].first;
				ll w = edges[v][j].second;
				ll wbit = (w >> bit) & 1LL;
				if (result[u][bit] == -1LL)
				{
					result[u][bit] = result[v][bit] ^ wbit;
					que.push(u);
				}
				else
				{
					if (result[u][bit] != (result[v][bit] ^ wbit))
					{
						return false;
					}
				}
			}
		}
		ll cnt = 0LL;
		REPD(j, 0, visited.size())
		{
			ll v = visited[j];
			cnt += result[v][bit];
		}
		if (cnt * 2LL > visited.size())
		{
			REPD(j, 0, visited.size())
			{
				ll v = visited[j];
				result[v][bit] ^= 1LL;
			}
		}
	}
	return true;
}

ll solve()
{
	ll n, m;
	cin >> n >> m;

	Edges edges(n);
	REPD(i, 0, m)
	{
		ll x, y, z;
		cin >> x >> y >> z;
		--x, --y;
		edges[x].emplace_back(y, z);
		edges[y].emplace_back(x, z);
	}

	auto result = make_multiple_vector<2, ll>(n, 32LL, -1LL);
	REPD(bit, 0LL, 32LL)
	{
		auto ok = compute(edges, n, bit, result);
		if (!ok)
		{
			cout << -1LL << endl;
			return 0;
		}
	}

	REPD(i, 0, n)
	{
		ll res = 0LL;
		REPD(j, 0, 32)
		{
			res |= (result[i][j] << j);
		}
		cout << res;
		if (i != n - 1)
		{
			cout << " ";
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
