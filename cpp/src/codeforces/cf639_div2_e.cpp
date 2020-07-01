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

bool is_cyclic_impl(ll node, const vector<vector<ll>>& edges, vector<int>& status, vector<ll>& result) {
	if (status[node] == 1) return true;
	if (status[node] == 0) {
		status[node] = 1;
		for (ll i = 0; i < edges[node].size(); ++i) {
			if (is_cyclic_impl(edges[node][i], edges, status, result)) return true;
		}
		status[node] = 2;
		result.emplace_back(node);
	}

	return false;
}

bool is_cyclic(const vector<vector<ll>>& edges, vector<int>& status, vector<ll>& result) {
	for (ll i = 0; i < edges.size(); ++i) {
		if (status[i] == 0 && is_cyclic_impl(i, edges, status, result)) return true;
	}
	reverse(result.begin(), result.end());
	return false;
}

int solve() {
	ll n, m;
	cin >> n >> m;

	vector<vector<ll>> edges(n);
	vector<vector<ll>> rev_edges(n);
	ll j, k;
	for (ll i = 0; i < m; ++i) {
		cin >> j >> k;
		--j, --k;
		edges[j].emplace_back(k);
		rev_edges[k].emplace_back(j);
	}

	vector<int> status(n, 0);
	vector<ll> result;
	result.reserve(n);
	if (is_cyclic(edges, status, result)) {
		cout << -1 << endl;
		return 0;
	}

	vector<ll> min_node(n);
	for (ll i = 0; i < n; ++i) {
		ll node = result[n - 1 - i];
		min_node[node] = node;
		for (ll j = 0; j < edges[node].size(); ++j) {
			min_node[node] = min(min_node[node], min_node[edges[node][j]]);
		}
	}

	vector<ll> min_rev_node(n);
	for (ll i = 0; i < n; ++i) {
		ll node = result[i];
		min_rev_node[node] = node;
		for (ll j = 0; j < rev_edges[node].size(); ++j) {
			min_rev_node[node] = min(min_rev_node[node], min_rev_node[rev_edges[node][j]]);
		}
	}

	ll count = 0;
	string qs;
	for (ll i = 0; i < n; ++i) {
		if (min_node[i] == i && min_rev_node[i] == i) ++count, qs += 'A';
		else qs += 'E';
	}
	
	cout << count << endl;
	cout << qs << endl;

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
