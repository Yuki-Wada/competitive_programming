//include
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

//debug
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

bool can_be_colored(ll node, ll color, vector<ll> &colors, const vector<vector<ll>> &edges)
{
	REPI(v, edges[node])
	{
		if (colors[v] == color)
			return false;
	}
	return true;
}

ll dfs(ll color_count, vector<ll> &colors, const vector<ll> &component, const vector<vector<ll>> &edges)
{
	if (color_count + 1LL >= component.size())
		return 1LL;

	ll res = 0;
	ll next = component[color_count + 1];
	REPD(color, 0, 3)
	{
		if (!can_be_colored(next, color, colors, edges))
			continue;
		colors[next] = color;
		res += dfs(color_count + 1, colors, component, edges);
		colors[next] = -1;
	}

	return res;
}

ll calc(const vector<ll> &component, const vector<vector<ll>> &edges)
{
	vector<ll> colors(edges.size(), -1);
	ll curr = component[0];
	colors[curr] = 0;
	return dfs(0, colors, component, edges) * 3LL;
}

int solve()
{
	ll n, m;
	cin >> n >> m;

	vector<vector<ll>> edges(n);
	ll a, b;
	REPD(i, 0, m)
	{
		cin >> a >> b;
		--a, --b;
		edges[a].emplace_back(b);
		edges[b].emplace_back(a);
	}

	vector<bool> is_visited(n, false);
	vector<vector<ll>> components;
	stack<ll> s;
	REPD(i, 0, n)
	{
		if (is_visited[i])
			continue;
		components.emplace_back();
		s.emplace(i);
		is_visited[i] = true;
		while (!s.empty())
		{
			auto v = s.top();
			s.pop();
			components[components.size() - 1].emplace_back(v);
			REPI(w, edges[v])
			{
				if (is_visited[w])
					continue;
				s.emplace(w);
				is_visited[w] = true;
			}
		}
	}

	ll res = 1;
	REPI(component, components)
	{
		res *= calc(component, edges);
	}
	cout << res << endl;

	return 0;
}

//main function
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
