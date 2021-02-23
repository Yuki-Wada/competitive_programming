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
	ll x, y;
	cin >> x >> y;

	ll cnt = 0;
	while ((x << cnt) <= y) ++cnt;

	ll res = MAX_VALUE;
	if (cnt > 0) {
		ll curr_res = cnt - 1LL;
		ll remain = y - (x << (cnt - 1LL));
		curr_res += remain / (1LL << (cnt - 1LL));
		remain %= 1LL << (cnt - 1LL);

		ll curr, bit_1_count = 0;
		REPD(i, 0, cnt) {
			curr = (remain >> i) % 2LL;
			if (curr == 1LL && bit_1_count == 0LL) ++curr_res;
			else if (curr == 0LL && bit_1_count >= 2LL) ++curr_res;
			if (curr == 1LL) ++bit_1_count;
			else bit_1_count = 0;
		}
		res = min(res, curr_res);
	}
	{
		ll curr_res = cnt;
		ll remain = (x << cnt) - y;
		curr_res += remain / (1LL << cnt);
		remain %= 1LL << cnt;

		ll curr, bit_1_count = 0;
		REPD(i, 0, cnt + 1LL) {
			curr = (remain >> i) % 2LL;
			if (curr == 1LL && bit_1_count == 0LL) ++curr_res;
			else if (curr == 0LL && bit_1_count >= 2LL) ++curr_res;
			if (curr == 1LL) ++bit_1_count;
			else bit_1_count = 0;
		}
		res = min(res, curr_res);
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
