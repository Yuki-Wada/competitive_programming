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

ll A, B, C, D;
map<ll, ll> memo;

ll coin(ll N) {
	if (memo.count(N) > 0) return memo[N];

	ll res = 1LL << 60LL;

	if (N % 2LL == 0LL) {
		res = min(res, coin(N / 2LL) + A);
	}
	else {
		ll residual = 1LL;
		res = min(res, coin(N / 2LL) + A + residual * D);
		res = min(res, coin(N / 2LL + 1LL) + A + (2LL - residual) * D);
	}
	if (N % 3LL == 0LL) {
		res = min(res, coin(N / 3LL) + B);
	}
	else {
		ll residual = N % 3LL;
		res = min(res, coin(N / 3LL) + B + residual * D);
		res = min(res, coin(N / 3LL + 1LL) + B + (3LL - residual) * D);
	}
	if (N % 5LL == 0LL) {
		res = min(res, coin(N / 5LL) + C);
	}
	else {
		ll residual = N % 5LL;
		res = min(res, coin(N / 5LL) + C + residual * D);
		res = min(res, coin(N / 5LL + 1LL) + C + (5LL - residual) * D);
	}

	memo[N] = res;
	if (res / N >= D) {
		memo[N] = N * D;
	}

	return memo[N];
}

int solve() {
	ll N;
	cin >> N >> A >> B >> C >> D;

	memo.clear();
	memo[0] = 0;
	memo[1] = D;

	ll res = coin(N);

	cout << res << endl;

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll T;
	cin >> T;
	for (ll i = 0; i < T; ++i) {
		solve();
	}

	return 0;
}
