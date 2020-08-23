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

	vector<ll> ps(n);
	vector<ll> cs(n);
	ll p;
	REPD(i, 0, n) { cin >> p; --p; ps[i] = p; }
	REPD(i, 0, n) cin >> cs[i];

	vector<bool> is_examined(n, false);
	vector<ll> cycle_lengths;
	vector<vector<ll>> group_cum_scores;
	REPD(i, 0, n) {
		if (is_examined[i]) continue;
		
		ll pos = i;
		ll cycle_length = 0;
		ll cum_score = 0;
		vector<ll> cum_scores;
		do {
			cum_score += cs[pos];
			cum_scores.emplace_back(cum_score);
			++cycle_length;
			is_examined[pos] = true;
			pos = ps[pos];
		} while (pos != i);
		cycle_lengths.emplace_back(cycle_length);
		group_cum_scores.emplace_back(cum_scores);
	}

	ll res = -MAX_VALUE;
	REPD(i, 0, cycle_lengths.size()) {
		REPD(j1, 0, group_cum_scores[i].size()) {
			REPD(j2, j1, group_cum_scores[i].size() * 2LL) {
				if (j2 - j1 >= k) break;
				ll curr_res = 0;
				if (j2 < group_cum_scores[i].size()) {
					curr_res += group_cum_scores[i][j2];
				}
				else {
					curr_res += group_cum_scores[i][j2 - group_cum_scores[i].size()] + group_cum_scores[i][group_cum_scores[i].size() - 1LL];
				}
				if (j1 > 0) curr_res -= group_cum_scores[i][j1 - 1LL];
				if (group_cum_scores[i][group_cum_scores[i].size() - 1LL] > 0LL) {
					curr_res += group_cum_scores[i][group_cum_scores[i].size() - 1LL] * ((k - j2 + j1 - 1LL) / cycle_lengths[i]);
				}

				res = max(res, curr_res);
			}
		}
	}

	RET(res);

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
