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

ll xor_a_bs(ll a, ll bit, const vector<ll>& residual_bs) {
	ll count = 0;
	ll residual_a = a % (1LL << (bit + 1LL));
	
	count += distance(lower_bound(residual_bs.begin(), residual_bs.end(), (1LL << bit) - residual_a), residual_bs.end());
	count -= distance(lower_bound(residual_bs.begin(), residual_bs.end(), (1LL << bit) * 2LL - residual_a), residual_bs.end());
	count += distance(lower_bound(residual_bs.begin(), residual_bs.end(), (1LL << bit) * 3LL - residual_a), residual_bs.end());
	count -= distance(lower_bound(residual_bs.begin(), residual_bs.end(), (1LL << bit) * 4LL - residual_a), residual_bs.end());

	return count % 2LL;
}

int solve() {
	ll n;
	cin >> n;

	vector<ll> as(n);
	vector<ll> bs(n);
	for (ll i = 0; i < n; ++i) cin >> as[i];
	for (ll i = 0; i < n; ++i) cin >> bs[i];

	ll res = 0;
	vector<ll> residual_bs(n);
	for (ll i = 0; i < 29; ++i) {
		for (ll j = 0; j < n; ++j) {
			residual_bs[j] = bs[j] % (1LL << (i + 1LL));
		}
		sort(residual_bs.begin(), residual_bs.end());
		for (ll j = 0; j < n; ++j) {
			res ^= (xor_a_bs(as[j], i, residual_bs) << i);
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
