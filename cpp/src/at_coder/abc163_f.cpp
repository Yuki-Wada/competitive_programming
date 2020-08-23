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

ll dfs_sub_tree_size(ll node, ll prev, const vector<vector<ll>>& edges, vector<ll>& sub_tree_size) {
	sub_tree_size[node] = 1;
	REPD(i, 0, edges[node].size()) {
		if (prev == edges[node][i]) continue;
		sub_tree_size[node] += dfs_sub_tree_size(edges[node][i], node, edges, sub_tree_size);
	}

	return sub_tree_size[node];
}

void dfs_subtraction(
		ll node, ll prev,
		const vector<vector<ll>>& edges,
		const vector<ll>& cs,
		const vector<ll>& sub_tree_size,
		vector<ll>& color_counts,
		vector<ll>& answers)
{
	ll color_count_in = color_counts[cs[node]];
	REPD(i, 0, edges[node].size()) {
		if (prev == edges[node][i]) continue;
		ll next = edges[node][i];
		ll next_color_count_in = color_counts[cs[node]];
		dfs_subtraction(next, node, edges, cs, sub_tree_size, color_counts, answers);
		ll node_remained = sub_tree_size[next] - (color_counts[cs[node]] - next_color_count_in);
		answers[cs[node]] -= node_remained * (node_remained + 1LL) / 2LL;
	}
	color_counts[cs[node]] = color_count_in + sub_tree_size[node];

	return;
}

int solve() {
	ll N;
	cin >> N;

	vector<ll> cs(N);
	REPD(i, 0, N) cin >> cs[i], --cs[i];
	vector<vector<ll>> edges(N);
	ll a, b;
	REPD(i, 1, N) {
		cin >> a >> b;
		--a, --b;
		edges[a].emplace_back(b);
		edges[b].emplace_back(a);
	}

	vector<ll> sub_tree_size(N);
	dfs_sub_tree_size(0, -1, edges, sub_tree_size);

	vector<ll> answers(N, N * (N + 1LL) / 2LL);
	vector<ll> color_counts(N);
	dfs_subtraction(0, -1, edges, cs, sub_tree_size, color_counts, answers);

	REPD(i, 0, N) {
		ll node_remained = N - color_counts[i];
		answers[i] -= node_remained * (node_remained + 1LL) / 2LL;
	}

	REPD(i, 0, N) cout << answers[i] << endl;

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
