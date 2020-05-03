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

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __line__ << ")" << " " << __file__ << endl

void dfs(const vector<vector<ll>>& edges, const vector<ll>& nums, ll node, vector<ll>& elem_max, vector<ll>& results) {
	auto iter = lower_bound(elem_max.begin(), elem_max.end(), nums[node]);
	ll prev_val = *iter;
	*iter = nums[node];
	results[node] = distance(elem_max.begin(), lower_bound(elem_max.begin(), elem_max.end(), (1LL << 58LL)));
	for (ll i = 0; i < edges[node].size(); ++i) {
		dfs(edges, nums, edges[node][i], elem_max, results);
	}
	*iter = prev_val;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll N;
	cin >> N;

	vector<ll> nums(N);
	for (ll i = 0; i < N; ++i) {
		cin >> nums[i];
	}

	vector<vector<ll>> edges(N);
	ll u, v;
	for (ll i = 0; i < N - 1; ++i) {
		cin >> u >> v;
		--u, --v;
		edges[u].emplace_back(v);
		edges[v].emplace_back(u);
	}

	vector<vector<ll>> dir_edges(N);
	vector<bool> is_checked(N, false);
	queue<ll> queue;
	queue.push(0);
	is_checked[0] = true;
	while (!queue.empty()) {
		ll node = queue.front();
		queue.pop();
		for (ll i = 0; i < edges[node].size(); ++i) {
			if (!is_checked[edges[node][i]]) {
				dir_edges[node].emplace_back(edges[node][i]);
				queue.push(edges[node][i]);
				is_checked[edges[node][i]] = true;
			}
		}
	}

	vector<ll> results(N);
	vector<ll> elem_max(N, (1LL << 60LL));
	dfs(dir_edges, nums, 0, elem_max, results);

	for (ll i = 0; i < results.size(); ++i) {
		cout << results[i] << endl;
	}

	return 0;
}
