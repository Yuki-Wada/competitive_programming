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

ll calc_dps(
	ll r, ll c, ll row_item_count,
	vector<vector<vector<ll>>>& dps,
	const vector<vector<ll>>& items)
{
	if (r < 0) return 0;
	if (c < 0) return 0;
	if (row_item_count < 0) return 0;
	if (dps[r][c][row_item_count] != -1) return dps[r][c][row_item_count];

	ll res = 0;
	if (items[r][c] == 0) {
		res = max(res, calc_dps(r - 1, c, 2, dps, items));
		res = max(res, calc_dps(r, c - 1, row_item_count, dps, items));
	}
	else
	{
		res = max(res, calc_dps(r - 1, c, 2, dps, items) + items[r][c]);
		res = max(res, calc_dps(r, c - 1, row_item_count, dps, items));
		if (row_item_count > 0) {
			res = max(res, calc_dps(r, c - 1, row_item_count - 1, dps, items) + items[r][c]);
		}
	}
	dps[r][c][row_item_count] = res;

	return dps[r][c][row_item_count];
}

int solve() {
	ll R, C, K;
	cin >> R >> C >> K;
	
	vector<vector<ll>> items(R, vector<ll>(C));
	ll r, c, v;
	REPD(i, 0, K) {
		cin >> r >> c >> v;
		--r, --c;
		items[r][c] = v;
	}

	vector<vector<vector<ll>>> dps(R, vector<vector<ll>>(C, vector<ll>(3, -1)));
	RET(calc_dps(R - 1LL, C - 1LL, 2LL, dps, items));

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
