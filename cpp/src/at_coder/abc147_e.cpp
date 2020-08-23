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

int solve() {
	ll h, w;
	cin >> h >> w;

	vector<vector<ll>> values(h, vector<ll>(w));
	ll v;
	REPD(i, 0, h) REPD(j, 0, w) {
		cin >> v;
		values[i][j] = v;
	}
	REPD(i, 0, h) REPD(j, 0, w) {
		cin >> v;
		values[i][j] = abs(values[i][j] - v);
	}

	vector<vector<vector<bool>>> dps(h, vector<vector<bool>>(w, vector<bool>(80 * 80 * 2 + 1)));
	dps[0][0][values[0][0]] = true;
	REPD(i, 0, h) REPD(j, 0, w) {
		if (i > 0) {
			REPD(k, 0, 80 * 80 * 1) {
				if (dps[i - 1][j][k]) {
					dps[i][j][abs(k + values[i][j])] = true;
					dps[i][j][abs(k - values[i][j])] = true;
				}
			}
		}
		if (j > 0) {
			REPD(k, 0, 80 * 80 * 1) {
				if (dps[i][j - 1][k]) {
					dps[i][j][abs(k + values[i][j])] = true;
					dps[i][j][abs(k - values[i][j])] = true;
				}
			}
		}
	}

	REPD(i, 0, 80 * 80 * 2 + 1) if (dps[h - 1][w - 1][i]) RET(i);

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
