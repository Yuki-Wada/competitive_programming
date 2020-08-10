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

vector<vector<ll>> dps;

ll calc_dps(ll idx, ll t, const vector<pair<ll, ll>>& ABs) {
	if (idx < 0) return 0;
	if (t < 0) return 0;
	if (dps[idx][t] != -1) return dps[idx][t];

	ll res = calc_dps(idx - 1, t, ABs);
	if (t >= ABs[idx].first) {
		res = max(res, calc_dps(idx - 1, t - ABs[idx].first, ABs) + ABs[idx].second);
	}

	dps[idx][t] = res;
	return dps[idx][t];
}

int solve() {
	ll N, T;
	cin >> N >> T;

	vector<pair<ll, ll>> ABs(N);
	ll A, B;
	REPD(i, 0, N) {
		cin >> A >> B;
		ABs[i] = {A, B};
	}
	sort(ABs.begin(), ABs.end());

	dps = vector<vector<ll>>(N, vector<ll>(T, -1));
	ll res = ABs[0].second;
	REPD(i, 0, N) res = max(res, ABs[i].second + calc_dps(i - 1, T - 1, ABs));

	RET(res);
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
