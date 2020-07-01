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

	vector<ll> as(n);
	for (ll i = 0; i < n; ++i) {
		cin >> as[i];
	}

	ll target = 0;
	for (ll i = 2; i < n; ++i) {
		target ^= as[i];
	}

	ll res = (1LL << 60LL);

	ll lower_a0 = as[0] & ((1LL << 20LL) - 1LL);
	ll lower_a1 = as[1] & ((1LL << 20LL) - 1LL);

	bool decrease_upper_digit_in_a1 = false;
	bool increase_upper_digit_in_a2 = false;
	bool can_candidate = true;
	vector<ll> candidates;
	for (ll i = 0; i < (1LL << 20LL); ++i) {
		if (i < as[0]) {
			if (decrease_upper_digit_in_a1 ^ (lower_a0 < i)) {
				decrease_upper_digit_in_a1 = lower_a0 < i;
				can_candidate = true;
			}
			if (increase_upper_digit_in_a2 ^ (lower_a1 + i >= (1LL << 20LL))) {
				increase_upper_digit_in_a2 = lower_a1 + i >= (1LL << 20LL);
				can_candidate = true;
			}
			if ((((as[0] - i) ^ (as[1] + i) ^ target) & ((1LL << 20LL) - 1LL)) == 0LL) {
				if (can_candidate) {
					candidates.emplace_back(i);
					can_candidate = false;
				}
			}
		}
	}

	for (auto candidate : candidates) {
		for (ll i = candidate; i < as[0]; i += (1LL << 20LL)) {
			if (((as[0] - i) ^ (as[1] + i) ^ target) == 0LL) {
				res = min(res, i);
				break;
			}
		}
	}

	cout << (res != (1LL << 60LL) ? res: -1LL) << endl;

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
