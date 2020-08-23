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

ll dfs(ll node, vector<vector<ll>>& edges, vector<ll>& prev_nodes){
	REPI(next_node, edges[node]) {
		if (prev_nodes[next_node] == -1) continue;
		if (prev_nodes[next_node] >= 0) {
			prev_nodes[next_node] = node;
			return next_node;
		}
		prev_nodes[next_node] = node;
		ll base_node = dfs(next_node, edges, prev_nodes);
		if (base_node != -1) return base_node;
		prev_nodes[next_node] = -1;
	}

	return -1;
}

ll get_cycle(vector<vector<ll>>& edges, vector<ll>& prev_nodes) {
	REPD(i, 0, edges.size()) {
		if (prev_nodes[i] == -2) {
			ll start_node = dfs(i, edges, prev_nodes);
			if (start_node != -1) return start_node;
			while(prev_nodes[i] != -2) ++i;
		}
	}
	return -1;
}

stack<ll> get_shortest_cycle_from_start_node(ll start_node, vector<vector<ll>>& edges, set<ll>& cycle_nodes) {
	queue<ll> que;
	que.emplace(start_node);
	vector<ll> prev_bfs_nodes(edges.size(), -1);
	while (!que.empty()) {
		ll node = que.front();
		que.pop();
		REPI(next_node, edges[node]) {
			if (next_node == start_node) {
				prev_bfs_nodes[next_node] = node;
				goto loop_end;
			}
			if (cycle_nodes.find(next_node) == cycle_nodes.end()) continue;
			if (prev_bfs_nodes[next_node] != -1) continue;
			prev_bfs_nodes[next_node] = node;
			que.emplace(next_node);
		}
	}
loop_end:
	stack<ll> results;
	ll prev_node = prev_bfs_nodes[start_node];
	while (prev_node != start_node) {
		results.emplace(prev_node + 1LL);
		prev_node = prev_bfs_nodes[prev_node];
	}
	results.emplace(start_node + 1);

	return results;
}

int solve() {
	ll n, m;
	cin >> n >> m;

	vector<vector<ll>> edges(n);
	ll a, b;
	REPD(i, 0, m) {
		cin >> a >> b;
		--a, --b;
		edges[a].emplace_back(b);
	}

	vector<ll> prev_dfs_nodes(n, -2);
	ll base_node = get_cycle(edges, prev_dfs_nodes);
	if (base_node == -1) RET(-1);

	set<ll> cycle_nodes;
	cycle_nodes.insert(base_node);
	ll prev_node = prev_dfs_nodes[base_node];
	while (prev_node != base_node) {
		cycle_nodes.insert(prev_node);
		prev_node = prev_dfs_nodes[prev_node];
	}

	stack<ll> best_results;
	REPI(start_node, cycle_nodes) {
		stack<ll> results = get_shortest_cycle_from_start_node(start_node, edges, cycle_nodes);
		if(best_results.size() == 0 || results.size() < best_results.size()) {
			best_results = results;
		}
	}

	cout << best_results.size() << endl;	
	while(!best_results.empty()) {
		cout << best_results.top() << endl;
		best_results.pop();
	}

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
