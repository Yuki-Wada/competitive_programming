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

const ll MOD = 998244353LL;;
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
	ll A, B, C, D;
	cin >> A >> B >> C >> D;
	vector<vector<ll>> results = vector<vector<ll>>(C - A + 1, vector<ll>(D - B + 1));

	ll rd, lu, ld, res;
	results[0][0] = 1;
	for (ll k = 1; k <= C - A + D - B; ++k) {
		for (ll e = max(k - (D - B), 0LL); e <= C - A && 0 <= k - e; ++e) {
			ll f = k - e;

			rd = (e - 1 >= 0 ? results[e - 1][f] : 0);
			lu = (f - 1 >= 0 ? results[e][f - 1] : 0);
			ld = (e - 1 >= 0 && f - 1 >= 0 ? results[e - 1][f - 1] : 0);
			res = rd * (f + B) % MOD +
				lu * (e + A) % MOD -
				ld * (e + A - 1) % MOD * (f + B - 1) % MOD;
			res = (res + MOD) % MOD;

			results[e][f] = res;
		}
	}

	cout << results[C - A][D - B] << endl;

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
