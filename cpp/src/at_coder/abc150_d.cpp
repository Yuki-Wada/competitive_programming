//include
//------------------------------------------
#include <string>
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
#include <cstring>
#include <ctime>

// namespace
using namespace std;

// type alias
using ll = long long;
using ull = unsigned long long;
using comp = complex<double>;

// constant
static const ll MOD = 1000000007LL;
static const double PI = 3.14159265358979323846;

// conversion
inline ll toint(string s) { ll v; istringstream sin(s); sin >> v; return v; }
template<class t> inline string tostring(t x) { ostringstream sout; sout << x; return sout.str(); }

// print
#define RET(x) return cout << x << endl, 0;

// for loop
#define REP(i, a, b) for ((i) = (ll)(a);(i) < (ll)(b);(i)++)
#define REPD(i, a, b) for (ll i = (ll)(a);(i) < (ll)(b);(i)++)
#define REPI(v, vs) for (auto& v : vs)

//debug
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" << " " << __FILE__ << endl

#define MAX_VALUE 9223372036854775807

inline ull get_gcd(ull a, ull b)
{
	if (b == 0)
	{
		return a;
	}
	return get_gcd(b, a % b);
}

int solve() {
	ll n, m;
	cin >> n >> m;

	vector<ll> as(n);
	REPD(i, 0, n) cin >> as[i];

	ll power_of_2 = -1;
	REPD(i, 0, n) {
		ll curr_power = 0;
		while(as[i] % 2LL == 0LL) {
			as[i] /= 2LL;
			++curr_power;
		}
		if (power_of_2 == -1) power_of_2 = curr_power;
		else if (power_of_2 != curr_power) RET(0);
	}

	ll base = 1;
	REPD(i, 1, power_of_2) base *= 2LL;

	ll slcm = as[0];
	if (slcm * base > m) RET(0);
	REPD(i, 1, n) {
		slcm *= as[i] / get_gcd(slcm, as[i]);
		if (slcm * base > m) RET(0);
	}

	RET(1LL + (m - slcm * base) / slcm / base / 2LL);
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	solve();
	// ll t;
	// cin >> t;
	// REPD(i, 0, t) solve();

	return 0;
}
