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

using Edge = pair<ll, ll>;

// 始点 s から各点への最短距離を返します。
// パス自体が存在しない場合は -1 を返します。
// 距離 lengths の各要素は非負である必要があります。
vector<ll> dijkstra(const vector<vector<pair<ll, ll>>>& adjacency_list, ll s = 0LL)
{
	using Vertex = ll;
	using Length = ll;

	// アルゴリズム本体
	using VertexInfo = pair<Length, Vertex>;
	priority_queue<VertexInfo, vector<VertexInfo>, greater<VertexInfo>> queue;
	vector<Length> dists(adjacency_list.size(), 1LL << 60);

	dists[s] = 0LL;
	queue.emplace(dists[s], s);
	while (!queue.empty())
	{
		Length l;
		Vertex v;
		tie(l, v) = queue.top();
		queue.pop();
		if (dists[v] < l) continue;
		for (auto& edge : adjacency_list[v])
		{
			Vertex to = get<0>(edge);
			Length length = get<1>(edge);
			if (dists[to] > dists[v] + length)
			{
				dists[to] = dists[v] + length;
				queue.emplace(dists[to], to);
			}
		}
	}
	return move(dists);
}

int solve() {
	ll N, M;
	cin >> N >> M;
	
	ll u, v;
	vector<vector<pair<ll, ll>>> adjacency_list(N);
	for (ll i = 0; i < M; ++i) {
		cin >> u >> v;
		--u, --v;
		adjacency_list[u].emplace_back(v, 1);
		adjacency_list[v].emplace_back(u, 1);
	}

	ll s;
	cin >> s;
	--s;

	ll K;
	cin >> K;

	vector<ll> ts(K);
	ll t;
	for (ll i = 0; i < K; ++i) {
		cin >> t;
		--t;
		ts[i] = t;
	}

	vector<ll> dists_from_start(K);
	auto dists = dijkstra(adjacency_list, s);
	for (ll i = 0; i < K; ++i) {
		dists_from_start[i] = dists[ts[i]];
	}

	vector<vector<ll>> dist_matrix(K, vector<ll>(K));
	for (ll i = 0; i < K; ++i) {
		dists = dijkstra(adjacency_list, ts[i]);
		for (ll j = 0; j < K; ++j) {
			dist_matrix[i][j] = dists[ts[j]];
		}
	}



	vector<vector<ll>> dps(1LL << K, vector<ll>(K, 1LL << 60LL));
	for (ll i = 0; i < K; ++i) {
		dps[(1LL << K) - 1LL][i] = 0;
	}

	for (ll state = (1LL << K) - 2; state >= 0; --state) {
		for (ll src = 0; src < K; ++src) {
			for (ll dst = 0; dst < K; ++dst) {
				if ((state & (1LL << dst)) == 0) {
					dps[state][src] = min(dps[state][src], dps[state | (1LL << dst)][dst] + dist_matrix[src][dst]);
				}
			}
		}
	}

	ll res = (1LL << 60LL);
	for (ll i = 0; i < K; ++i) {
		res = min(res, dists_from_start[i] + dps[0][i]);
	}

	cout << res << endl;

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
