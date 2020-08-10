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
static const double PI = 3.14159265358979323846;

// conversion
inline ll toint(string s) { ll v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a);(i) < (ll)(b);(i)++)
#define REPD(i, a, b) for (ll i = (ll)(a);(i) < (ll)(b);(i)++)
#define REPI(v, vs) for (auto& v : vs)

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" << " " << __FILE__ << endl

#define MAX_VALUE 9223372036854775807

ll dfs(
		ll node, ll weight,
		const vector<vector<pair<ll, ll>>>& edges,
		vector<bool>& visited,
		vector<pair<ll, ll>>& weights)
{
	ll count = 0;
	ll next_node, next_weight;
	bool is_leaf = true;
	REPI(edge, edges[node]) {
		tie(next_node, next_weight) = edge;
		if (visited[next_node]) continue;

		is_leaf = false;
		visited[next_node] = true;
		count += dfs(next_node, next_weight, edges, visited, weights);
	}

	if (is_leaf) {
		count = 1;
	}

	weights[node] = { weight, count };
	return count;
}

int solve() {
	ll n, S;
	cin >> n >> S;

	vector<vector<pair<ll, ll>>> edges(n);
	ll u, v, w;
	REPD(i, 0, n - 1) {
		cin >> u >> v >> w;
		--u, --v;
		edges[u].emplace_back(v, w);
		edges[v].emplace_back(u, w);
	}

	vector<bool> visited(n, false);
	vector<pair<ll, ll>> weights(n);
	visited[0] = true;
	dfs(0, 0, edges, visited, weights);

	auto compare = [](pair<ll, ll> a, pair<ll, ll> b) {
		ll cost_a = (a.first - a.first / 2LL) * a.second;
		ll cost_b = (b.first - b.first / 2LL) * b.second;
		return cost_a < cost_b;
	};
	priority_queue<
		pair<ll, ll>,
		vector<pair<ll, ll>>,
		decltype(compare)
	> pq(compare);
	ll curr_S = 0;
	REPD(i, 1, n) {
		curr_S += weights[i].first * weights[i].second;
		pq.emplace(weights[i]);
	}
	ll res = 0;

	ll weight, count;
	while (curr_S > S) {
		tie(weight, count) = pq.top();
		pq.pop();
		pq.emplace(weight / 2LL, count);
		curr_S -= (weight - weight / 2LL) * count;
		++res;
	}

	RET(res);

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll t;
	cin >> t;
	REPD(i, 0, t) solve();

	return 0;
}
