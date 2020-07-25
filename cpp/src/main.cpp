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
#define REPI(v, vs) for (auto v : vs)

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" << " " << __FILE__ << endl

int solve() {
	ll n;
	cin >> n;

	string A, B;
	cin >> A >> B;
	
	REPD(i, 0, n) if (A[i] > B[i]) RET(-1);

	vector<vector<bool>> adjs(20, vector<bool>(20, false));
	REPD(i, 0, n) {
		ll pos_a = A[i] - 'a';
		ll pos_b = B[i] - 'a';
		if (pos_a < pos_b) adjs[pos_a][pos_b] = true;
	}

	REPD(row_src, 0, 20) {
		REPD(row_tgt, row_src + 1, 20) {
			ll count = 0;
			REPD(col_dst, 0, 20) {
				if (adjs[row_src][col_dst] && adjs[row_tgt][col_dst]) ++count;
				if (count >= 2) break;
			}
			if (count >= 2) {
				adjs[row_src][row_tgt] = true;
			}
		}
	}

	vector<vector<ll>> path_counts(20, vector<ll>(20));
	REPD(col_dst, 0, 20) {
		for (ll row_src = col_dst - 1LL; row_src >= 0LL; --row_src) {
			if (!adjs[row_src][col_dst]) continue;
			for (ll i = 0; i < row_src; ++i) {
				path_counts[i][col_dst] += path_counts[i][row_src];
			}
			++path_counts[row_src][col_dst];
		}
	}
	ll res = 0;
	REPD(col_dst, 0, 20) {
		REPD(row_src, 0, 20) {
			if (adjs[row_src][col_dst]) ++res;
			if (path_counts[row_src][col_dst] > 1) {
				res -= path_counts[row_src][col_dst] - 1;
			}
		}
	}

	RET(res);

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll t;
	cin >> t;
	REPD(i, 0, t) solve();

	return 0;
}
