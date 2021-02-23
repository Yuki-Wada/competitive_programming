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
	cout << fixed << setprecision(15);

	ll n, m, k;
	cin >> n >> m >> k;

	auto as = make_multiple_vector<1, ll>(k, 0);
	REPD(i, 0, k) {
		cin >> as[i];
	}
	if (k > 0) {
		ll cnt = 1;
		if (m == 1) RET(-1);
		REPD(i, 1, k) {
			if (as[i] == as[i - 1] + 1) ++cnt;
			else cnt = 1;
			if (cnt >= m) RET(-1);
		}
	}

	queue<pair<long double, long double>> for_remove;
	REPD(i, 0, m) for_remove.push({0.0, 0.0});

	vector<pair<long double, long double>> eis(n);
	pair<long double, long double> sum_e = {0.0, 0.0}, ei = {1.0, 0.0};
	for (ll i = n - 1; i >= 0; --i) {
		if (find(as.begin(), as.end(), i) == as.end()) {
			ei = {sum_e.first / static_cast<long double>(m), sum_e.second / static_cast<long double>(m) + 1.0};
		}	
		else {
			ei = {1.0, 0.0};
		}
		sum_e.first += ei.first;
		sum_e.first -= for_remove.front().first;
		sum_e.second += ei.second;
		sum_e.second -= for_remove.front().second;

		for_remove.pop();
		for_remove.push({ei.first, ei.second});

		eis[i] = ei;
	}

	long double res = eis[0].second / (1.0 - eis[0].first);
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
