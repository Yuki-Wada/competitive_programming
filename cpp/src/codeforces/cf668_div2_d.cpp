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
static const ll MOD = 998244353LL;
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

int solve() {
	ll n;
	cin >> n;

	vector<ll> as(n);
	REPD (i, 0, n) {
		cin >> as[i];
	}

	vector<ll> lefts(n + 1, -1);
	lefts[0] = 0;
	REPD(i, 0, n) {
		lefts[i + 1] = as[i] - lefts[i];
		if (lefts[i + 1] < 0) break;
	}
	if (lefts[n] == 0) RET("YES");

	vector<ll> rights(n + 1, -1);
	rights[n] = 0;
	REPD(i, 0, n) {
		rights[n - i - 1] = as[n - i - 1] - rights[n - i];
		if (rights[n - i - 1] < 0) break;
	}

	ll a0, a1, a2, a3;
	REPD(i, 1, n) {
		a0 = lefts[i - 1];
		a1 = as[i];
		a2 = as[i - 1];
		a3 = rights[i + 1];
		if (a0 < 0 || a3 < 0) continue;
		if (a0 > a1 || a2 < a3) continue;
		a1 -= a0;
		a2 -= a3;
		if (a1 == a2) RET("YES");
	}

	RET("NO");

	return 0;
}

//main function
int main()
{
	cin.tie(0);
	ios::sync_with_stdio(false);

	// solve();
	ll t;
	cin >> t;
	REPD(i, 0, t) solve();

	return 0;
}
