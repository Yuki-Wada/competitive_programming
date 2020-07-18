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

int solve() {
	ll n;
	cin >> n;

	vector<ll> as(n + 1);
	for (ll i = 1; i <= n; ++i) {
		cin >> as[i];
	}

	vector<ll> odd_sum(n + 1);
	vector<ll> even_sum(n + 1);
	for (ll i = 1; i <= n; i += 2) {
		odd_sum[i] = (i >= 2 ? odd_sum[i - 2] : 0LL) + as[i];
	}
	for (ll i = 2; i <= n; i += 2) {
		even_sum[i] = even_sum[i - 2] + as[i];
	}

	ll res = -1;
	for (ll i = 1; i <= n; ++i) {
		res = max(res, odd_sum[i] + (even_sum[n - 1LL] - even_sum[i - 1LL]));
	}
	for (ll i = 2; i <= n - 1LL; ++i) {
		res = max(res, even_sum[i] + (odd_sum[n] - odd_sum[i - 1LL]));
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
