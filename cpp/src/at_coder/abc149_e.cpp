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

	vector<ll> as(n);
	REPD(i, 0, n) cin >> as[i];
	sort(as.begin(), as.end());

	ll low = as[0] * 2LL, high = as[n - 1LL] * 2LL + 1LL;
	ll mid = (high + low) / 2LL;
	while (high - low >= 2) {
		ll count = 0;
		REPD(i, 0, n) {
			count += distance(lower_bound(as.begin(), as.end(), mid - as[i]), as.end());
		}
		if (count >= m) {
			low = mid;
		}
		else {
			high = mid;
		}
		mid = (high + low) / 2LL;
	}

	vector<ll> accums(n);
	ll accum = 0;
	REPD(i, 0, n) {
		accum += as[n - 1LL - i];
		accums[n - 1LL - i] = accum;
	}

	ll res = 0;
	ll count = 0;
	REPD(i, 0, n) {
		auto iter = lower_bound(as.begin(), as.end(), high - as[i]);
		count += distance(iter, as.end());
		ll idx = distance(as.begin(), iter);
		if (idx < as.size()) {
			res += (as.size() - idx) * as[i];
			res += accums[idx];
		}
	}
	res += (m - count) * low;
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
