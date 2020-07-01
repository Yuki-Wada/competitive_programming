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

int solve() {
	ll N;
	cin >> N;

	vector<vector<ll>> dists(N, vector<ll>(N));
	vector<vector<ll>> walls(N, vector<ll>(N, 1));
	for (ll i = 0; i < N; ++i) {
		for (ll j = 0; j < N; ++j) {
			dists[i][j] = i + 1;
			dists[i][j] = min(dists[i][j], N - i);
			dists[i][j] = min(dists[i][j], j + 1);
			dists[i][j] = min(dists[i][j], N - j);
		}
	}

	ll res = 0;
	ll P;
	queue<pair<ll, ll>> check_queue;
	vector<vector<bool>> checked(N, vector<bool>(N, false));
	queue<pair<ll, ll>> for_rollback;
	for (ll i = 0; i < N * N; ++i) {
		cin >> P;
		--P;
		ll x, y;
		x = P / N;
		y = P % N;
		walls[x][y] = 0;
		res += --dists[x][y];

		check_queue.emplace(x, y);
		while (!check_queue.empty()) {
			tie(x, y) = check_queue.front();
			check_queue.pop();
			for_rollback.emplace(x, y);

			if (x + 1 < N) {
				if (!checked[x + 1][y] && dists[x + 1][y] > dists[x][y] + walls[x + 1][y]) {
					dists[x + 1][y] = dists[x][y] + walls[x + 1][y];
					check_queue.emplace(x + 1, y);
					checked[x + 1][y] = true;
				}
			}
			if (x - 1 >= 0) {
				if (!checked[x - 1][y] && dists[x - 1][y] > dists[x][y] + walls[x - 1][y]) {
					dists[x - 1][y] = dists[x][y] + walls[x - 1][y];
					check_queue.emplace(x - 1, y);
					checked[x - 1][y] = true;
				}
			}
			if (y + 1 < N) {
				if (!checked[x][y + 1] && dists[x][y + 1] > dists[x][y] + walls[x][y + 1]) {
					dists[x][y + 1] = dists[x][y] + walls[x][y + 1];
					check_queue.emplace(x, y + 1);
					checked[x][y + 1] = true;
				}
			}
			if (y - 1 >= 0) {
				if (!checked[x][y - 1] && dists[x][y - 1] > dists[x][y] + walls[x][y - 1]) {
					dists[x][y - 1] = dists[x][y] + walls[x][y - 1];
					check_queue.emplace(x, y - 1);
					checked[x][y - 1] = true;
				}
			}
		}

		while (!for_rollback.empty()) {
			tie(x, y) = for_rollback.front();
			for_rollback.pop();
			checked[x][y] = false;
		}
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
