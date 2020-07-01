//include
//------------------------------------------
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
#include <string>
#include <cstring>
#include <ctime>

#include <stdexcept>

using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

const ll MOD = 1000000007LL;
const double PI = 3.14159265358979323846;

//conversion
//------------------------------------------
inline int toint(string s) { int v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// for loop
#define REP(i, n) for ((i) = 0;(i) < (ll)(n);(i)++)

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __line__ << ")" << " " << __file__ << endl

void dfs(ll node, ll prev_node, const vector<vector<ll>>& tree, vector<vector<ll>>& results) {
	for (ll i = 0; i < tree[node].size(); ++i) dfs(tree[node][i], node, tree, results);
	if (prev_node < 0) return;
	if (results[node].size() % 2LL != 0LL) results[node].emplace_back(prev_node);
	else results[prev_node].emplace_back(node);
}

int solve() {
	ll n, m;
	cin >> n >> m;

	if (m % 2LL != 0LL) {
		cout << -1 << endl;
		return 0;
	}

	vector<vector<ll>> edges(n);
	ll a, b;
	for (ll i = 0; i < m; ++i) {
		cin >> a >> b;
		--a, --b;
		edges[a].emplace_back(b);
		edges[b].emplace_back(a);
	}

	vector<vector<ll>> results(n);
	vector<vector<ll>> tree(n);

	set<pair<ll, ll>> checked;
	vector<bool> visited(n, false);
	queue<ll> queue;
	queue.push(0);
	visited[0] = true;
	while (!queue.empty()) {
		ll node = queue.front();
		queue.pop();
		for (ll i = 0; i < edges[node].size(); ++i) {
			ll next_node = edges[node][i];

			if (checked.count(make_pair(node, next_node)) > 0 || checked.count(make_pair(next_node, node)) > 0) continue;
			checked.insert(make_pair(node, next_node));
			checked.insert(make_pair(next_node, node));

			if (visited[next_node]) results[node].emplace_back(next_node);
			else {
				tree[node].emplace_back(next_node);
				queue.push(next_node);
				visited[next_node] = true;
			}
		}
	}

	dfs(0, -1, tree, results);
	for (ll i = 0; i < n; ++i) {
		for (ll j = 0; j < results[i].size();++j) {
			cout << i + 1 << " " << results[i][j] + 1 << endl;
		}
	}

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();

	return 0;
}
