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

	return dists;
}

int solve() {
	ll n, m, t;
	cin >> n >> m >> t;

	ll black_count = 0;
	vector<vector<bool>> cells(n, vector<bool>(m));
	string s;
	for (ll i = 0; i < n; ++i) {
		cin >> s;
		for (ll j = 0; j < s.size(); ++j) {
			cells[i][j] = s[j] == '1';
			black_count += cells[i][j];
		}
	}

	if (n == 1 && m == 1) {
		ll row, col, p;
		for (ll i = 0; i < t; ++i) {
			cin >> row >> col >> p;
			--row, --col;
			cout << cells[0][0] << endl;
		}
		return 0;
	}

	vector<vector<bool>> is_surrounded(n, vector<bool>(m, false));
	for (ll i = 0; i < n; ++i) {
		for (ll j = 0; j < s.size(); ++j) {
			if (i + 1 < n) {
				if (cells[i + 1][j] == cells[i][j]) continue;
			}
			if (i - 1 >= 0) {
				if (cells[i - 1][j] == cells[i][j]) continue;
			}
			if (j + 1 < m) {
				if (cells[i][j + 1] == cells[i][j]) continue;
			}
			if (j - 1 >= 0) {
				if (cells[i][j - 1] == cells[i][j]) continue;
			}
			is_surrounded[i][j] = true;
		}
	}

	for (ll i = 0; i < n; ++i) {
		for (ll j = 0; j < s.size(); ++j) {
			if (!is_surrounded[i][j]) goto loop_break;
		}
	}

	{
		ll row, col, p;
		for (ll i = 0; i < t; ++i) {
			cin >> row >> col >> p;
			--row, --col;
			cout << cells[row][col] << endl;
		}

		return 0;
	}

loop_break:
	vector<vector<ll>> keep_nums(n, vector<ll>(m));
	vector<vector<pair<ll, ll>>> adjacency_list(m * n + 1);
	for (ll i = 0; i < n; ++i) {
		for (ll j = 0; j < m; ++j) {
			if (!is_surrounded[i][j]) continue;
			bool exist_cell_not_surrounded = false;
			if (i + 1 < n) {
				if (!is_surrounded[i + 1][j]) exist_cell_not_surrounded = true;
				else {
					ll from = i * m + j + 1;
					ll to = (i + 1) * m + j + 1;
					adjacency_list[from].emplace_back(to, 1);
				}
			}
			if (i - 1 >= 0) {
				if (!is_surrounded[i - 1][j]) exist_cell_not_surrounded = true;
				else {
					ll from = i * m + j + 1;
					ll to = (i - 1) * m + j + 1;
					adjacency_list[from].emplace_back(to, 1);
				}
			}
			if (j + 1 < m) {
				if (!is_surrounded[i][j + 1]) exist_cell_not_surrounded = true;
				else {
					ll from = i * m + j + 1;
					ll to = i * m + (j + 1) + 1;
					adjacency_list[from].emplace_back(to, 1);
				}
			}
			if (j - 1 >= 0) {
				if (!is_surrounded[i][j - 1]) exist_cell_not_surrounded = true;
				else {
					ll from = i * m + j + 1;
					ll to = i * m + (j - 1) + 1;
					adjacency_list[from].emplace_back(to, 1);
				}
			}
			if (exist_cell_not_surrounded) {
				ll from = 0;
				ll to = i * m + j + 1;
				adjacency_list[from].emplace_back(to, 1);
			}
		}
	}
	auto dists = dijkstra(adjacency_list);
	for (ll i = 0; i < n; ++i) {
		for (ll j = 0; j < m; ++j) {
			if (dists[i * m + j + 1] < (1LL << 58LL)) {
				keep_nums[i][j] = dists[i * m + j + 1];
			}
		}
	}

	ll row, col, p;
	for (ll i = 0; i < t; ++i) {
		cin >> row >> col >> p;
		--row, --col;
		if (p <= keep_nums[row][col]) {
			cout << cells[row][col] << endl;
		}
		else {
			cout << ((cells[row][col] + p - keep_nums[row][col]) % 2) << endl;
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
