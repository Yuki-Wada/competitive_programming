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

ll floor_sum(ll n, ll q, ll t) {
	ll d = n % q;
	ll res = (n / q) * (t + 1LL);
	if (t <= d) {
		return (n / q) * (t + 1LL);
	}
	t -= d + 1;

	ll a = t / q;
	res -= a * (a + 1LL) / 2LL * q;
	res -= (a + 1LL) * (t % q + 1LL);

	return res;
}

int solve() {
	ll n , k;
	cin >> n >> k;

	if (k == 0) {
		cout << n * n << endl;
		return 0;
	}

	ll res = 0;
	res += (n - k) * (n - k + 1LL) / 2LL;

	for (ll q = 1; q * (k + 1LL) + k <= n; ++q) {
		ll l = (n - q) / (q + 1LL);
		res -= (k + l) * (l - k + 1LL) / 2LL;
		res += floor_sum(n, q, l) - floor_sum(n, q, k - 1LL);
	}

	cout << res << endl;

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
