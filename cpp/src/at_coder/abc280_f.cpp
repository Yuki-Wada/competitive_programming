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
static const ll MOD = 1000000007LL;
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

#define MAX_VALUE 9223372036854775807LL

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

#define INF_VALUE 9223372036854775807LL
#define NAN_VALUE 9223372036854775806LL

class QueryCalculator
{
private:
	ll N;
	vector<ll> components;
	vector<ll> dists;
	vector<vector<pair<ll, ll>>> edges;
	vector<bool> exist_closed_walk;

public:
	QueryCalculator(ll n) : N(n), components(n), dists(n), edges(n), exist_closed_walk(0) {}

	void add_edge(ll a, ll b, ll c)
	{
		--a, --b;
		edges[a].emplace_back(b, c);
		edges[b].emplace_back(a, -c);
	}

	void construct()
	{
		vector<bool> is_visited(N);
		ll component_idx = 0;
		for (ll i = 0; i < N; ++i)
		{
			if (is_visited[i])
				continue;

			exist_closed_walk.emplace_back(false);

			queue<ll> que;
			que.push(i);
			is_visited[i] = true;
			components[i] = component_idx;

			while (!que.empty())
			{
				ll curr = que.front();
				que.pop();
				for (auto [next, cost] : edges[curr])
				{
					if (!is_visited[next])
					{
						que.push(next);
						is_visited[next] = true;
						components[next] = component_idx;
						dists[next] = dists[curr] + cost;
					}
					else
					{
						if (dists[next] != dists[curr] + cost)
						{
							exist_closed_walk[component_idx] = true;
						}
					}
				}
			}
			++component_idx;
		}
	}

	ll calc_query(ll x, ll y)
	{
		--x, --y;
		if (components[x] != components[y])
		{
			return NAN_VALUE;
		}
		if (exist_closed_walk[components[x]])
		{
			return INF_VALUE;
		}
		return dists[y] - dists[x];
	}
};

int solve()
{
	ll N, M, Q;
	cin >> N >> M >> Q;

	auto calculator = QueryCalculator(N);
	ll a, b, c;
	for (ll i = 0; i < M; ++i)
	{
		cin >> a >> b >> c;
		calculator.add_edge(a, b, c);
	}
	calculator.construct();
	for (ll i = 0; i < Q; ++i)
	{
		cin >> a >> b;
		auto res = calculator.calc_query(a, b);
		if (res == NAN_VALUE)
		{
			cout << "nan" << endl;
		}
		else if (res == INF_VALUE)
		{
			cout << "inf" << endl;
		}
		else
		{
			cout << res << endl;
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
	// REPD(i, 0, t) solve();

	return 0;
}
