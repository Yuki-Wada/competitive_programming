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
	ll n;
	cin >> n;

	vector<tuple<ll, ll, ll>> xyps;
	ll x, y, p;
	REPD(i, 0, n){
		cin >> x >> y >> p;
		xyps.emplace_back(x, y, p);
	}

	vector<vector<ll>> min_xs(n, vector<ll>(1LL << n, MAX_VALUE));
	vector<vector<ll>> min_ys(n, vector<ll>(1LL << n, MAX_VALUE));
	ll xk, yk, pk;
	REPD(i, 0, n) {
		REPD(j, 0, 1LL << n) {
			tie(x, y, p) = xyps[i];
			min_xs[i][j] = min(min_xs[i][j], abs(x));
			min_ys[i][j] = min(min_ys[i][j], abs(y));
			REPD(k, 0, n) {
				if ((j >> k) % 2LL == 1LL) {
					tie(xk, yk, pk) = xyps[k];
					min_xs[i][j] = min(min_xs[i][j], abs(x - xk));
					min_ys[i][j] = min(min_ys[i][j], abs(y - yk));
				}
			}
		}
	}

	ll status_count = 1;
	REPD(i, 0, n) status_count *= 3LL;

	vector<ll> results(n + 1, MAX_VALUE);
	REPD(i, 0, status_count) {
		ll status = i;
		ll status_x = 0, status_y = 0, line_count = 0;
		REPD(j, 0, n) {
			status_x <<= 1LL;
			status_y <<= 1LL;
			if (status % 3LL == 1LL) {
				status_x += 1LL;
				++line_count;
			}
			if (status % 3LL == 2LL) {
				status_y += 1LL;				
				++line_count;
			}
			status /= 3LL;
		}
		ll result = 0;
		REPD(j, 0, n) {
			tie(x, y, p) = xyps[j];
			result += p * min(min_xs[j][status_x], min_ys[j][status_y]);
		}
		results[line_count] = min(results[line_count], result);
	}

	REPD(i, 0, n + 1) cout << results[i] << endl;

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
