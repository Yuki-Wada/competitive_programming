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

int solve() {
	ll n, k;
	cin >> n >> k;

	vector<ll> as(n + 1);
	ll a;
	REPD(i, 0, n) {
		cin >> a;
		--a;
		as[i + 1] = (as[i] + a) % k;
	}

	map<ll, vector<ll>> counters;
	REPD(i, 0, n + 1) {
		if (counters.count(as[i]) == 0) counters[as[i]] = vector<ll>();
		counters[as[i]].emplace_back(i);
	}

	ll res = 0;
	REPI(pairs, counters){
		auto& counter = pairs.second;
		ll j = 0;
		REPD(i, 0, counter.size()) {
			while(j < counter.size()) {
				if (counter[j] - counter[i] >= k) break;
				++j;
			}
			res += max(j - i - 1LL, 0LL);
		}
	}

	RET(res);
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
