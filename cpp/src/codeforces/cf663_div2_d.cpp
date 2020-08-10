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
	ll n, m;
	cin >> n >> m;

	vector<string> as_str(n);
	REPD(i, 0, n) cin >> as_str[i];

	if (n >= 4LL && m >= 4LL) RET(-1);
	if (n == 1LL || m == 1LL) RET(0);
	ll n_ = min(n, m), m_ = max(n, m);
	vector<vector<ll>> as(n_, vector<ll>(m_));
	REPD(i, 0, n_) {
		REPD(j, 0, m_) {
			if (n < m) as[i][j] = as_str[i][j] - '0';
			else as[i][j] = as_str[j][i] - '0';
		}
	}
	ll res = MAX_VALUE;
	if (n_ == 2LL) {
		REPD (up, 0, 2) {
			ll curr_res = 0;
			REPD(j, 0, m_) {
				if ((as[0][j] + as[1][j] + up + j) % 2 != 0) ++curr_res;
			}
			res = min(res, curr_res);
		}
	}
	else {
		REPD (up, 0, 2) {
			REPD (down, 0, 2) {
				ll curr_res = 0;
				REPD(j, 0, m_) {
					if (((as[0][j] + as[1][j] + up + j) % 2 != 0) || ((as[1][j] + as[2][j] + down + j) % 2 != 0)) ++curr_res;
				}
				res = min(res, curr_res);
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

	solve();
	// ll t;
	// cin >> t;
	// REPD(i, 0, t) solve();

	return 0;
}
