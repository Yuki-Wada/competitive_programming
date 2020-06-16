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

int get_x_count(ll a, ll val) {
	if (a - val - 1 < 0) return 0;

	double sol = (3.0 + sqrt(9.0 + 12.0 * (a - val - 1))) / 6.0;
	return min(ll(sol), a);
}

int solve() {
	ll n, k;
	cin >> n >> k;

	ll max_thre = 0, min_thre;
	vector<ll> as(n);
	for (ll i = 0; i < n; ++i) {
		cin >> as[i];
		max_thre = max(max_thre, as[i]);
	}

	max_thre = max_thre * max_thre * 4LL;
	min_thre = -max_thre;
	ll mid_thre = (max_thre + min_thre) / 2LL;
	while (max_thre - min_thre >= 2LL) {
		ll count = 0;
		for (ll i = 0; i < n; ++i) {
			count += get_x_count(as[i], mid_thre);
		}
		
		if (count >= k) {
			min_thre = mid_thre;
		}
		else {
			max_thre = mid_thre;
		}
		mid_thre = (max_thre + min_thre) / 2LL;
	}
	
	ll count = 0;
	for (ll i = 0; i < n; ++i) {
		count += get_x_count(as[i], max_thre);
	}
	ll target = (count >= k ? max_thre : min_thre) + 1;
	
	count = k;
	for (ll i = 0; i < n; ++i) {
		count -= get_x_count(as[i], target);
	}

	vector<ll> bs(n);
	for (ll i = 0; i < n; ++i) {
		bs[i] += get_x_count(as[i], target);
		if (count > 0) {
			ll x = bs[i] + 1;
			if (as[i] - x * x * 3LL + x * 3LL - 1 == target - 1) {
				++bs[i];
				--count;
			}
		}
	}

	for (ll i = 0; i < n; ++i) {
		cout << bs[i];
		if (i + 1 < n) {
			cout << " ";
		}
		else {
			cout << endl;
		}
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
