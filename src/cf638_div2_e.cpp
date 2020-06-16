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
	ll n, k;
	cin >> n >> k;

	ll sum_a = 0, sum_b = 0;
	vector<ll> as(n);
	vector<ll> bs(n);
	for (ll i = 0; i < n; ++i) {
		cin >> as[i] >> bs[i];
		sum_a += as[i];
		sum_b += bs[i];
	}

	vector<bool> can_subtract(k, false);
	vector<bool> temp_subtract(k, false);
	can_subtract[0] = 2;
	for (ll i = 0; i < n; ++i) {
		ll right = min(as[i], k - 1LL);
		if (right + bs[i] < k) {
			continue;
		}
		ll left = max(right - (right + bs[i] - k), 1LL);

		for (ll j = 0; j < k; ++j) {
			temp_subtract[j] = false;
		}
		for (ll j = 0; j < k; ++j) {
			for (ll l = left; l <= right; ++l) {
				if (can_subtract[j]) {
					temp_subtract[(j + l) % k] = true;
				}
			}
		}
		for (ll j = 0; j < k; ++j) {
			if (temp_subtract[j]) {
				can_subtract[j] = true;
			}
		}
	}

	ll res = 0;
	for (ll i = 0; i < k; ++i) {
		if (can_subtract[i] > 0) {
			res = max(res, sum_a / k + sum_b / k + (((sum_a + k) % k) + ((sum_b + k) % k) - ((sum_a - i + k) % k) - ((sum_b + i + k) % k)) / k);
		}
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
