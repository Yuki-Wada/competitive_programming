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

	vector<ll> as(n * 2);
	REPD (i, 0, n * 2) {
		cin >> as[i];
	}
	sort(as.begin(), as.end());

	ll first_a, first_b, a1, a2, b1, b2;
	first_a = *max_element(as.begin(), as.end());
	for (ll i = 0; i < n * 2; ++i) {
		multiset<ll> bs;
		for (ll j = 0; j < n * 2 - 1; ++j) {
			if (j == i) continue;
			bs.insert(as[j]);
		}
		first_b = as[i];

		vector<pair<ll, ll>> b_results;
		b1 = first_a;
		bool success = true;
		while (!bs.empty()) {
			b2 = *(--bs.end());
			bs.erase(bs.find(b2));
			if (bs.count(b1 - b2) == 0) {
				success = false;
				break;
			}
			bs.erase(bs.find(b1 - b2));
			b_results.emplace_back(b2, b1 - b2);
			b1 = b2;
		}
		if (success) {
			cout << "YES" << endl;
			cout << first_a + first_b << endl;
			cout << first_a << " " << first_b << endl;
			REPD(i, 0, b_results.size()) {
				cout << b_results[i].first << " " << b_results[i].second << endl;
			}
			return 0;
		}
	}
	cout << "NO" << endl;

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
