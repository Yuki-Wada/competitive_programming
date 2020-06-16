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
	ll H, W, K;
	cin >> H >> W >> K;

	ll x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	--x1, --y1, --x2, --y2;

	vector<string> cs(H);
	for (ll i = 0; i < H; ++i) {
		cin >> cs[i];
	}

	vector<vector<ll>> res(H, vector<ll>(W, -1));
	vector<vector<bool>> que_popped(H, vector<bool>(W, false));

	queue<pair<ll, ll>> que;
	que.emplace(x2, y2);
	res[x2][y2] = 0;
	ll x, y;
	while (!que.empty()) {
		tie(x, y) = que.front();
		que.pop();
		que_popped[x][y] = true;
		for (ll i = 1; i <= K; ++i) {
			if (x - i < 0) break;
			if (cs[x - i][y] == '@') break;
			if (que_popped[x - i][y]) break;
			if (res[x - i][y] == -1) {
				que.emplace(x - i, y);
				res[x - i][y] = res[x][y] + 1;
			}
		}
		for (ll i = 1; i <= K; ++i) {
			if (x + i >= H) break;
			if (cs[x + i][y] == '@') break;
			if (que_popped[x + i][y]) break;
			if (res[x + i][y] == -1) {
				que.emplace(x + i, y);
				res[x + i][y] = res[x][y] + 1;
			}
		}
		for (ll i = 1; i <= K; ++i) {
			if (y - i < 0) break;
			if (cs[x][y - i] == '@') break;
			if (que_popped[x][y - i]) break;
			if (res[x][y - i] == -1) {
				que.emplace(x, y - i);
				res[x][y - i] = res[x][y] + 1;
			}
		}
		for (ll i = 1; i <= K; ++i) {
			if (y + i >= W) break;
			if (cs[x][y + i] == '@') break;
			if (que_popped[x][y + i]) break;
			if (res[x][y + i] == -1) {
				que.emplace(x, y + i);
				res[x][y + i] = res[x][y] + 1;
			}
		}
	}

	cout << res[x1][y1] << endl;

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
