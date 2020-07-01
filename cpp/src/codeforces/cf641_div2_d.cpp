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

int solve_simple_query() {
	ll n, k;
	cin >> n >> k;

	bool exist_k = false;
	vector<ll> as(n);
	for (ll i = 0; i < n; ++ i) {
		cin >> as[i];
		if (as[i] == k) {
			exist_k = true;
		}
	}

	if (!exist_k) {
		cout << "no" << endl;
		return 0;
	}

	if (n == 1){
		cout << "yes" << endl;
		return 0;
	}

	for (ll i = 0; i + 1< n; ++i) {
		if (as[i] >= k && as[i + 1] >= k) {
			cout << "yes" << endl;
			return 0;
		}
		if (i + 2 < n && as[i] >= k && as[i + 2] >= k) {
			cout << "yes" << endl;
			return 0;
		}
	}

	cout << "no" << endl;

	return 0;
}

int solve() {
	ll t;
	cin >> t;
	for (ll i = 0; i < t; ++i) {
		solve_simple_query();
	}

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
