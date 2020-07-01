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
	ll n, a, b;
	cin >> n >> a >> b;

	if (a + b - 1 > n || a * b < n) {
		cout << -1 << endl;
		return 0;
	}

	vector<ll> nums(a);
	nums[0] = b;
	for (ll i = 1; i < a; ++i) {
		ll num = n - b;
		nums[i] = num / (a - 1LL) + (i <= (num % (a - 1LL)) ? 1 : 0);
	}
	ll res = 0;
	for (ll i = 0; i < a; ++i) {
		res += nums[i];
		for (ll j = 0; j < nums[i]; ++j) {
			cout << res - j;
			if (i + 1 != a || j + 1 != nums[i]) {
				cout << " ";
			}
		}
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
