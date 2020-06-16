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

ll get_grundy(ll a, ll k) {
	if (a < k) return 0;
	if (a % k == 0) return a / k;

	while (a > k * k) {
		a -= a / k + 1LL;
		if (a % k == 0) return a / k;
	}

	while (a >= k) {
		ll period = a / k + 1LL;
		a -= ((a % k) / period) * period;
		if (a % k == 0) return a / k;
		a -= period;
	}

	return 0;
}

int solve() {
	ll n;
	cin >> n;

	ll res = 0;
	ll a, k;
	for (ll i = 0; i < n; ++i) {
		cin >> a >> k;
		ll grundy = get_grundy(a, k);
		res ^= grundy;
	}

	cout << (res != 0LL ? "Takahashi": "Aoki") << endl;

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
