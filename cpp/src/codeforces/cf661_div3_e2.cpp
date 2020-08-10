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

class Edge {
public:
	Edge(ll target, ll weight, ll cost) : target(target), weight(weight), cost(cost) {}
	ll target;
	ll weight;
	ll cost;
};

class WeightInfo {
public:
	WeightInfo() : weight(0), count(0), cost(0) {}
	WeightInfo(ll weight, ll count, ll cost) : weight(weight), count(count), cost(cost){}
	ll weight;
	ll count;
	ll cost;
};

ll dfs(
		Edge prev_edge,
		const vector<vector<Edge>>& edges,
		vector<bool>& visited,
		vector<WeightInfo>& weights
	)
{
	ll count = 0;
	ll next_node, next_weight, cost;

	bool is_leaf = true;
	REPI(edge, edges[prev_edge.target]) {
		next_node = edge.target;
		next_weight = edge.weight;
		if (visited[next_node]) continue;

		is_leaf = false;
		visited[next_node] = true;
		count += dfs(edge, edges, visited, weights);
	}

	if (is_leaf) {
		count = 1;
	}

	weights[prev_edge.target] = { prev_edge.weight, count, prev_edge.cost };
	return count;
}

int solve() {
	ll n, S;
	cin >> n >> S;

	vector<vector<Edge>> edges(n);
	ll u, v, w, c;
	REPD(i, 0, n - 1) {
		cin >> u >> v >> w >> c;
		--u, --v;
		edges[u].emplace_back(v, w, c);
		edges[v].emplace_back(u, w, c);
	}

	vector<bool> visited(n, false);
	vector<WeightInfo> weight_infos(n);
	visited[0] = true;
	dfs({0, 0, 0}, edges, visited, weight_infos);

	auto compare = [](WeightInfo a, WeightInfo b) {
		ll reduce_a = (a.weight - a.weight / 2LL) * a.count;
		ll reduce_b = (b.weight - b.weight / 2LL) * b.count;
		return reduce_a < reduce_b;
	};

	priority_queue<WeightInfo, vector<WeightInfo>, decltype(compare)> pq1(compare);
	priority_queue<WeightInfo, vector<WeightInfo>, decltype(compare)> pq2(compare);
	REPD(i, 1, n) {
		if (weight_infos[i].weight == 0) continue;
		if (weight_infos[i].cost == 1) pq1.emplace(weight_infos[i]);
		else pq2.emplace(weight_infos[i]);
	}

	vector<ll> reduce1;
	while (!pq1.empty()) {
		auto weight_info = pq1.top();
		pq1.pop();
		reduce1.emplace_back((weight_info.weight - weight_info.weight / 2LL) * weight_info.count);
		if (weight_info.weight / 2LL > 0) {
			pq1.emplace(weight_info.weight / 2LL, weight_info.count, weight_info.cost);
		}
	}
	vector<ll> reduce2;
	while (!pq2.empty()) {
		auto weight_info = pq2.top();
		pq2.pop();
		reduce2.emplace_back((weight_info.weight - weight_info.weight / 2LL) * weight_info.count);
		if (weight_info.weight / 2LL > 0) {
			pq2.emplace(weight_info.weight / 2LL, weight_info.count, weight_info.cost);
		}
	}
	
	reduce1.emplace_back(0);
	reverse(reduce1.begin(), reduce1.end());
	REPD(i, 1, reduce1.size()) reduce1[i] += reduce1[i - 1];
	reduce2.emplace_back(0);
	reverse(reduce2.begin(), reduce2.end());
	REPD(i, 1, reduce2.size()) reduce2[i] += reduce2[i - 1];

	ll res = MAX_VALUE;
	REPD(i, 0, reduce2.size()) {
		auto s2 = reduce2[i];
		if (S - s2 < 0) break;
		auto dist = distance(reduce1.begin(), upper_bound(reduce1.begin(), reduce1.end(), S - s2)) - 1LL;
		res = min(res, ll((reduce1.size() - dist - 1LL) + (reduce2.size() - i - 1LL) * 2LL));
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
