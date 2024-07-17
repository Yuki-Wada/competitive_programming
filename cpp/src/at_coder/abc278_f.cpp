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

class Solver
{
private:
	ll node_count;
	ll edge_count;
	vector<pair<ll, ll>> edges;
	vector<vector<ll>> dps;

public:
	Solver(ll node_count, vector<pair<ll, ll>> edges) : node_count(node_count), edge_count(edges.size()), edges(edges), dps((1LL << edge_count), vector<ll>(node_count, -1LL))
	{
	}

	ll dp(ll node)
	{
		return dp_impl((1LL << edge_count) - 1LL, node);
	}

	ll dp_impl(ll g, ll node)
	{
		if (dps[g][node] != -1LL)
		{
			return dps[g][node];
		}
		for (ll i = 0; i < edges.size(); ++i)
		{
			auto [snode, dnode] = edges[i];
			if (snode == node && ((g >> i) % 2LL == 1LL))
			{
				if (dp_impl(g ^ (1LL << i), dnode) == 0LL)
				{
					dps[g][node] = 1LL;
					return dps[g][node];
				}
			}
		}
		dps[g][node] = 0LL;
		return dps[g][node];
	}
};

int solve()
{
	ll N;
	string S;
	vector<pair<ll, ll>> edges;
	cin >> N;
	map<char, ll> char2count;
	for (ll i = 0; i < N; ++i)
	{
		cin >> S;

		if (char2count.count(S[0]) == 0)
		{
			char2count[S[0]] = char2count.size();
		}
		if (char2count.count(S.back()) == 0)
		{
			char2count[S.back()] = char2count.size();
		}

		edges.emplace_back(make_pair(char2count[S[0]], char2count[S.back()]));
	}

	auto node_count = char2count.size();

	auto solver = Solver(node_count, edges);
	for (ll i = 0; i < node_count; ++i)
	{
		if (solver.dp(i) == 1)
		{
			cout << "First" << endl;
			return 0;
		}
	}

	cout << "Second" << endl;

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
