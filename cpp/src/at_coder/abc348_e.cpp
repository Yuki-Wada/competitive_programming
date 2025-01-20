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
// static const ll MOD = (1LL << 61LL) - 1LL;
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
using pair2d = vector2d<llpair>;
ll N;
pair1d ABs;
ll1d Cs;
pair2d edges;
vector<bool> visited;

llpair dfs1(ll idx, ll depth)
{
	ll edge_score = Cs[idx], base_score = Cs[idx] * depth;
	visited[idx] = true;
	REPD(i, 0, edges[idx].size())
	{
		auto node = edges[idx][i].first;
		if (visited[node])
		{
			continue;
		}
		auto [edge_node_score, base_node_score] = dfs1(node, depth + 1);
		edges[idx][i].second = edge_node_score;
		edge_score += edge_node_score;
		base_score += base_node_score;
	}
	return {edge_score, base_score};
}

ll dfs2(ll idx, ll parent_score, ll current_score, ll result)
{
	ll base_score = parent_score + Cs[idx];
	REPD(i, 0, edges[idx].size())
	{
		base_score += edges[idx][i].second;
	}

	visited[idx] = true;
	REPD(i, 0, edges[idx].size())
	{
		auto node = edges[idx][i].first;
		if (visited[node])
		{
			continue;
		}
		auto next_score = current_score + base_score - edges[idx][i].second * 2LL;
		result = min(result, next_score);
		result = dfs2(node, base_score - edges[idx][i].second, next_score, result);
	}

	return result;
}

int solve()
{
	cin >> N;

	edges = make_multiple_vector(make_pair(0LL, 0LL), N, 0);
	visited = make_multiple_vector(false, N);
	ll a, b, c;
	REPD(i, 0, N - 1)
	cin >> a >> b, --a, --b, edges[a].emplace_back(b, 0), edges[b].emplace_back(a, 0);
	Cs.reserve(N);
	REPD(i, 0, N)
	cin >> c, Cs.emplace_back(c);

	auto [_, base_score] = dfs1(0, 0);

	visited = make_multiple_vector(false, N);
	auto result = dfs2(0, 0, base_score, base_score);
	RET(result);

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
