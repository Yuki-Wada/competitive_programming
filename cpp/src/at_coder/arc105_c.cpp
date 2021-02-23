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
	ll N, M;
	cin >> N >> M;

	vector<ll> ws(N);
	REPD(i, 0, N) cin >> ws[i];
	ll max_w = *max_element(ws.begin(), ws.end());

	vector<pair<ll, ll>> lvs(M);
	REPD(i, 0, M) {
		cin >> lvs[i].first >> lvs[i].second;
		if (lvs[i].second < max_w) RET(-1);
	}

	vector<ll> dist(1LL << N, 0);
    REPD(bit, 0, 1LL << N) {
        ll w = 0;
        REPD(i, 0, N) {
            if ((bit >> i) & 1LL != 0LL) w += ws[i];
        }
        REPD(i, 0, M) {
            if (lvs[i].second < w) dist[bit] = max(dist[bit], lvs[i].first);
        }
    }

	ll res = MAX_VALUE;
	vector<ll> ids(N);
	iota(ids.begin(), ids.end(), 0);
	do {
		ll id1, id2;
		ll bit;
		vector<ll> dps(N);
		REPD(i, 1, N) {
			id1 = ids[i];
			bit = 1LL << id1;
			for(ll j = i; j >= 0; --j) {
				id2 = ids[j];
				bit = bit | (1LL << id2);
				dps[i] = max(dps[i], dps[j] + dist[bit]);
			}
		}
		res = min(res, dps[N - 1]);
	} while (next_permutation(ids.begin(), ids.end()));
 
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
