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

bool is_mass_movable(const vector<string> &masses, ll i, ll j, ll H, ll W)
{
	if (masses[i][j] != '.')
	{
		return false;
	}

	if (i - 1LL >= 0LL && masses[i - 1LL][j] == '#')
	{
		return false;
	}
	if (i + 1LL < H && masses[i + 1LL][j] == '#')
	{
		return false;
	}
	if (j - 1LL >= 0LL && masses[i][j - 1LL] == '#')
	{
		return false;
	}
	if (j + 1LL < W && masses[i][j + 1LL] == '#')
	{
		return false;
	}
	return true;
}

ll compute_possible_mass_count(vector<vector<ll>> &visited, const vector<string> &masses, ll i, ll j, ll H, ll W, ll connected_component_idx)
{
	ll res = 0;

	queue<pair<ll, ll>> que;
	visited[i][j] = connected_component_idx;
	que.emplace(i, j);
	++res;

	while (!que.empty())
	{
		auto [i, j] = que.front();
		que.pop();
		if (i - 1LL >= 0LL)
		{
			if (visited[i - 1LL][j] != connected_component_idx && masses[i - 1LL][j] == '.')
			{
				visited[i - 1LL][j] = connected_component_idx;
				++res;
				if (is_mass_movable(masses, i - 1LL, j, H, W))
				{
					que.emplace(i - 1LL, j);
				}
			}
		}
		if (i + 1LL < H)
		{
			if (visited[i + 1LL][j] != connected_component_idx && masses[i + 1LL][j] == '.')
			{
				visited[i + 1LL][j] = connected_component_idx;
				++res;
				if (is_mass_movable(masses, i + 1LL, j, H, W))
				{
					que.emplace(i + 1LL, j);
				}
			}
		}
		if (j - 1LL >= 0LL)
		{
			if (visited[i][j - 1LL] != connected_component_idx && masses[i][j - 1LL] == '.')
			{
				visited[i][j - 1LL] = connected_component_idx;
				++res;
				if (is_mass_movable(masses, i, j - 1LL, H, W))
				{
					que.emplace(i, j - 1LL);
				}
			}
		}
		if (j + 1LL < W)
		{
			if (visited[i][j + 1LL] != connected_component_idx && masses[i][j + 1LL] == '.')
			{
				visited[i][j + 1LL] = connected_component_idx;
				++res;
				if (is_mass_movable(masses, i, j + 1LL, H, W))
				{
					que.emplace(i, j + 1LL);
				}
			}
		}
	}
	return res;
}

int solve()
{
	ll H, W;
	cin >> H >> W;
	vector<string> masses(H);
	REPD(i, 0, H)
	{
		cin >> masses[i];
	}

	auto visited = make_multiple_vector(-1LL, H, W);
	ll res = 1;
	ll connected_component_idx = 0;
	REPD(i, 0, H)
	REPD(j, 0, W)
	{
		if ((visited[i][j] == -1LL))
		{
			if (is_mass_movable(masses, i, j, H, W))
			{
				res = max(res, compute_possible_mass_count(visited, masses, i, j, H, W, connected_component_idx));
				++connected_component_idx;
			}
		}
	}

	cout << res << endl;

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
