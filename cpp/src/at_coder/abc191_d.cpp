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
// static const ll MOD = (1LL << 61LL) - 1LL;
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
#ifdef LOCAL_ENV
#define DUMP(x)  cerr << #x << " = " << (x) << endl
#define DEBUG(x) cerr << #x << " = " << (x) << " (l" << __LINE__ << ")" << " " << __FILE__ << endl
#else
#define DUMP(x)
#define DEBUG(x)
#endif

#define MAX_VALUE 9223372036854775807LL

template <ull N, class T, class... Args, std::enable_if_t<N == 0, int> = 0>
auto make_multiple_vector(Args... args) {
    return T(args...);
}

template <ull N, class T, class... Args, std::enable_if_t<N != 0, int> = 0>
auto make_multiple_vector(ull size, Args... args) {
    using value_type = std::decay_t<decltype(make_multiple_vector<N - 1, T>(args...))>;
    return vector<value_type>(size, make_multiple_vector<N - 1, T>(args...));
}

ll get_10000x(string x_str) {
	ll power10 = 4;
	bool after_decimal_point = false;
	ll x = 0;
	REPD(i, 0, x_str.size()) {
		if (x_str[i] == '-') continue;
		if (x_str[i] != '.') {
			x = x * 10LL + ll(x_str[i] - '0');
			if (after_decimal_point) --power10;
		}
		else {
			after_decimal_point = true;
		}
	}
	REPD(i, 0, power10) x *= 10LL;

	return x;
}

ll least_10000_multiple_more_than_or_equal_to_x(ll x) {
	if (x > 0LL) return 10000LL;
	return 0LL;
}

ll largest_10000_multiple_less_than_x(ll x) {
	if (x > 0LL) return 0LL;
	return -10000LL;
}

ll largest_sqrt(ll val) {
	ll sqrt_val = sqrt(double(val));
	if (sqrt_val * sqrt_val > val) {
		while (sqrt_val * sqrt_val > val) {
			--sqrt_val;
		}
	}
	else {
		while ((sqrt_val + 1) * (sqrt_val + 1) <= val) {
			++sqrt_val;
		}
	}
	return sqrt_val;
}

int solve() {
	string x_str, y_str, r_str;
	cin >> x_str >> y_str >> r_str;

	ll x = get_10000x(x_str), y = get_10000x(y_str), r = get_10000x(r_str);
	x %= 10000LL;
	y %= 10000LL;

	ll res = 0;

	ll lattice_x = least_10000_multiple_more_than_or_equal_to_x(x);
	ll y_dist;
	while (abs(lattice_x - x) <= r) {
		y_dist = largest_sqrt(r * r - (lattice_x - x) * (lattice_x - x));
		res += (y + y_dist) / 10000LL;
		if (y - y_dist <= 0) res += (-(y - y_dist)) / 10000LL + 1LL;
		lattice_x += 10000LL;
	}
	lattice_x = largest_10000_multiple_less_than_x(x);
	while (abs(lattice_x - x) <= r) {
		y_dist = largest_sqrt(r * r - (lattice_x - x) * (lattice_x - x));
		res += (y + y_dist) / 10000LL;
		if (y - y_dist <= 0) res += (-(y - y_dist)) / 10000LL + 1LL;
		lattice_x -= 10000LL;
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
	// ll t;
	// cin >> t;
	// REPD(i, 0, t) solve();

	return 0;
}
