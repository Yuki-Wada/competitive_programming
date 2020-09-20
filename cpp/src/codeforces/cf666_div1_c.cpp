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

int solve() {
	ll n, r1, r2, r3, d;
	cin >> n >> r1 >> r2 >> r3 >> d;

	vector<ll> as(n);
	REPD(i, 0, n) cin >> as[i];

	vector<ll> dps0(n + 1);
	vector<ll> dps1(n + 1);

	REPD(i, 1, n) {
		dps0[i] = min(
			dps0[i - 1] + as[i - 1] * r1 + r3 + d,
			dps1[i - 1] + d * 3LL + r1 + min({
				(as[i - 1] + 2LL) * r1,
				as[i - 1] * r1 + r3,
				r1 + r2
			})
		);
		dps1[i] = dps0[i - 1] + min((as[i - 1] + 1LL) * r1, r2) + d;
	}
	dps0[n] = min({
		dps0[n - 1] + min({
			as[n - 1] * r1 + r3,
			(as[n - 1] + 2LL) * r1 + d * 2LL,
			r1 + r2 + d * 2LL
		}),
		dps1[n - 1] + r1 + min({
			as[n - 1] * r1 + r3 + d,
			(as[n - 1] + 2LL) * r1 + d * 2LL,
			r1 + r2 + d * 2LL
		})
	});

	RET(dps0[n]);
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
