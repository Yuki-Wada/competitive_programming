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

	vector<tuple<ll, ll, ll>> triplets;
	for (ll i = 0; i <= 9; ++i) {
		ll sum = n;
		for (ll j = 0; j <= k; ++j) {
			sum -= (i + j) % 10;
			sum -= (i + j) / 10;
		}

		ll incr_count = max(i + k - 9LL, 0LL);
		for (ll j = 0;; ++j) {
			if ((k + 1 - incr_count) * j * 9 > sum) break;
			if ((sum - (k + 1 - incr_count) * j * 9) % (k + 1) != 0) continue;
			triplets.emplace_back((sum - (k + 1 - incr_count) * j * 9) / (k + 1), j, i);
		}
	}
	if (triplets.empty()) {
		cout << -1 << endl;
		return 0;
	}

	string res_str = string(1000, '1');
	for (ll i = 0; i < triplets.size(); ++i){
		ll digit_sum, seq9, place1;
		tie(digit_sum, seq9, place1) = triplets[i];
		
		string num_str;
		num_str += to_string(place1);
		num_str += string(seq9, '9');
		bool first = true;
		while (digit_sum > 0) {
			if (first) {
				ll digit = min(digit_sum, 8LL);
				num_str += to_string(digit);
				digit_sum -= digit;
				first = false;
			}
			else {
				ll digit = min(digit_sum, 9LL);
				num_str += to_string(digit);
				digit_sum -= digit;
			}
		}
		reverse(num_str.begin(), num_str.end());

		if (res_str.size() > num_str.size()) res_str = num_str;
		else if (res_str.size() == num_str.size() && res_str > num_str) res_str = num_str;
	}

	cout << res_str << endl;

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	ll t;
	cin >> t;
	for (ll i = 0; i < t; ++i) {
		solve();
	}

	return 0;
}
