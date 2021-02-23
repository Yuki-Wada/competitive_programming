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
	
	vector<ll> as(n), bs(n), ps(n);
	REPD(i, 0, n) cin >> as[i];
	REPD(i, 0, n) cin >> bs[i];
	REPD(i, 0, n) cin >> ps[i], --ps[i];

	vector<pair<ll, ll>> results;
	vector<bool> is_visited(n, false);
	REPD(i, 0, n) {
		if (is_visited[i]) continue;

		ll begin_idx = i, curr_idx = i;
		vector<ll> idxs;
		ll cnt = 0, min_cnt;
		ll min_val = MAX_VALUE;
		do {
			if (as[curr_idx] <= bs[ps[curr_idx]] && curr_idx != ps[curr_idx]) RET(-1);
			idxs.emplace_back(curr_idx);
			if (bs[ps[curr_idx]] < min_val) {
				min_val = bs[ps[curr_idx]];
				min_cnt = cnt;
			}
			++cnt;
			is_visited[curr_idx]= true;
			curr_idx = ps[curr_idx];
		}
		while (curr_idx != begin_idx);
		
		REPD(j, 1, idxs.size()) {
			results.emplace_back(idxs[min_cnt] + 1LL, idxs[(min_cnt - 1LL + idxs.size()) %  idxs.size()] + 1LL);
			min_cnt = (min_cnt - 1LL + idxs.size()) %  idxs.size();
		}
	}

	cout << results.size() << endl;
	REPI(res, results) cout << res.first << " " << res.second << endl;

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
