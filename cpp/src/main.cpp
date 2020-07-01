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
	ll n, p;
	cin >> n >> p;

	vector<ll> as(n);
	for (ll i = 0; i < n; ++i) cin >> as[i];
	sort(as.begin(), as.end());

	ll min_x = 0;
	for (ll i = 0; i < n; ++i) {
		min_x = max(as[i] - i, min_x);
	}
	for (ll i = 0; i < n; ++i) {
		as[i] -= min_x;
	}
	ll max_a = as[n - 1LL];

	rmq query(max_a + 1LL);
	for (ll i = 0; i <= max_a; ++i) {
		ll num = distance(as.begin(), upper_bound(as.begin(), as.end(), i));
		num -= i;
		query.update(i, -num);
	}

	vector<ll> xs;
	for (ll i = 0; i <= max_a; ++i) {
		ll comb = - query.query(i, max_a + 1LL) + i;
		if (comb < p) {
			xs.emplace_back(i + min_x);
		}
		else {
			break;
		}
	}

	cout << xs.size() << endl;
	for (ll i = 0; i < xs.size(); ++i) {
		cout << xs[i];
		if (i + 1 < xs.size()) cout << " ";
	}
	cout << endl;

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
